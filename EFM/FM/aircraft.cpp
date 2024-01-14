// ED_FM_Template.cpp : Defines the exported functions for the DLL application.
#include "stdafx.h"

#ifdef FM_TESTS
#include "mockedfmapi.h"
#else
#include "aircraft.h"
#endif

#include "vec3.h"
#include "force.h"
#include "utilities.h"
#include <Math.h>
#include <stdio.h>
#include <string>
#include "aeromodel.h"
#include "fuelsys.h"
#include "engine.h"
#include "airframe.h"
#include "state.h"
#include "world.h"
#include "input.h"
#include "log.h"
#include "enginedata.h"
#include <WinUser.h>

static Aircraft::World* world;
static Aircraft::State* state = NULL;
static Aircraft::AeroModel* aeroModel = NULL;
static Aircraft::FuelSys* fuelSys = NULL;
static Aircraft::Engine* engineL = NULL;
static Aircraft::Engine* engineR = NULL;
static Aircraft::Input* input = NULL;
static Aircraft::AirFrame* airFrame = NULL;
static HWND window = NULL;
static bool aircraftInited = false;

void init()
{
	LOG("aircraft init...\n");

	srand(741);
	world = new Aircraft::World;
	state = new Aircraft::State;
	aeroModel = new Aircraft::AeroModel;
	fuelSys = new Aircraft::FuelSys;
	engineL = new Aircraft::Engine;
	engineL->setPos(Vec3(-8, 0, -1));
	engineR = new Aircraft::Engine;
	engineR->setPos(Vec3(-8, 0, 1));
	input = new Aircraft::Input;
	airFrame = new Aircraft::AirFrame;

	window = GetActiveWindow();
	printf("Have window: %p\n", window);
	LOG("aircraft init complete \n");
}

void cleanup()
{
	delete world;
	delete state;
	delete aeroModel;
	delete fuelSys;
	delete engineL;
	delete engineR;
	delete input;
	delete airFrame;

	world = NULL;
	state = NULL;
	aeroModel = NULL;
	fuelSys = NULL;
	engineL = NULL;
	engineR = NULL;
	input = NULL;
	airFrame = NULL;
	window = NULL;
}

void ed_fm_add_local_force(double& x, double& y, double& z, double& pos_x, double& pos_y, double& pos_z)
{
	x = state->getForce().x;
	y = state->getForce().y;
	z = state->getForce().z;

	pos_x = state->getCg().x;
	pos_y = state->getCg().y;
	pos_z = state->getCg().z;
}

void ed_fm_add_global_force(double& x, double& y, double& z, double& pos_x, double& pos_y, double& pos_z)
{
}

void ed_fm_add_global_moment(double& x, double& y, double& z)
{
}

void ed_fm_add_local_moment(double& x, double& y, double& z)
{
	x = state->getMoment().x;
	y = state->getMoment().y;
	z = state->getMoment().z;
}

void ed_fm_simulate(double dt)
{
	if (!aircraftInited)
	{
		init();
		aircraftInited = true;
	}

	LOG("aircraft simulate...\n");
	Vec3 airspeed = state->getAirspeed();
	double throttle = input->getThrottle();
	printf("throttle values: %f \n", throttle);

	// Engine thrust
	Force thrustL = engineL->getThrust(throttle);
	Force thrustR = engineR->getThrust(throttle);

	double asMag = magnitude(airspeed);
	double dyPre = 0.5 * world->getAtmDensity() * asMag * asMag;
	double mach = getMach(asMag);
	double aoa = state->getAoa();

	// Lift + Drag
	Force aeroForce = aeroModel->getAeroForce(dyPre, aoa, mach);

	double stickRoll = input->getStickRoll();
	double rollTrim = input->getRollTrim();
	double stickPitch = input->getStickPitch();
	double pitchTrim = input->getPitchTrim();
	double rudderYaw = input->getPedalYaw();
	double yawDamper = input->getYawDamper();
	double yawTrim = input->getYawTrim();
	LOG("aircraft stick roll: %f\n", stickRoll);

	airFrame->simulate(dt, mach, stickPitch, pitchTrim, stickRoll, rollTrim, rudderYaw, yawDamper, yawTrim);

	// Control surfaces' forces
	Force alrnLeftF = aeroModel->getLeftAlrnForce(dyPre, stickRoll);
	Force alrnRightF = aeroModel->getRightAlrnForce(dyPre, stickRoll);
	Force eleLeftF = aeroModel->getLeftEleForce(dyPre, stickPitch);
	Force eleRightF = aeroModel->getRightEleForce(dyPre, stickPitch);
	Force rudderF = aeroModel->getRudderForce(dyPre, rudderYaw);

	// set over all force and moment to zero
	state->resetForce();
	state->addForce(thrustL);
	state->addForce(thrustR);
	state->addForce(aeroForce);
	state->addForce(alrnLeftF);
	state->addForce(alrnRightF);
	state->addForce(eleLeftF);
	state->addForce(eleRightF);
	state->addForce(rudderF);

	fuelSys->simulate(dt, input->getThrottle());
	LOG("aircraft simulate complete\n");
}

void ed_fm_set_atmosphere(double h,		  // altitude above sea level
	double t,		  // current atmosphere temperature , Kelwins
	double a,		  // speed of sound
	double ro,	  // atmosphere density
	double p,		  // atmosphere pressure
	double wind_vx, // components of velocity vector, including turbulence in world coordinate system
	double wind_vy, // components of velocity vector, including turbulence in world coordinate system
	double wind_vz  // components of velocity vector, including turbulence in world coordinate system
)
{
	world->setWind(Vec3(wind_vx, wind_vy, wind_vz));
	world->setAtmDensity(ro);
	world->setAtmPre(p);
	world->setAltitude(h);
	world->setAtmTemp(t);
}
/*
called before simulation to set up your environment for the next step
*/
void ed_fm_set_current_mass_state(double mass,
	double center_of_mass_x,
	double center_of_mass_y,
	double center_of_mass_z,
	double moment_of_inertia_x,
	double moment_of_inertia_y,
	double moment_of_inertia_z)
{
	state->setMass(mass);
	state->setCg(Vec3(center_of_mass_x, center_of_mass_y, center_of_mass_z));
}
/*
called before simulation to set up your environment for the next step
*/
void ed_fm_set_current_state(double ax,			  // linear acceleration component in world coordinate system
	double ay,			  // linear acceleration component in world coordinate system
	double az,			  // linear acceleration component in world coordinate system
	double vx,			  // linear velocity component in world coordinate system
	double vy,			  // linear velocity component in world coordinate system
	double vz,			  // linear velocity component in world coordinate system
	double px,			  // center of the body position in world coordinate system
	double py,			  // center of the body position in world coordinate system
	double pz,			  // center of the body position in world coordinate system
	double omegadotx,	  // angular accelearation components in world coordinate system
	double omegadoty,	  // angular accelearation components in world coordinate system
	double omegadotz,	  // angular accelearation components in world coordinate system
	double omegax,		  // angular velocity components in world coordinate system
	double omegay,		  // angular velocity components in world coordinate system
	double omegaz,		  // angular velocity components in world coordinate system
	double quaternion_x, // orientation quaternion components in world coordinate system
	double quaternion_y, // orientation quaternion components in world coordinate system
	double quaternion_z, // orientation quaternion components in world coordinate system
	double quaternion_w  // orientation quaternion components in world coordinate system
)
{
	world->setPos(Vec3(px, py, pz));
	world->setVelocity(Vec3(vx, vy, vz));
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

void ed_fm_set_current_state_body_axis(double ax,	   // linear acceleration component in body coordinate system
	double ay,	   // linear acceleration component in body coordinate system
	double az,	   // linear acceleration component in body coordinate system
	double vx,	   // linear velocity component in body coordinate system
	double vy,	   // linear velocity component in body coordinate system
	double vz,	   // linear velocity component in body coordinate system
	double wind_vx, // wind linear velocity component in body coordinate system
	double wind_vy, // wind linear velocity component in body coordinate system
	double wind_vz, // wind linear velocity component in body coordinate system

	double omegadotx,			  // angular accelearation components in body coordinate system
	double omegadoty,			  // angular accelearation components in body coordinate system
	double omegadotz,			  // angular accelearation components in body coordinate system
	double omegax,				  // angular velocity components in body coordinate system
	double omegay,				  // angular velocity components in body coordinate system
	double omegaz,				  // angular velocity components in body coordinate system
	double yaw,					  // radians
	double pitch,				  // radians
	double roll,					  // radians
	double common_angle_of_attack, // AoA radians
	double common_angle_of_slide	  // AoS radians
)
{
	state->setAoa(common_angle_of_attack);
	state->setAos(common_angle_of_slide);
	state->setAngle(Vec3(roll, yaw, pitch));
	state->setAngVelo(Vec3(omegax, omegay, omegaz));
	state->setAngAcc(Vec3(omegadotx, omegadoty, omegadotz));
	state->setLocalSpeed(Vec3(vx, vy, vz));
	state->setAirspeed(Vec3(vx - wind_vx, vy - wind_vy, vz - wind_vz));
	state->setAccel(Vec3(ax, ay, az));
}
/*
input handling
*/
void ed_fm_set_command(int command,
	float value)
{
	switch (command)
	{
	case Aircraft::Control::THROTTLE:
		input->setThrt(value);
		break;
	case Aircraft::Control::THROTTLE_UP_START:
		input->startThrtUp();
		break;
	case Aircraft::Control::THROTTLE_DOWN_START:
		input->startThrtDown();
		break;
	case Aircraft::Control::THROTTLE_STOP:
		input->stopThrtMove();
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
	case Aircraft::Control::RUDDER_LEFT_STOP:
	case Aircraft::Control::RUDDER_RIGHT_STOP:
		input->resetPedalYaw();
		break;
	case Aircraft::Control::RUDDER_LEFT_START:
		input->startYawLeft();
		break;
	case Aircraft::Control::RUDDER_RIGHT_START:
		input->startYawRight();
		break;
	case Aircraft::Control::ROLL_LEFT_STOP:
	case Aircraft::Control::ROLL_RIGHT_STOP:
		input->resetStickRoll();
		break;
	case Aircraft::Control::ROLL_LEFT_START:
		input->startRollLeft();
		break;
	case Aircraft::Control::ROLL_RIGHT_START:
		input->startRollRight();
		break;
	case Aircraft::Control::PITCH_UP_STOP:
	case Aircraft::Control::PITCH_DOWN_STOP:
		input->stopStickPitch();
		break;
	case Aircraft::Control::PITCH_UP_START:
		input->startPitchUp();
		break;
	case Aircraft::Control::PITCH_DOWN_START:
		input->startPitchDown();
		break;
	default:;
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
bool ed_fm_change_mass(double& delta_mass,
	double& delta_mass_pos_x,
	double& delta_mass_pos_y,
	double& delta_mass_pos_z,
	double& delta_mass_moment_of_inertia_x,
	double& delta_mass_moment_of_inertia_y,
	double& delta_mass_moment_of_inertia_z)
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
void ed_fm_set_internal_fuel(double fuel)
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
void ed_fm_set_external_fuel(int station,
	double fuel,
	double x,
	double y,
	double z)
{
}
/*
	get external fuel volume
*/
double ed_fm_get_external_fuel()
{
	return 0;
}

void ed_fm_set_draw_args(EdDrawArgument* drawargs, size_t size)
{
	drawargs[28].f = input->getThrottle();
	drawargs[29].f = input->getThrottle();

	if (size > 616)
	{
		drawargs[611].f = drawargs[0].f;
		drawargs[614].f = drawargs[3].f;
		drawargs[616].f = drawargs[5].f;
	}

	drawargs[LEFT_AILERON].f = airFrame->getLeftAlrnPos();
	drawargs[RIGHT_AILERON].f = airFrame->getRightAlrnPos();
	drawargs[LEFT_ELEVATOR].f = airFrame->getLeftElePos();
	drawargs[RIGHT_ELEVATOR].f = airFrame->getRightElePos();
	drawargs[RUDDER].f = airFrame->getRudderPos();
	drawargs[LEFT_FLAP].f = airFrame->getLeftFlpPos();
	drawargs[RIGHT_FLAP].f = airFrame->getRightFlpPos();
	drawargs[AIRBRAKE].f = airFrame->getSpdBrkPos();
	drawargs[STABILIZER_TRIM].f = airFrame->getStabAnim();
	drawargs[LEFT_SLAT].f = airFrame->getLeftSltPos();
	drawargs[RIGHT_SLAT].f = airFrame->getRightSltPos();

	drawargs[22].f = 1.0;

	airFrame->setLeftWhlArg(drawargs[103].f);
	airFrame->setRightWhlArg(drawargs[102].f);
}

void ed_fm_configure(const char* cfg_path)
{
}

double test_gear_state = 0;
double ed_fm_get_param(unsigned index)
{
	double throttle = input->getThrottle();
	switch (index)
	{
		// APU
	case ED_FM_ENGINE_0_RPM:
	case ED_FM_ENGINE_0_RELATED_RPM:
	case ED_FM_ENGINE_0_THRUST:
	case ED_FM_ENGINE_0_RELATED_THRUST:
		return 0;
		// ENGINE 1
	case ED_FM_ENGINE_1_CORE_RPM:
	case ED_FM_ENGINE_1_RPM:
		return engineL->getRPM(throttle);
	case ED_FM_ENGINE_1_TEMPERATURE:
		return 23.0;
	case ED_FM_ENGINE_1_OIL_PRESSURE:
		return 600.0;
	case ED_FM_ENGINE_1_FUEL_FLOW:
		return fuelSys->getFuelFlow() / 2;
	case ED_FM_ENGINE_1_RELATED_RPM:
	case ED_FM_ENGINE_1_CORE_RELATED_RPM:
		return engineL->getRPMNorm(throttle);
	case ED_FM_ENGINE_1_CORE_THRUST:
	case ED_FM_ENGINE_1_THRUST:
		return engineL->getThrustVal(throttle);
	case ED_FM_ENGINE_1_RELATED_THRUST:
	case ED_FM_ENGINE_1_CORE_RELATED_THRUST:
		return engineL->getThrustNorm(throttle);
	case ED_FM_ENGINE_1_COMBUSTION:
		return fuelSys->getFuelFlow() / (2 * ENGINE_FUELFLOW_MAX);
		// ENGINE 2
	case ED_FM_ENGINE_2_CORE_RPM:
	case ED_FM_ENGINE_2_RPM:
		return engineR->getRPM(throttle);
	case ED_FM_ENGINE_2_TEMPERATURE:
		return 23.0;
	case ED_FM_ENGINE_2_OIL_PRESSURE:
		return 600.0;
	case ED_FM_ENGINE_2_FUEL_FLOW:
		return fuelSys->getFuelFlow() / 2;
	case ED_FM_ENGINE_2_RELATED_RPM:
	case ED_FM_ENGINE_2_CORE_RELATED_RPM:
		return engineR->getRPMNorm(throttle);
	case ED_FM_ENGINE_2_CORE_THRUST:
	case ED_FM_ENGINE_2_THRUST:
		return engineR->getThrustVal(throttle);
	case ED_FM_ENGINE_2_RELATED_THRUST:
	case ED_FM_ENGINE_2_CORE_RELATED_THRUST:
		return engineR->getThrustNorm(throttle);
	case ED_FM_ENGINE_2_COMBUSTION:
		return fuelSys->getFuelFlow() / (2 * ENGINE_FUELFLOW_MAX);
		// SUSPENSION 0
	case ED_FM_SUSPENSION_0_WHEEL_YAW:
		return airFrame->getNoseWhlAng();
	case ED_FM_SUSPENSION_0_WHEEL_SELF_ATTITUDE:
		return true;
	case ED_FM_SUSPENSION_0_GEAR_POST_STATE:
	case ED_FM_SUSPENSION_0_DOWN_LOCK:
	case ED_FM_SUSPENSION_0_UP_LOCK:
		return airFrame->getNoseGrPos();
		// SUSPENSION 1
	case ED_FM_SUSPENSION_1_GEAR_POST_STATE:
	case ED_FM_SUSPENSION_1_DOWN_LOCK:
	case ED_FM_SUSPENSION_1_UP_LOCK:
		return airFrame->getLeftGrPos();
	case ED_FM_SUSPENSION_1_RELATIVE_BRAKE_MOMENT:
		return pow(input->setLeftBrk(), 3.0);
		// SUSPENSION 2
	case ED_FM_SUSPENSION_2_GEAR_POST_STATE:
	case ED_FM_SUSPENSION_2_DOWN_LOCK:
	case ED_FM_SUSPENSION_2_UP_LOCK:
		return airFrame->getRightGrPos();
	case ED_FM_SUSPENSION_2_RELATIVE_BRAKE_MOMENT:
		return pow(input->setRightBrk(), 3.0);

	case ED_FM_STICK_FORCE_CENTRAL_ROLL: // i.e. trimmered position where force feeled by pilot is zero
		return input->getRollTrim();
	case ED_FM_CAN_ACCEPT_FUEL_FROM_TANKER:
		return 1000.0;
	case ED_FM_ANTI_SKID_ENABLE:
		break;
	}

	return 0;
}

void ed_fm_cold_start()
{
	LOG("aircraft cold start...\n");
	airFrame->setNoseGrPos(1);
	airFrame->setLeftGrPos(1);
	airFrame->setRightGrPos(1);
}

void ed_fm_hot_start()
{
	LOG("aircraft hot start...\n");
	airFrame->setNoseGrPos(1);
	airFrame->setLeftGrPos(1);
	airFrame->setRightGrPos(1);
	input->setThrt(0.25);
	fuelSys->setIgnition(true);
}

void ed_fm_hot_start_in_air()
{
	LOG("aircraft start in air...\n");
	airFrame->setNoseGrPos(0);
	airFrame->setLeftGrPos(0);
	airFrame->setRightGrPos(0);
	input->setThrt(0.75);
	fuelSys->setIgnition(true);
}

bool ed_fm_add_local_force_component(double& x, double& y, double& z, double& pos_x, double& pos_y, double& pos_z)
{
	return false;
}

bool ed_fm_add_global_force_component(double& x, double& y, double& z, double& pos_x, double& pos_y, double& pos_z)
{
	return false;
}

bool ed_fm_add_local_moment_component(double& x, double& y, double& z)
{
	return false;
}

bool ed_fm_add_global_moment_component(double& x, double& y, double& z)
{
	return false;
}

void ed_fm_set_plugin_data_install_path(const char* path)
{
#ifdef LOGGING
	char logFile[200];
	sprintf_s(logFile, 200, "%s/efm_log.txt", path);
	fopen_s(&g_log, logFile, "a+");
#endif
	printf("%s\n", srcvers);

	LOG_BREAK();
	LOG("Begin Log, %s\n", srcvers);
	LOG("Initializing Components...\n");

	g_safeToRun = 1;

	init();
	aircraftInited = true;
}

void ed_fm_release()
{
	cleanup();
	aircraftInited = false;
	g_safeToRun = false;
#ifdef LOGGING
	LOG("Releasing Components...\n");
	LOG("Closing Log...\n");
	if (g_log)
	{
		fclose(g_log);
		g_log = NULL;
	}
#endif
}

bool ed_fm_enable_debug_info()
{
	return false;
}

void ed_fm_suspension_feedback(int idx, const ed_fm_suspension_info* info)
{

	if (idx == 0)
	{
		airFrame->setNoseWhlGS(info->wheel_speed_X);
		airFrame->setNoseWhlForce(Force(Vec3(info->acting_force[0], info->acting_force[1], info->acting_force[2]),
			Vec3(info->acting_force_point[0], info->acting_force_point[1], info->acting_force_point[2])));

		// printf( "Force={%lf,%lf,%lf},Position={%lf,%lf,%lf}\n", info->acting_force[0], info->acting_force[1], info->acting_force[2], info->acting_force_point[0], info->acting_force_point[1], info->acting_force_point[2] );
		airFrame->setNoseWhlComp(info->struct_compression);
	}

	if (idx == 1)
	{
		airFrame->setLeftWhlGS(info->wheel_speed_X);
		airFrame->setLeftWhlComp(info->struct_compression);
		/*printf( "wheel speed: %lf, force: %lf,%lf,%lf, point: %lf, %lf, %lf\n",
			info->wheel_speed_X,
			info->acting_force[0],
			info->acting_force[1],
			info->acting_force[2],
			info->acting_force_point[0],
			info->acting_force_point[1],
			info->acting_force_point[2] );*/
	}

	if (idx == 2)
	{
		airFrame->setRightWhlGS(info->wheel_speed_X);
		airFrame->setRightWhlComp(info->struct_compression);
	}

	if (idx > 2)
	{
		printf("Something Else\n");
	}

	//
	//("Force(%lf, %lf, %lf)\n", info->acting_force[0], info->acting_force[1], info->acting_force[2]);
	// printf("Position(%lf, %lf, %lf)\n", info->acting_force_point[0], info->acting_force_point[1], info->acting_force_point[2]);
	// printf("Struct Compression %d: %lf\n", idx, info->struct_compression);
	// printf("Integrity Factor: %lf", info->integrity_factor);
}

void ed_fm_set_surface(
	double h,	  // surface height under the center of aircraft
	double h_obj, // surface height with objects
	unsigned surface_type,
	double normal_x, // components of normal vector to surface
	double normal_y, // components of normal vector to surface
	double normal_z	 // components of normal vector to surface
)
{
	printf("Type: %d\n", surface_type);
	world->setSurfHeight(world->getPos().y - h_obj);
	world->setSurfNorm(Vec3(normal_x, normal_y, normal_z));
}
