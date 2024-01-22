#pragma once

#ifndef ACTUATOR_H
#define ACTUATOR_H

#include "maths.h"
#include <cmath>

namespace Aircraft
{
	class Actuator
	{
	public:
		Actuator() {}
		Actuator(double speed) : speed(speed) {}
		~Actuator() {}

		inline double inputUpdate(double targetPos, double dt);
		inline void physicsUpdate(double dt);
		inline double getPosition();
		inline void setActuatorFactor(double factor);

		void setSpeed(double speed_) { speed = speed_; }

		double getPos() const { return pos; }

	private:
		double factor = 1;
		double speed = 10;
		double pos = 0;
		double targetPos = 0;
	};

	double Actuator::getPosition()
	{
		return pos;
	}

	void Actuator::setActuatorFactor(double factor)
	{
		factor = factor;
	}

	double Actuator::inputUpdate(double targetPos_, double dt)
	{
		targetPos = targetPos_;
		physicsUpdate(dt);
		return pos;
	}

	void Actuator::physicsUpdate(double dt)
	{
		double reqSpd = (targetPos - pos) / dt;
		double actSpd = 0;
		if (pos > 0)
		{
			if (targetPos - pos < 0)
			{
				actSpd = speed;
			}
			else
			{
				actSpd = speed * factor;
			}
		}
		else
		{
			if (targetPos - pos > 0)
			{
				actSpd = speed;
			}
			else
			{
				actSpd = speed * factor;
			}
		}

		if (abs(reqSpd) <= actSpd)
		{
			pos = targetPos;
		}
		else
		{
			pos += copysign(1.0, reqSpd) * actSpd * dt;
		}

		pos = clamp(pos, -1, 1);
	}
}
#endif // ACTUATOR_H
