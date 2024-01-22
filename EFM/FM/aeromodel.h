#pragma once

#ifndef AIRMODEL_H
#define AIRMODEL_H

#include "vec3.h"
#include "units.h"
#include "utilities.h"
#include "aeromodeldata.h"
#include "force.h"
#include "log.h"

namespace Aircraft
{
	class AeroModel
	{
	public:
		AeroModel() {};
		~AeroModel() {};

		inline double getLiftVal(double dyPre, double aoa, double mach);
		inline double getDragVal(double dyPre, double aoa, double mach);
		inline Force getAeroForce(double dyPre, double aoa, double mach);

		inline Vec3 getPos();
		inline double getCx();
		inline double getCy();

		inline Force getLeftAlrnForce(double dyPre, double stickRoll);
		inline Force getRightAlrnForce(double dyPre, double stickRoll);

		inline Force getLeftEleForce(double dyPre, double stickPitch);
		inline Force getRightEleForce(double dyPre, double stickPitch);

		inline Force getRudderForce(double dyPre, double stickRaw);

	private:
		inline void calAeroCoeffs(double mach, double aoa);
		inline void calCy(double aoa);
		inline void calCx();
		double wingArea = 29;
		double cyAlpha = 0;
		double cxZero = 0;
		double cyMax = 0;
		double b = 0;
		double b4 = 0;
		double cx = 0;
		double cy = 0;

		// aerodynamic center
		Vec3 pos = Vec3(1.0, 0, 0);

		// control surfaces
		Vec3 leftAlrnPos = Vec3(0, 0, -5.0);
		Vec3 rightAlrnPos = Vec3(0, 0, 5.0);
		double alronArea = 5;

		Vec3 leftElePos = Vec3(0, -8, -2.0);
		Vec3 rightElePos = Vec3(0, -8, 2.0);
		double eleArea = 2;

		Vec3 rudderPos = Vec3(1, -5, 0);
		double rudderArea = 2;
	};

	double AeroModel::getLiftVal(double dyPre, double aoa, double mach)
	{
		// double asMag = magnitude(airspeed);
		// double mach = getMach(asMag);
		calAeroCoeffs(mach, aoa);
		// double dyPre = 0.5 * airDensity*asMag*asMag;
		return cy * dyPre * wingArea;
	}

	double AeroModel::getDragVal(double dyPre, double aoa, double mach)
	{
		// double asMag = magnitude(airspeed);
		// double mach = getMach(asMag);
		calAeroCoeffs(mach, aoa);
		// double dyPre = 0.5 * airDensity*asMag*asMag;
		return cx * dyPre * wingArea;
	}

	Force AeroModel::getAeroForce(double dyPre, double aoa, double mach)
	{
		calAeroCoeffs(mach, aoa);
		double lift = cy * dyPre * wingArea;
		double drag = cx * dyPre * wingArea;
		return Force(Vec3(-drag, lift, 0), pos);
	}

	void AeroModel::calAeroCoeffs(double mach, double aoa)
	{
		cyAlpha = lerp(MATCH_TABLE, CYA, sizeof(MATCH_TABLE) / sizeof(double), mach);
		cxZero = lerp(MATCH_TABLE, CX0, sizeof(MATCH_TABLE) / sizeof(double), mach);
		cyMax = lerp(MATCH_TABLE, CY_MAX, sizeof(MATCH_TABLE) / sizeof(double), mach);
		b = lerp(MATCH_TABLE, B, sizeof(MATCH_TABLE) / sizeof(double), mach);
		b4 = lerp(MATCH_TABLE, B4, sizeof(MATCH_TABLE) / sizeof(double), mach);

		calCy(aoa);
		calCx();
		LOG("calculated aero coefficients: CyAlph: %f, CxZero: %f, CyMax: %f, B: %f, B4: %f, Cy: %f, Cx: %f \n", cyAlpha, cxZero, cyMax, b, b4, cy, cx);
	}

	void AeroModel::calCy(double aoa)
	{
		cy = cyAlpha * 57.3 * aoa;
		if (fabs(aoa) > 90 / 57.3)
		{
			cy = 0;
		}

		if (cy > cyMax)
		{
			cy = cyMax;
		}
	}

	void AeroModel::calCx()
	{
		cx = 0.05 + b * cy * cy + b4 * cy * cy * cy * cy;
	}

	Vec3 AeroModel::getPos()
	{
		return pos;
	}

	double AeroModel::getCx()
	{
		return cx;
	}

	double AeroModel::getCy()
	{
		return cy;
	}

	Force AeroModel::getLeftAlrnForce(double dyPre, double stickRoll)
	{
		return Force(Vec3(0, 0.05 * cy * stickRoll * dyPre * alronArea, 0), leftAlrnPos);
	}

	Force AeroModel::getRightAlrnForce(double dyPre, double stickRoll)
	{
		return Force(Vec3(0, -0.05 * cy * stickRoll * dyPre * alronArea, 0), rightAlrnPos);
	}

	Force AeroModel::getLeftEleForce(double dyPre, double stickPitch)
	{
		return Force(Vec3(0, 0.05 * stickPitch * dyPre * eleArea, 0), leftElePos);
	}

	Force AeroModel::getRightEleForce(double dyPre, double stickPitch)
	{
		return Force(Vec3(0, 0.05 * stickPitch * dyPre * eleArea, 0), rightElePos);
	}

	Force AeroModel::getRudderForce(double dyPre, double stickRaw)
	{
		return Force(Vec3(0, 0, 0.05 * stickRaw * dyPre * eleArea), rudderPos);
	}
}

#endif
