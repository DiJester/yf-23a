#pragma once
#ifndef INPUT_H
#define INPUT_H

namespace Aircraft {

enum Control {
	//Axis
	PITCH = 2001, //Stick pitch axis
	ROLL = 2002, //Stick roll axis
	YAW = 2003, //Pedals yaw axis
	THROTTLE = 2004, //Throttle axis
	GEAR_TOGGLE = 68, //68
	GEAR_UP = 430, //
	GEAR_DOWN = 431, //
	BRAKE = 2111,
	LEFT_BRAKE = 3162,
	RIGHT_BRAKE = 3163,
	FLAPS_INCREASE = 10001,
	FLAPS_DECREASE = 10002,
	FLAPS_DOWN = 145,
	FLAPS_UP = 146,
	FLAPS_TOGGLE = 72,
	AIRBRAKE_EXTEND = 147,
	AIRBRAKE_RETRACT = 148,
	HOOK_TOGGLE = 69,
	CONNECT_TO_CAT = 120,
	NOSEWHEEL_STEERING_ENGAGE = 3133,
	NOSEWHEEL_STEERING_DISENGAGE = 3134,
	STARTER_BUTTON = 3013,
	THROTTLE_DETEND = 3087,

	//Keyboard Stuff,
	RUDDER_LEFT_START = 201,
	RUDDER_LEFT_STOP = 202,
	RUDDER_RIGHT_START = 203,
	RUDDER_RIGHT_STOP = 204,

	ROLL_LEFT_START = 197,
	ROLL_LEFT_STOP = 198,
	ROLL_RIGHT_START = 199,
	ROLL_RIGHT_STOP = 200,

	PITCH_DOWN_START = 193,
	PITCH_DOWN_STOP = 194,
	PITCH_UP_START = 195,
	PITCH_UP_STOP = 196,

	THROTTLE_UP_START = 1032,
	THROTTLE_STOP = 1034,
	THROTTLE_DOWN_START = 1033,

	BRAKE_ALL_START = 10135,
	BRAKE_ALL_STOP = 10136,
	BRAKE_LEFT_START = 10180,
	BRAKE_LEFT_STOP = 10181,
	BRAKE_RIGHT_START = 10182,
	BRAKE_RIGHT_STOP = 10183,
	RADIO_MENU = 179, //iCommandToggleCommandMenu
	RADIO_PTT = 10179,

	//If the comms menu is changed these need to be found again.
	LOCK_SLATS_RADIO_MENU = 966,
	UNLOCK_SLATS_RADIO_MENU = 967,
};

    class Input {
        public:
            Input();
            ~Input();

            inline void setThrottle(double thrt);
            inline void setStickPitch(double pitch);
            inline void setStickRoll(double roll);
            inline void setPedalYaw(double yaw);

            inline double getThrottle();
            inline double getStickPitch();
            inline double getStickRoll();
            inline double getPedalYaw();

        private:
            double throttle = 0;
            double stickPitch = 0;
            double stickRoll = 0;
            double pedalYaw = 0;
    };

    void Input::setThrottle(double thrt){
        throttle = thrt;
    }

    void Input::setStickPitch(double pitch){
        stickPitch = pitch;
    }

    void Input::setStickRoll(double roll){
        stickRoll = roll;
    }

    void Input::setPedalYaw(double yaw) {
        pedalYaw = yaw;
    }


    double Input::getThrottle(){
        return throttle;
    }

    double Input::getStickPitch(){
        return stickPitch;
    }

    double Input::getStickRoll(){
        return stickRoll;
    }

    double Input::getPedalYaw(){
        return pedalYaw;
    }
}

#endif
