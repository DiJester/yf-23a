#pragma once

#ifndef AXIS_H
#define AXIS_H

#include "maths.h"

class Axis
{

public:
	Axis(double sensitivity, double min, double max, double resetVal, double linear) : sensitivity(sensitivity),
		min(min),
		max(max),
		resetVal(resetVal),
		linear(linear)
	{
	}
	Axis() : sensitivity(0),
		min(0),
		max(0),
		resetVal(0),
		linear(0)
	{
	}
	~Axis() {}
	inline void update();
	inline void updateAxis(double axis);
	inline void keyIncrease();
	inline void keyDecrease();
	inline void reset();
	inline void slowResetx();
	inline void stop();
	inline const double getValue() const;

private:
	double value = 0.0;
	int dir = 0;
	bool slowReset = false;

	const double sensitivity;
	const double min;
	const double max;
	const double resetVal;
	const double linear;
};

void Axis::updateAxis(double axis)
{
	value = axis;
	dir = 0;
}

void Axis::stop()
{
	dir = 0;
	slowReset = false;
}

void Axis::reset()
{
	value = resetVal;
	dir = 0;
	slowReset = false;
}

void Axis::slowResetx()
{
	dir = (int)copysign(1.0, resetVal - value);
	slowReset = true;
}

void Axis::keyIncrease()
{
	if (slowReset)
		dir = 0;

	dir += 1;
	slowReset = false;
}

void Axis::keyDecrease()
{
	if (slowReset)
		dir = 0;

	dir -= 1;
	slowReset = false;
}

const double Axis::getValue() const
{
	return value;
}

void Axis::update()
{
	value += sensitivity * (double)dir * (0.2 + fabs(value) * linear);
	value = clamp(value, min, max);

	if (slowReset)
	{
		int sign = (int)copysign(1.0, resetVal - value);

		if (sign != dir)
		{
			dir = 0;
			value = resetVal;
			slowReset = false;
		}
	}
}

#endif // AXIS_H
