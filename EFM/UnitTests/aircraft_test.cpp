#pragma once

#ifndef FM_TESTS
#define FM_TESTS
#endif

#include "CppUnitTest.h"

#define private public
#include "mockedfmapi.h"
//#include "../FM/engine.h"
#include "../FM/force.h"
#include "../FM/vec3.h"
#include <iostream>
#include <sstream>
#define FLOAT_TOLERANCE 0.001
#define TARGET_TOLERANCE 0.1

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FMTests{
	TEST_CLASS(AircraftTests) {
	public:
		TEST_METHOD(init) {
			ed_fm_set_plugin_data_install_path("../temp/test/");
			ed_fm_set_atmosphere(10,100,340, 9.7,19001,1,1,1);
			ed_fm_set_surface(1,2,1,2,3,4);
			ed_fm_set_current_state(0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0);
			ed_fm_set_current_mass_state(15000, 0,0,0,0,0,0);
			ed_fm_set_current_state_body_axis(0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0.1,0);
			ed_fm_set_internal_fuel(1000.0);
			Assert::AreEqual(1000.0,ed_fm_get_internal_fuel(), L"Internal fuel not filled correctly.");
			ed_fm_set_command(2004, 0.8);
			ed_fm_simulate(5);

			double dMass = 0;
			Vec3 dCG = Vec3();
			Vec3 dMoment = Vec3();
			ed_fm_change_mass(dMass, dCG.x, dCG.y, dCG.z, dMoment.x,dMoment.y, dMoment.z);

			Force force = Force();
			ed_fm_add_local_force(force.force.x, force.force.y, force.force.z, force.pos.x, force.pos.y, force.pos.z);

			Vec3 moment = Vec3();
			ed_fm_add_local_moment(moment.x,moment.y, moment.z);

			ed_fm_release();
			
		}
	};
}
