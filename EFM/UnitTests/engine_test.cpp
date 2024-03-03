#pragma once
#include "CppUnitTest.h"

#define private public
#include "../FM/engine2.h"
#include <iostream>
#include <sstream>
#define FLOAT_TOLERANCE 0.001
#define TARGET_TOLERANCE 0.1

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FMTests {
	TEST_CLASS(EngineTests) {
public:
	TEST_METHOD(initengine) {
		Aircraft::Engine2 engine = Aircraft::Engine2();
		engine.simulate(1, 100, 2116, 518.6, 0, 0);
		double thrust = engine.getThrustVal();
		double fuelrate = engine.getFuelRate();
		Assert::IsTrue(thrust > 156000 && thrust < 157000, L"Engine Thrust not simulated correctly");
		Assert::IsTrue(fuelrate > 19800 && fuelrate < 19900, L"Engine Fuelrate not simulated correctly");
	}
	};
}
