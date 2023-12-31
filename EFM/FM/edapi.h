#pragma once
#ifndef EDAPI_H
#define EDAPI_H

#include <stdlib.h>
#include <stdio.h>
#include "../include/Cockpit/ccParametersAPI.h"
#include "vec3.h"
#include "log.h"

//=========================================================================//

extern "C"
{
	void _set_radio(void* ptr, bool on);
	bool _get_radio(void* ptr);
	bool _get_intercom(void* ptr);
	bool _is_on_intercom(void* ptr, void* fooPtr);
	void _switch_radio(void* ptr, void* fnc);
	int _get_gun_shells(void* ptr, void* fnc);
	bool _ext_is_on(void* ptr, void* fnc);

	void _connect_radio_power(void* radio, void* elec, void* fnc);
	void _set_radio_power(void* radio, bool value, void* fnc);
}

namespace Aircraft
{ // namespace begin

	class EdApi
	{
	public:
		EdApi(cockpit_param_api api) : edApi(api)
		{
			Init();
		}

		EdApi()
		{
			edApi = ed_get_cockpit_param_api();
			Init();
		}

		void Init()
		{
			RPM = edApi.pfn_ed_cockpit_get_parameter_handle("RPM");

			noseGear = edApi.pfn_ed_cockpit_get_parameter_handle("FM_GEAR_NOSE");
			leftGear = edApi.pfn_ed_cockpit_get_parameter_handle("FM_GEAR_LEFT");
			rightGear = edApi.pfn_ed_cockpit_get_parameter_handle("FM_GEAR_RIGHT");

			flaps = edApi.pfn_ed_cockpit_get_parameter_handle("FM_FLAPS");
			airbrakes = edApi.pfn_ed_cockpit_get_parameter_handle("FM_BRAKES");
			spoiler = edApi.pfn_ed_cockpit_get_parameter_handle("FM_SPOILERS");

			test = edApi.pfn_ed_cockpit_get_parameter_handle("TEST_TEST");
			throttlePosition = edApi.pfn_ed_cockpit_get_parameter_handle("FM_THROTTLE_POSITION");

			engineThrottlePosition = edApi.pfn_ed_cockpit_get_parameter_handle("FM_ENGINE_THROTTLE_POSITION");
			engineIgnition = edApi.pfn_ed_cockpit_get_parameter_handle("FM_IGNITION");
			engineBleedAir = edApi.pfn_ed_cockpit_get_parameter_handle("FM_BLEED_AIR");

			stickPitch = edApi.pfn_ed_cockpit_get_parameter_handle("STICK_PITCH");
			stickRoll = edApi.pfn_ed_cockpit_get_parameter_handle("STICK_ROLL");
			rudderPedals = edApi.pfn_ed_cockpit_get_parameter_handle("RUDDER_PEDALS");
			leftBrakePedal = edApi.pfn_ed_cockpit_get_parameter_handle("LEFT_BRAKE_PEDAL");
			rightBrakePedal = edApi.pfn_ed_cockpit_get_parameter_handle("RIGHT_BRAKE_PEDAL");

			stickInputPitch = edApi.pfn_ed_cockpit_get_parameter_handle("FM_STICK_INPUT_PITCH");
			stickInputRoll = edApi.pfn_ed_cockpit_get_parameter_handle("FM_STICK_INPUT_ROLL");

			pitchTrim = edApi.pfn_ed_cockpit_get_parameter_handle("PITCH_TRIM");
			rollTrim = edApi.pfn_ed_cockpit_get_parameter_handle("ROLL_TRIM");
			rudderTrim = edApi.pfn_ed_cockpit_get_parameter_handle("RUDDER_TRIM");

			nws = edApi.pfn_ed_cockpit_get_parameter_handle("FM_NWS");

			internalFuel = edApi.pfn_ed_cockpit_get_parameter_handle("FM_INTERNAL_FUEL");
			externalFuel = edApi.pfn_ed_cockpit_get_parameter_handle("FM_EXTERNAL_FUEL");

			radio = edApi.pfn_ed_cockpit_get_parameter_handle("THIS_RADIO_PTR");
			elec = edApi.pfn_ed_cockpit_get_parameter_handle("THIS_ELEC_PTR");

			radioPower = edApi.pfn_ed_cockpit_get_parameter_handle("FM_RADIO_POWER");

			intercom = edApi.pfn_ed_cockpit_get_parameter_handle("THIS_INTERCOM_PTR");
			weapon = edApi.pfn_ed_cockpit_get_parameter_handle("THIS_WEAPON_PTR");

			cockpitShake = edApi.pfn_ed_cockpit_get_parameter_handle("FM_COCKPIT_SHAKE");

			airspeed = edApi.pfn_ed_cockpit_get_parameter_handle("FM_AIRSPEED");

			yawDamper = edApi.pfn_ed_cockpit_get_parameter_handle("FM_YAW_DAMPER");

			beta = edApi.pfn_ed_cockpit_get_parameter_handle("FM_BETA");
			aoa = edApi.pfn_ed_cockpit_get_parameter_handle("FM_AOA");
			aoaUnits = edApi.pfn_ed_cockpit_get_parameter_handle("FM_AOA_UNITS");

			validSolution = edApi.pfn_ed_cockpit_get_parameter_handle("FM_VALID_SOLUTION");
			setTarget = edApi.pfn_ed_cockpit_get_parameter_handle("FM_SET_TARGET");
			slantRange = edApi.pfn_ed_cockpit_get_parameter_handle("FM_SLANT_RANGE");

			radarAltitude = edApi.pfn_ed_cockpit_get_parameter_handle("FM_RADAR_ALTITUDE");
			gunsightAngle = edApi.pfn_ed_cockpit_get_parameter_handle("FM_GUNSIGHT_ANGLE");
			targetSet = edApi.pfn_ed_cockpit_get_parameter_handle("FM_TARGET_SET");
			cp741Power = edApi.pfn_ed_cockpit_get_parameter_handle("FM_CP741_POWER");
			inRange = edApi.pfn_ed_cockpit_get_parameter_handle("D_ADVISORY_INRANGE");

			dumpingFuel = edApi.pfn_ed_cockpit_get_parameter_handle("FM_DUMPING_FUEL");
			avionicsAlive = edApi.pfn_ed_cockpit_get_parameter_handle("FM_AVIONICS_ALIVE");

			lTankCapacity = edApi.pfn_ed_cockpit_get_parameter_handle("FM_L_TANK_CAPACITY");
			cTankCapacity = edApi.pfn_ed_cockpit_get_parameter_handle("FM_C_TANK_CAPACITY");
			rTankCapacity = edApi.pfn_ed_cockpit_get_parameter_handle("FM_R_TANK_CAPACITY");

			sndCockpitRattle = edApi.pfn_ed_cockpit_get_parameter_handle("SND_ALWS_COCKPIT_RATTLE");

			leftSlat = edApi.pfn_ed_cockpit_get_parameter_handle("FM_SLAT_LEFT");
			rightSlat = edApi.pfn_ed_cockpit_get_parameter_handle("FM_SLAT_RIGHT");

			usingFFB = edApi.pfn_ed_cockpit_get_parameter_handle("FM_USING_FFB");

			elecPrimaryAC = edApi.pfn_ed_cockpit_get_parameter_handle("ELEC_PRIMARY_AC_OK");
			elecPrimaryDC = edApi.pfn_ed_cockpit_get_parameter_handle("ELEC_PRIMARY_DC_OK");
			elecMonitoredAC = edApi.pfn_ed_cockpit_get_parameter_handle("ELEC_AFT_MON_AC_OK");
			masterTest = edApi.pfn_ed_cockpit_get_parameter_handle("D_MASTER_TEST");

			fuelTransferCaution = edApi.pfn_ed_cockpit_get_parameter_handle("D_FUELTRANS_CAUTION");
			fuelBoostCaution = edApi.pfn_ed_cockpit_get_parameter_handle("D_FUELBOOST_CAUTION");

			gForce = edApi.pfn_ed_cockpit_get_parameter_handle("FM_GFORCE");
			fuelFlow = edApi.pfn_ed_cockpit_get_parameter_handle("FM_FUEL_FLOW");

			tcnX = edApi.pfn_ed_cockpit_get_parameter_handle("API_TCN_X");
			tcnY = edApi.pfn_ed_cockpit_get_parameter_handle("API_TCN_Y");
			tcnZ = edApi.pfn_ed_cockpit_get_parameter_handle("API_TCN_Z");
			tcnValid = edApi.pfn_ed_cockpit_get_parameter_handle("API_TCN_VALID");
			tcnObjectID = edApi.pfn_ed_cockpit_get_parameter_handle("API_TCN_OBJECT_ID");
			tcnUnitName = edApi.pfn_ed_cockpit_get_parameter_handle("API_TCN_OBJECT_NAME");

			mclX = edApi.pfn_ed_cockpit_get_parameter_handle("API_MCL_X");
			mclY = edApi.pfn_ed_cockpit_get_parameter_handle("API_MCL_Y");
			mclZ = edApi.pfn_ed_cockpit_get_parameter_handle("API_MCL_Z");
			mclHeading = edApi.pfn_ed_cockpit_get_parameter_handle("API_MCL_HEADING");
			mclValid = edApi.pfn_ed_cockpit_get_parameter_handle("API_MCL_VALID");
			mclObjectID = edApi.pfn_ed_cockpit_get_parameter_handle("API_MCL_OBJECT_ID");
			mclUnitName = edApi.pfn_ed_cockpit_get_parameter_handle("API_MCL_OBJECT_NAME");

			accelerationX = edApi.pfn_ed_cockpit_get_parameter_handle("FM_ACCELERATION_X");
			accelerationY = edApi.pfn_ed_cockpit_get_parameter_handle("FM_ACCELERATION_Y");
			accelerationZ = edApi.pfn_ed_cockpit_get_parameter_handle("FM_ACCELERATION_Z");

			ADC_TAS = edApi.pfn_ed_cockpit_get_parameter_handle("ADC_TAS");
			ADC_CAS = edApi.pfn_ed_cockpit_get_parameter_handle("FM_CAS");
			ADC_ALT = edApi.pfn_ed_cockpit_get_parameter_handle("ADC_ALT");
			ADC_altSetting = edApi.pfn_ed_cockpit_get_parameter_handle("ADC_ALT_SETTING");
			ADC_MACH = edApi.pfn_ed_cockpit_get_parameter_handle("ADC_MACH");

			chocks = edApi.pfn_ed_cockpit_get_parameter_handle("WHEEL_CHOCKS_STATE");

			averageLoadFactor = edApi.pfn_ed_cockpit_get_parameter_handle("SND_ALWS_DAMAGE_AIRFRAME_STRESS");
			engineStall = edApi.pfn_ed_cockpit_get_parameter_handle("SND_INST_ENGINE_STALL");

			disableRadar = edApi.pfn_ed_cockpit_get_parameter_handle("FM_RADAR_DISABLED");
			wheelBrakeAssist = edApi.pfn_ed_cockpit_get_parameter_handle("FM_WHEEL_BRAKE_ASSIST");

			autoCatMode = edApi.pfn_ed_cockpit_get_parameter_handle("FM_CAT_AUTO_MODE");
			egg = edApi.pfn_ed_cockpit_get_parameter_handle("EGG");
			eggScore = edApi.pfn_ed_cockpit_get_parameter_handle("EGG_SCORE");
			eggHighScore = edApi.pfn_ed_cockpit_get_parameter_handle("EGG_HIGH_SCORE");

			skid_l_detector = edApi.pfn_ed_cockpit_get_parameter_handle("SKID_L_DETECTOR");
			skid_r_detector = edApi.pfn_ed_cockpit_get_parameter_handle("SKID_R_DETECTOR");
		}

		cockpit_param_api& api()
		{
			return edApi;
		}

		inline void coldInit()
		{
		}

		inline void hotInit()
		{
		}

		inline void airbornInit()
		{
		}

		inline bool getEgg()
		{
			return getParamNumber(egg) > 0.5;
		}

		inline void setEggScore(int score)
		{
			setParamNumber(eggScore, score);
		}

		inline void setEggHighScore(int score)
		{
			setParamNumber(eggHighScore, score);
		}

		inline void* getPointer(void* handle)
		{
			char buffer[20];
			uintptr_t ptr = NULL;
			getParamString(handle, buffer, 20);
			printf("%s\n", buffer);
			// printf( "%s\n", buffer );
			if (sscanf_s(buffer, "%p.0", &ptr))
			{
				if (ptr)
				{
					// 0x20 is the offset from the lua virtual
					// function table to the primary virtual function
					// table.
					//
					// primary table | 16 bytes of data | global context pointer | lua table
					return (void*)(ptr - 0x20);
				}
			}
			else
			{
				LOG("Pointer could not be found from string: %s\n", buffer)
			}

			return NULL;
		}

		inline void* getIntercomPointer()
		{
			printf("Intercom: ");
			return getPointer(intercom);
		}

		inline void* getRadioPointer()
		{
			printf("Radio: ");
			return getPointer(radio);
		}

		inline void* getElecPointer()
		{
			printf("Elec: ");
			return getPointer(elec);
		}

		inline void* getWeapPointer()
		{
			printf("Weapon: ");
			return getPointer(weapon);
		}

		inline bool getChocks() const
		{
			return getParamNumber(chocks) > 0.5;
		}

		inline uint32_t getTacanObjectID()
		{
			return (uint32_t)getParamNumber(tcnObjectID);
		}

		inline void getTacanObjectName(char* buffer, unsigned int size)
		{
			getParamString(tcnUnitName, buffer, size);

			// printf( "%s\n", buffer );
		}

		inline uint32_t getMCLObjectID()
		{
			return (uint32_t)getParamNumber(mclObjectID);
		}

		inline void getMCLObjectName(char* buffer, unsigned int size)
		{
			getParamString(mclUnitName, buffer, size);

			// printf( "%s\n", buffer );
		}

		inline bool getRadarDisabled()
		{
			return getParamNumber(disableRadar) > 0.5;
		}

		inline bool getCatAutoMode()
		{
			return getParamNumber(autoCatMode) > 0.5;
		}

		inline void SetLSkid(bool skid)
		{
			setParamNumber(skid_l_detector, (double)skid);
		}

		inline void SetRSkid(bool skid)
		{
			setParamNumber(skid_r_detector, (double)skid);
		}

		inline void setEngineStall(bool stall)
		{
			setParamNumber(engineStall, (double)stall);
		}

		inline void ADC_setTAS(double value)
		{
			setParamNumber(ADC_TAS, value);
		}

		inline void ADC_setCAS(double value)
		{
			setParamNumber(ADC_CAS, value);
		}

		inline void ADC_setAlt(double value)
		{
			setParamNumber(ADC_ALT, value);
		}

		inline void ADC_setMeasuredMach(double value)
		{
			setParamNumber(ADC_MACH, value);
		}

		inline void setWorldAcceleration(const Vec3& a)
		{
			setParamNumber(accelerationX, a.x);
			setParamNumber(accelerationY, a.y);
			setParamNumber(accelerationZ, a.z);
		}

		inline void setTacanPosition(const Vec3& v)
		{
			setParamNumber(tcnX, v.x);
			setParamNumber(tcnY, v.y);
			setParamNumber(tcnZ, v.z);
		}

		inline void setTacanValid(bool valid)
		{
			setParamNumber(tcnValid, (double)valid);
		}

		inline void setMCLPosition(const Vec3& v)
		{
			setParamNumber(mclX, v.x);
			setParamNumber(mclY, v.y);
			setParamNumber(mclZ, v.z);
		}

		inline void setMCLHeading(double heading)
		{
			setParamNumber(mclHeading, heading);
		}

		inline void setMCLValid(bool valid)
		{
			setParamNumber(mclValid, (double)valid);
		}

		inline void setFuelFlow(double number)
		{
			setParamNumber(fuelFlow, number);
		}

		inline void setLeftSlat(double number)
		{
			setParamNumber(leftSlat, number);
		}

		inline void setRightSlat(double number)
		{
			setParamNumber(rightSlat, number);
		}

		inline void setCockpitRattle(double number)
		{
			setParamNumber(sndCockpitRattle, number);
		}

		inline void setInternalFuel(double number)
		{
			setParamNumber(internalFuel, number);
		}

		inline void setExternalFuel(double number)
		{
			setParamNumber(externalFuel, number);
		}

		inline void setRPM(double number)
		{
			setParamNumber(RPM, number);
		}

		inline void setThrottlePosition(double number)
		{
			setParamNumber(throttlePosition, number);
		}

		inline void setStickPitch(double number)
		{
			setParamNumber(stickPitch, number);
		}

		inline void setStickRoll(double number)
		{
			setParamNumber(stickRoll, number);
		}

		inline void setRudderPedals(double number)
		{
			setParamNumber(rudderPedals, number);
		}

		inline void setAirspeed(double number)
		{
			setParamNumber(airspeed, number);
		}

		inline void setAOA(double number)
		{
			setParamNumber(aoa, number);
		}

		inline void setBeta(double number)
		{
			setParamNumber(beta, number);
		}

		inline void setAOAUnits(double number)
		{
			setParamNumber(aoaUnits, number);
		}

		inline void setValidSolution(bool solution)
		{
			setParamNumber(validSolution, (double)solution);
		}

		inline void setTargetSet(bool targetSet_)
		{
			setParamNumber(targetSet, (double)targetSet_);
		}

		inline void setStickInputPitch(double number)
		{
			setParamNumber(stickInputPitch, number);
		}

		inline void setStickInputRoll(double number)
		{
			setParamNumber(stickInputRoll, number);
		}

		inline void setLeftBrakePedal(double number)
		{
			setParamNumber(leftBrakePedal, number);
		}

		inline void setRightBrakePedal(double number)
		{
			setParamNumber(rightBrakePedal, number);
		}

		inline void setUsingFFB(bool ffb)
		{
			setParamNumber(usingFFB, (double)ffb);
		}

		inline void setInRange(bool inRange_)
		{
			if (getMasterTest() == false)
			{
				setParamNumber(inRange, (double)inRange_);
			}
		}

		inline void setFuelTransferCaution(bool caution)
		{
			setParamNumber(fuelTransferCaution, (double)caution);
		}

		inline void setFuelBoostCaution(bool caution)
		{
			setParamNumber(fuelBoostCaution, (double)caution);
		}

		inline void setLoadFactor(double factor)
		{
			setParamNumber(averageLoadFactor, factor);
		}

		inline double getGForce()
		{
			return getParamNumber(gForce);
		}

		inline bool getCP741Power()
		{
			return getParamNumber(cp741Power) > 0.5;
		}

		inline bool getElecPrimaryAC()
		{
			return getParamNumber(elecPrimaryAC) > 0.5;
		}

		inline bool getElecPrimaryDC()
		{
			return getParamNumber(elecPrimaryDC) > 0.5;
		}

		inline bool getElecMonitoredAC()
		{
			return getParamNumber(elecMonitoredAC) > 0.5;
		}

		inline bool getMasterTest()
		{
			return getParamNumber(masterTest) > 0.5;
		}

		inline bool getRadioPower()
		{
			return getParamNumber(radioPower) > 0.5;
		}

		inline double getSlantRange()
		{
			return getParamNumber(slantRange);
		}

		inline bool getSetTarget()
		{
			return getParamNumber(setTarget) > 0.5;
		}

		inline double getGearNose()
		{
			return getParamNumber(noseGear);
		}
		inline double getGearLeft()
		{
			return getParamNumber(leftGear);
		}
		inline double getGearRight()
		{
			return getParamNumber(rightGear);
		}

		inline double getFlaps()
		{
			return getParamNumber(flaps);
		}

		inline double getSpeedBrakes()
		{
			return getParamNumber(airbrakes);
		}

		inline double getSpoilers()
		{
			return getParamNumber(spoiler);
		}

		inline double getPitchTrim()
		{
			return getParamNumber(pitchTrim);
		}

		inline double getRollTrim()
		{
			return getParamNumber(rollTrim);
		}

		inline double getRudderTrim()
		{
			return getParamNumber(rudderTrim);
		}

		inline double getEngineThrottlePosition()
		{
			return getParamNumber(engineThrottlePosition);
		}

		inline double getBleedAir()
		{
			return getParamNumber(engineBleedAir);
		}

		inline double getIgnition()
		{
			return getParamNumber(engineIgnition);
		}

		inline bool getNWS()
		{
			return getParamNumber(nws) > 0.5;
		}

		inline double getCockpitShake()
		{
			return getParamNumber(cockpitShake);
		}

		inline double getYawDamper()
		{
			return getParamNumber(yawDamper);
		}

		inline double getRadarAltitude()
		{
			return getParamNumber(radarAltitude);
		}

		inline double getGunsightAngle()
		{
			return getParamNumber(gunsightAngle);
		}

		inline bool getDumpingFuel()
		{
			return getParamNumber(dumpingFuel) > 0.5;
		}

		inline bool getAvionicsAlive()
		{
			return getParamNumber(avionicsAlive) > 0.5;
		}

		inline double getLTankCapacity()
		{
			return getParamNumber(lTankCapacity);
		}

		inline double getCTankCapacity()
		{
			return getParamNumber(cTankCapacity);
		}

		inline double getRTankCapacity()
		{
			return getParamNumber(rTankCapacity);
		}

		inline bool getWheelBrakeAssist()
		{
			return getParamNumber(wheelBrakeAssist) > 0.5;
		}

		inline double getAltSetting()
		{
			return getParamNumber(ADC_altSetting);
		}

		void* test = NULL;

		inline void setParamNumber(void* ptr, double number)
		{
			edApi.pfn_ed_cockpit_update_parameter_with_number(ptr, number);
		}
		inline double getParamNumber(void* ptr) const
		{
			double result;
			edApi.pfn_ed_cockpit_parameter_value_to_number(ptr, result, false);
			return result;
		}

	private:
		inline void getParamString(void* ptr, char* buffer, unsigned int bufferSize) const
		{
			edApi.pfn_ed_cockpit_parameter_value_to_string(ptr, buffer, bufferSize);
		}

		inline void setParamString(void* ptr, const char* string)
		{
			edApi.pfn_ed_cockpit_update_parameter_with_string(ptr, string);
		}

		cockpit_param_api edApi;

		// void* because C isn't a typed language kek
		void* RPM = NULL;
		void* noseGear = NULL;
		void* leftGear = NULL;
		void* rightGear = NULL;
		void* flaps = NULL;
		void* spoiler = NULL;
		void* airbrakes = NULL;

		void* rudderPedals = NULL;
		void* stickRoll = NULL;
		void* stickPitch = NULL;
		void* throttlePosition = NULL;

		void* leftBrakePedal = NULL;
		void* rightBrakePedal = NULL;

		void* stickInputPitch = NULL;
		void* stickInputRoll = NULL;

		void* engineThrottlePosition = NULL;
		void* engineIgnition = NULL;
		void* engineBleedAir = NULL;

		void* rollTrim = NULL;
		void* pitchTrim = NULL;
		void* rudderTrim = NULL;

		void* nws = NULL;

		void* internalFuel = NULL;
		void* externalFuel = NULL;

		void* airspeed = NULL;

		// Radio Pointer for the Radio Device.
		void* radio = NULL;
		void* elec = NULL;
		void* intercom = NULL;
		void* radioPower = NULL;
		void* weapon = NULL;
		void* cockpitShake = NULL;

		void* yawDamper = NULL;

		void* beta = NULL;
		void* aoa = NULL;
		void* aoaUnits = NULL;

		void* setTarget = NULL;
		void* validSolution = NULL;
		void* slantRange = NULL;
		void* cp741Power = NULL;
		void* inRange = NULL;

		void* radarAltitude = NULL;
		void* gunsightAngle = NULL;
		void* targetSet = NULL;

		void* dumpingFuel = NULL;

		void* avionicsAlive = NULL;

		void* lTankCapacity = NULL;
		void* cTankCapacity = NULL;
		void* rTankCapacity = NULL;

		void* sndCockpitRattle = NULL;

		void* leftSlat = NULL;
		void* rightSlat = NULL;

		void* usingFFB = NULL;

		// Electrics
		void* fuelTransferCaution = NULL;
		void* fuelBoostCaution = NULL;

		void* elecPrimaryAC = NULL;
		void* elecPrimaryDC = NULL;
		void* elecMonitoredAC = NULL;

		void* masterTest = NULL;

		void* gForce = NULL;

		void* fuelFlow = NULL;

		void* tcnX = NULL;
		void* tcnY = NULL;
		void* tcnZ = NULL;
		void* tcnValid = NULL;
		void* tcnObjectID = NULL;
		void* tcnUnitName = NULL;

		void* mclX = NULL;
		void* mclY = NULL;
		void* mclZ = NULL;
		void* mclHeading = NULL;
		void* mclValid = NULL;
		void* mclObjectID = NULL;
		void* mclUnitName = NULL;

		void* accelerationX = NULL;
		void* accelerationY = NULL;
		void* accelerationZ = NULL;

		// ADC Variables
		void* ADC_TAS = NULL;
		void* ADC_TASX = NULL;
		void* ADC_TASZ = NULL;
		void* ADC_ALT = NULL;
		void* ADC_altSetting = NULL;
		void* ADC_MACH = NULL;

		void* chocks = NULL;

		void* averageLoadFactor = NULL;

		void* ADC_CAS = NULL;

		void* engineStall = NULL;

		void* disableRadar = NULL;
		void* wheelBrakeAssist = NULL;

		void* autoCatMode = NULL;

		void* egg = NULL;
		void* eggScore = NULL;
		void* eggHighScore = NULL;

		void* skid_l_detector = NULL;
		void* skid_r_detector = NULL;
	};

} // namepsace end
#endif
