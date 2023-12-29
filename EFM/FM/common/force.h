#pragma once
#ifndef FORCE_H
#define FORCE_H

#include "vec3.h"

struct Force
{
	Force(const Vec3& force_, const Vec3& pos_) : force(force_), pos(pos_) {}
	Force() : force(), pos() {}

	Vec3 force;
	Vec3 pos;
};

#endif

