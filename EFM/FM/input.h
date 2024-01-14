#pragma once

#ifndef INPUT_H
#define INPUT_H

#include "axis.h"

namespace Aircraft
{

	enum Control
	{
		// Axis
		PITCH = 2001,	  // Stick pitch axis
		ROLL = 2002,	  // Stick roll axis
		YAW = 2003,		  // Pedals yaw axis
		THROTTLE = 2004,  // Throttle axis
		GEAR_TOGGLE = 68, // 68
		GEAR_UP = 430,	  //
		GEAR_DOWN = 431,  //
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

		// Keyboard Stuff,
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
		RADIO_MENU = 179, // iCommandToggleCommandMenu
		RADIO_PTT = 10179,

		// If the comms menu is changed these need to be found again.
		LOCK_SLATS_RADIO_MENU = 966,
		UNLOCK_SLATS_RADIO_MENU = 967,
	};

	class Input
	{
	public:
		Input() : thrtAxis(0.015, -1, 1, 0, 1),
			pitchAxis(0.015, -1, 1, 0, 1),
			rollAxis(0.015, -1, 1, 0, 1),
			yawAxis(0.015, -1, 1, 0, 1),
			leftBrkAxis(0.02, 0, 1, 0, 0),
			rightBrkAxis(0.02, 0, 1, 0, 0)
		{
		}
		~Input() {}

		inline void setThrt(double thrt);
		inline void startThrtUp();
		inline void startThrtDown();
		inline void stopThrtMove();

		inline void setStickPitch(double pitch);
		inline void resetStickPitch();
		inline void stopStickPitch();
		inline void startPitchUp();
		inline void startPitchDown();

		inline void setStickRoll(double roll);
		inline void resetStickRoll();
		inline void stopStickRoll();
		inline void startRollLeft();
		inline void startRollRight();

		inline void setPedalYaw(double yaw);
		inline void resetPedalYaw();
		inline void stopPedalYaw();
		inline void startYawLeft();
		inline void startYawRight();

		inline double getThrottle();
		inline double getStickPitch();
		inline double getStickRoll();
		inline double getPedalYaw();
		inline void update();

		static inline double normalise(double value)
		{
			return (value + 1.0) / 2.0;
		}

		double getLeftBrk() const
		{
			return leftBrkAxis.getValue();
		}

		inline const double& setLeftBrk() const
		{
			// Fade the brake linearly based on rudder position.
			return (1.0 - clamp(yawAxis.getValue(), 0.0, 1.0)) * leftBrkAxis.getValue();
		}

		void setLeftBrk(double value)
		{
			leftBrkAxis.updateAxis(normalise(-value));
		}

		double getYawDamper() const { return yawDamper; }

		double getRightBrk() const
		{
			return rightBrkAxis.getValue();
		}

		inline const double& setRightBrk() const
		{
			// Fade the brake linearly based on rudder position.
			return (1.0 - clamp(yawAxis.getValue(), -1.0, 0.0)) * rightBrkAxis.getValue();
		}

		void setRightBrk(double value)
		{
			rightBrkAxis.updateAxis(normalise(-value));
		}

		double getPitchTrim() const { return pitchTrim; }

		double getRollTrim() const { return rollTrim; }

		double getYawTrim() const { return yawTrim; }

	private:
		Axis thrtAxis = Axis();
		Axis pitchAxis = Axis();
		Axis rollAxis = Axis();
		Axis yawAxis = Axis();
		Axis leftBrkAxis = Axis();
		Axis rightBrkAxis = Axis();

		double throttle = 0;
		double stickPitch = 0;
		double stickRoll = 0;
		double pedalYaw = 0;
		double leftBrk = 0;
		double rightBrk = 0;
		double yawDamper = 0;
		double pitchTrim = 0;
		double rollTrim = 0;
		double yawTrim = 0;
	};

	void Input::setThrt(double thrt)
	{
		thrtAxis.updateAxis(thrt);
	}

	void Input::startThrtUp()
	{
		thrtAxis.keyDecrease();
	}

	void Input::startThrtDown()
	{
		thrtAxis.keyIncrease();
	}

	void Input::stopThrtMove()
	{
		thrtAxis.stop();
	}

	void Input::setStickPitch(double pitch)
	{
		pitchAxis.updateAxis(pitch);
	}

	void Input::resetStickPitch()
	{
		pitchAxis.reset();
	}

	void Input::stopStickPitch()
	{
		pitchAxis.stop();
	}

	void Input::startPitchUp()
	{
		pitchAxis.keyIncrease();
	}

	void Input::startPitchDown()
	{
		pitchAxis.keyDecrease();
	}

	void Input::setStickRoll(double roll)
	{
		rollAxis.updateAxis(roll);
	}

	void Input::resetStickRoll()
	{
		rollAxis.reset();
	}

	void Input::stopStickRoll()
	{
		rollAxis.stop();
	}

	void Input::startRollLeft()
	{
		rollAxis.keyDecrease();
	}

	void Input::startRollRight()
	{
		rollAxis.keyIncrease();
	}

	void Input::setPedalYaw(double yaw)
	{
		yawAxis.updateAxis(yaw);
	}

	void Input::resetPedalYaw()
	{
		yawAxis.reset();
	}

	void Input::stopPedalYaw()
	{
		yawAxis.stop();
	}

	void Input::startYawLeft()
	{
		yawAxis.keyDecrease();
	}

	void Input::startYawRight()
	{
		yawAxis.keyIncrease();
	}

	double Input::getThrottle()
	{
		return thrtAxis.getValue();
	}

	double Input::getStickPitch()
	{
		return pitchAxis.getValue();
	}

	double Input::getStickRoll()
	{
		return rollAxis.getValue();
	}

	double Input::getPedalYaw()
	{
		return yawAxis.getValue();
	}

	void Input::update()
	{
		pitchAxis.update();
		rollAxis.update();
		yawAxis.update();
		thrtAxis.update();
		leftBrkAxis.update();
		rightBrkAxis.update();
	};

}

#endif // INPUT_H
