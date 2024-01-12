#pragma once
#include "CppUnitTest.h"

#define private public
#include "../FM/airframe.h"
#include "mockedfmapi.h"
//#include "../FM/engine.h"
//#include "../FM/force.h"
//#include "../FM/vec3.h"
#include <iostream>
#include <sstream>
#define FLOAT_TOLERANCE 0.001
#define TARGET_TOLERANCE 0.1

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FMTests {
	TEST_CLASS(AirFrameTests) {
public:
	TEST_METHOD(init) {
		Aircraft::AirFrame airFrame = Aircraft::AirFrame();
	}

	};
}
