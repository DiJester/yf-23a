#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include "vec3.h"
#include "force.h"
#include "enginedata.h"

namespace Aircraft
{
	class Engine
	{
	public:
		Engine() {};
		Engine(Vec3& pos_)
		{
			pos = pos_;
		};
		~Engine() {};

		inline Force getThrust(double throttle);
		inline double getThrustNorm(double throttle);
		inline double getThrustVal(double throttle);
		inline Vec3 getPos();
		inline void setPos(Vec3& pos_);
		inline double getRPM(double throttle);
		inline double getRPMNorm(double throttle);

	private:
		double maxThrustVal = ENGINE_THRUST_MAX;
		Vec3 pos = (0, 0, 0);
	};

	Force Engine::getThrust(double throttle)
	{
		return Force((throttle * maxThrustVal, 0, 0), pos);
	}

	double Engine::getThrustVal(double throttle)
	{
		return throttle * maxThrustVal;
	}

	Vec3 Engine::getPos()
	{
		return pos;
	}

	void inline Engine::setPos(Vec3& pos_)
	{
		pos = pos_;
	}

	double Engine::getRPM(double throttle)
	{
		return throttle * 3000;
	}

	double Engine::getRPMNorm(double throttle)
	{
		return getRPM(throttle) / ENGINE_RPM_MAX;
	}

	double Engine::getThrustNorm(double throttle)
	{
		return getThrustVal(throttle) / ENGINE_THRUST_MAX;
	}

}
#endif
