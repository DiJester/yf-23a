// ED_FM_Template.cpp : Defines the exported functions for the DLL application.
#include "stdafx.h"
#include "yf23a.h"
#include "./common/vec3.h"
#include "./common/utilities.h"
#include <Math.h>
#include <stdio.h>
#include <string>
#include "./airframe/airframe.h"
#include "./fuelsys/fuelsys.h"
#include "./engine/engine.h"
#include "./flightcontrol/flightcontrol.h"
#include "./state/state.h"
#include "./world/world.h"
#include "./input/input.h"


static Aircraft::World* world = NULL;
static Aircraft::State* state = NULL;
static Aircraft::AirFrame* airFrame = NULL;
static Aircraft::FuelSys* fuelSys = NULL;
static Aircraft::Engine* engine1 = NULL;
static Aircraft::Engine* engine2 = NULL;
static Aircraft::Input* input = NULL;
static Aircraft::FlightControl* flightControl = NULL;
static HWND window = NULL;

void init()
{
	srand( 741 );

	world = new Aircraft::World;
	state = new Aircraft::State;
	airFrame = new Aircraft::AirFrame;
	fuelSys = new Aircraft:: FuelSys;
	engine1 = new Aircraft::Engine;
	engine2 = new Aircraft::Engine;
	input = new Aircraft::Input;
	flightControl = new Aircraft::FlightControl;

	window = GetActiveWindow();
	printf( "Have window: %p\n", window );
}

void cleanup() {
	delete world;
	delete state;
	delete airFrame;
	delete fuelSys;
	delete engine1;
	delete engine2;
	delete input;
	delete flightControl;


	world = NULL;
	state = NULL;
	airFrame = NULL;
	fuelSys = NULL;
	engine1 = NULL;
	engine2 =NULL;
	input = NULL;
	flightControl = NULL;
	window = NULL;
}

void ed_fm_add_local_force(double & x,double &y,double &z,double & pos_x,double & pos_y,double & pos_z)
{
	x = state->getForce().x;
	y = state->getForce().y;
	z = state->getForce().z;

	pos_x = state->getCg().x;
	pos_y = state->getCg().y;
	pos_z = state->getCg().z;
}

void ed_fm_add_global_force(double & x,double &y,double &z,double & pos_x,double & pos_y,double & pos_z)
{

}

void ed_fm_add_global_moment(double & x,double &y,double &z)
{

}

void ed_fm_add_local_moment(double & x,double &y,double &z)
{
	x = state->getMoment().x;
	y = state->getMoment().y;
	z = state->getMoment().z;
}

void ed_fm_simulate(double dt)
{
	Vec3 airspeed = state->getAirspeed();
	double throttle = input->getThrottle();

	// Engine thrust
	Force thrust1 = engine1->getThrust(throttle);
	Force thrust2 = engine2->getThrust(throttle);
	
	double asMag = magnitude(airspeed);
	double dyPre= 0.5 * world->getAtmDensity()*asMag*asMag;
	double mach = getMach(asMag);
	double aoa = state.getAoa();

	// Lift + Drag
	Vec3 aeroForce = airFrame->getAeroForce(dyPre, aoa, mach);
	// Control surfaces' forces
	Vec3 alrnLeftF = flightControl->getLeftAlronForce();
	Vec3 alrnRightF = flightControl->getRightAlronForce();
	Vec3 eleLeftF = flightControl->getLeftAlronForce();
	Vec3 eleRightF = flightControl->getRightAlronForce();
	Vec3 rudderF = flightControl->getRudderForce(); 

	state->addForce(thrust1);
	state->addForce(thrust2);
	state->addForce(aeroForce);
	state->addForce(alrnLeftF);
	state->addForce(alrnRightF);
	state->addForce(eleLeftF);
	state->addForce(eleRightF);
	state->addForce(rudderF);

	fuelSys->simulate(dt);
}

void ed_fm_set_atmosphere(double h,//altitude above sea level
							double t,//current atmosphere temperature , Kelwins
							double a,//speed of sound
							double ro,// atmosphere density
							double p,// atmosphere pressure
							double wind_vx,//components of velocity vector, including turbulence in world coordinate system
							double wind_vy,//components of velocity vector, including turbulence in world coordinate system
							double wind_vz //components of velocity vector, including turbulence in world coordinate system
						)
{
	world->setWind((wind_vx, wind_vy, wind_vz));
	world->setAtmDensity(ro);
	world->setAtmPre(p);
	world->setAltitude(h);
	world->setAtmTemp(t);
}
/*
called before simulation to set up your environment for the next step
*/
void ed_fm_set_current_mass_state (double mass,
									double center_of_mass_x,
									double center_of_mass_y,
									double center_of_mass_z,
									double moment_of_inertia_x,
									double moment_of_inertia_y,
									double moment_of_inertia_z
									)
{
	state.setMass(mass);
	state->setMoment((center_of_mass_x,center_of_mass_y,center_of_mass_z));
}
/*
called before simulation to set up your environment for the next step
*/
void ed_fm_set_current_state (double ax,//linear acceleration component in world coordinate system
							double ay,//linear acceleration component in world coordinate system
							double az,//linear acceleration component in world coordinate system
							double vx,//linear velocity component in world coordinate system
							double vy,//linear velocity component in world coordinate system
							double vz,//linear velocity component in world coordinate system
							double px,//center of the body position in world coordinate system
							double py,//center of the body position in world coordinate system
							double pz,//center of the body position in world coordinate system
							double omegadotx,//angular accelearation components in world coordinate system
							double omegadoty,//angular accelearation components in world coordinate system
							double omegadotz,//angular accelearation components in world coordinate system
							double omegax,//angular velocity components in world coordinate system
							double omegay,//angular velocity components in world coordinate system
							double omegaz,//angular velocity components in world coordinate system
							double quaternion_x,//orientation quaternion components in world coordinate system
							double quaternion_y,//orientation quaternion components in world coordinate system
							double quaternion_z,//orientation quaternion components in world coordinate system
							double quaternion_w //orientation quaternion components in world coordinate system
							)
{
	world->setPos((px,py,pz));
	world->setVelocity((vx,vy,vz));
	Vec3 direction;

	double x = quaternion_x;
	double y = quaternion_y;
	double z = quaternion_z;
	double w = quaternion_w;

	double y2 = y + y;
	double z2 = z + z;

	double yy = y * y2;
	double zz = z * z2;

	double xy = x * y2;
	double xz = x * z2;

	double wz = w * z2;
	double wy = w * y2;


	direction.x = 1.0 - (yy + zz);
	direction.y = xy + wz;
	direction.z = xz - wy;
	world->setDirection(direction);

	Vec3 globalUp;
	double x2 = x + x;
	double yz = y * z2;
	double wx = w * x2;

	double xx = x * x2;

	globalUp.x = xy + wz;
	globalUp.y = 1.0 - (xx + zz);
	globalUp.z = yz - wx;
	world->setGlobalDown(-globalUp);

}


void ed_fm_set_current_state_body_axis(double ax,//linear acceleration component in body coordinate system
	double ay,//linear acceleration component in body coordinate system
	double az,//linear acceleration component in body coordinate system
	double vx,//linear velocity component in body coordinate system
	double vy,//linear velocity component in body coordinate system
	double vz,//linear velocity component in body coordinate system
	double wind_vx,//wind linear velocity component in body coordinate system
	double wind_vy,//wind linear velocity component in body coordinate system
	double wind_vz,//wind linear velocity component in body coordinate system

	double omegadotx,//angular accelearation components in body coordinate system
	double omegadoty,//angular accelearation components in body coordinate system
	double omegadotz,//angular accelearation components in body coordinate system
	double omegax,//angular velocity components in body coordinate system
	double omegay,//angular velocity components in body coordinate system
	double omegaz,//angular velocity components in body coordinate system
	double yaw,  //radians
	double pitch,//radians
	double roll, //radians
	double common_angle_of_attack, //AoA radians
	double common_angle_of_slide   //AoS radians
	)
{
	state->setAoa(common_angle_of_attack);
	state->setAos(common_angle_of_slide);
	state->setAngle((roll, yaw, pitch));
	state->setAngVelo((omegax,omegay, omegaz));
	state->setAngAcc((omegadotx,omegadoty,omegadotz));
	state->setLocalSpeed((vx,vy,vz));
	state->setAirspeed((vx-wind_vx, vy-wind_vy, vz-wind_vz));
	state->setAccel((ax,ay,az));
}
/*
input handling
*/
void ed_fm_set_command (int command,
							float value)
{
	switch (command) {
		case Aircraft::Control::THROTTLE:
			input->setThrottle(value);
			break;
		case Aircraft::Control::ROLL:
			input->setStickRoll(value);
			break;
		case Aircraft::Control::PITCH:
			input->setStickPitch(value);
			break;
		case Aircraft::Control::YAW:
			input->setPedalYaw(value);
			break;
		default:
		;
	}
}
/*
	Mass handling 

	will be called  after ed_fm_simulate :
	you should collect mass changes in ed_fm_simulate 

	double delta_mass = 0;
	double x = 0;
	double y = 0; 
	double z = 0;
	double piece_of_mass_MOI_x = 0;
	double piece_of_mass_MOI_y = 0; 
	double piece_of_mass_MOI_z = 0;
 
	//
	while (ed_fm_change_mass(delta_mass,x,y,z,piece_of_mass_MOI_x,piece_of_mass_MOI_y,piece_of_mass_MOI_z))
	{
	//internal DCS calculations for changing mass, center of gravity,  and moments of inertia
	}
*/
bool ed_fm_change_mass  (double & delta_mass,
						double & delta_mass_pos_x,
						double & delta_mass_pos_y,
						double & delta_mass_pos_z,
						double & delta_mass_moment_of_inertia_x,
						double & delta_mass_moment_of_inertia_y,
						double & delta_mass_moment_of_inertia_z
						)
{
	const Vec3& fuelSysPos = fuelSys->getPos();
	delta_mass = fuelSys->getFuelQtyDelta();
	fuelSys->setPreInterFuel();

	delta_mass_pos_x = fuelSysPos.x;
	delta_mass_pos_y = fuelSysPos.y;
	delta_mass_pos_z = fuelSysPos.z;

	return true;
}
/*
	set internal fuel volume , init function, called on object creation and for refueling , 
	you should distribute it inside at different fuel tanks
*/
void   ed_fm_set_internal_fuel(double fuel)
{
	fuelSys->setInternalFuel(fuel);
}
/*
	get internal fuel volume 
*/
double ed_fm_get_internal_fuel()
{
	return fuelSys->getInternalFuel();
}
/*
	set external fuel volume for each payload station , called for weapon init and on reload
*/
void  ed_fm_set_external_fuel (int	 station,
								double fuel,
								double x,
								double y,
								double z)
{

}
/*
	get external fuel volume 
*/
double ed_fm_get_external_fuel ()
{
	return 0;
}

void ed_fm_set_draw_args (EdDrawArgument * drawargs,size_t size)
{
	drawargs[28].f   = input->getThrottle();
	drawargs[29].f   = input->getThrottle();

	if (size > 616)
	{	
		drawargs[611].f = drawargs[0].f;
		drawargs[614].f = drawargs[3].f;
		drawargs[616].f = drawargs[5].f;
	}

	drawargs[LEFT_AILERON].f = flightControl->getLeftAlrnDflt();
	drawargs[RIGHT_AILERON].f =flightControl->getRightAlrnDflt();
	drawargs[LEFT_ELEVATOR].f= flightControl->getLeftEleDflt();
	drawargs[RIGHT_ELEVATOR].f = flightControl->getRightEleDflt();
	drawargs[RUDDER].f = flightControl->getRudderDflt();
}


void ed_fm_configure(const char * cfg_path)
{

}

double test_gear_state = 0;
double ed_fm_get_param(unsigned index)
{

	switch (index)
		{
		case ED_FM_ENGINE_0_RPM:			
		case ED_FM_ENGINE_0_RELATED_RPM:	
		case ED_FM_ENGINE_0_THRUST:			
		case ED_FM_ENGINE_0_RELATED_THRUST:	
			return 0; // APU
		case ED_FM_ENGINE_1_RPM:
			return engine1->getRPM();
		case ED_FM_ENGINE_1_RELATED_RPM:
			return engine1->getRPMNorm();
		case ED_FM_ENGINE_1_THRUST:
			return magnitude(engine1->getThrust().force);
		case ED_FM_ENGINE_1_RELATED_THRUST:
			return magnitude(engine1->getThrust().force);
		case ED_FM_ENGINE_1_COMBUSTION:
			return engine1->getFuelFlow();
		case ED_FM_ENGINE_2_RPM:
			return engine2->getRPM();
		case ED_FM_ENGINE_2_RELATED_RPM:
			return engine2->getRPMNorm();
		case ED_FM_ENGINE_2_THRUST:
			return magnitude(engine2->getThrust().force);
		case ED_FM_ENGINE_2_RELATED_THRUST:
			return engine2->magnitude(getThrust().force);
		case ED_FM_ENGINE_2_COMBUSTION:
			return engine2->getFuelFlow();
		}

	return 0;
}


void ed_fm_cold_start()
{

}

void ed_fm_hot_start()
{

}

void ed_fm_hot_start_in_air()
{

}

bool ed_fm_add_local_force_component( double & x,double &y,double &z,double & pos_x,double & pos_y,double & pos_z )
{
	return false;
}

bool ed_fm_add_global_force_component( double & x,double &y,double &z,double & pos_x,double & pos_y,double & pos_z )
{
	return false;
}

bool ed_fm_add_local_moment_component( double & x,double &y,double &z )
{
	return false;
}

bool ed_fm_add_global_moment_component( double & x,double &y,double &z )
{
	return false;
}


void ed_fm_set_plugin_data_install_path ( const char* path )
{
	init();
}


void ed_fm_release ()
{
	cleanup();
}

