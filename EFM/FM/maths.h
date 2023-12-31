#pragma once
//=========================================================================//
//
//		FILE NAME	: Maths.h
//		AUTHOR		: TerjeTL
//		DATE		: October 2020
//
//		This file falls under the licence found in the root ExternalFM directory.
//
//		DESCRIPTION	:	Utility maths functions.
//
//================================ Includes ===============================//
#include <math.h>
#include "vec3.h"
#include <algorithm>
//=========================================================================//

// To stop silly macros.
#undef max
#undef min

#define PI 3.14159265359

static double toDegrees(double radians)
{
	return radians * 180.0 / PI;
}

static double toRad(double degrees)
{
	return degrees * PI / 180.0;
}

static double clamp(double value, double min, double max)
{
	return std::max(std::min(value, max), min);
}

// Weight goes from 0 -> 1
static double lerpWeight(double v0, double v1, double w)
{
	return v0 + w * (v1 - v0);
}

static double random()
{
	return (double)(rand() % 100) / 100.0;
}

static double randomCentred()
{
	return 2.0 * random() - 1.0;
}

const Vec3 rotateVectorIntoXYPlane(const Vec3& v)
{
	Vec3 result;
	double d = sqrt(v.x * v.x + v.z * v.z);
	result.x = (v.x * v.x + v.z * v.z) / d;
	result.y = v.y;
	result.z = 0.0;
	return result;
}

const Vec3 rotate(const Vec3& v, const double pitch, const double yaw)
{
	double sin_b = sin(yaw);
	double cos_b = cos(yaw);
	double sin_a = sin(pitch);
	double cos_a = cos(pitch);

	double res_x = cos_b * cos_a * v.x + sin_b * v.z - cos_b * sin_a * v.y;
	double res_z = -cos_a * sin_b * v.x + cos_b * v.z + sin_a * sin_b * v.y;
	double res_y = sin_a * v.x + cos_a * v.y;

	return Vec3(res_x, res_y, res_z);
}

const Vec3 windAxisToBody(const Vec3& force, const double& alpha, const double& beta)
{
	return rotate(force, -alpha, beta);
}

const Vec3 directionVector(const double pitch, const double yaw)
{
	double cosPitch = cos(pitch);
	double sinPitch = sin(pitch);
	double cosYaw = cos(yaw);
	double sinYaw = sin(-yaw);

	Vec3 newV;
	newV.x = cosYaw * cosPitch;
	newV.z = sinYaw * cosPitch;
	newV.y = sinPitch;

	return normalize(newV);
}
