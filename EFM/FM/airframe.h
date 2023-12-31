#pragma once

#ifndef AIRFRAME_H
#define AIRFRAME_H

#include "vec3.h"
#include "force.h"
#include "actuator.h"
#include <algorithm>

namespace Aircraft
{
	class AirFrame
	{
	public:
		AirFrame() {};
		~AirFrame() {};

		Actuator getActLeftEle() const { return actLeftEle; }

		void updateActEle(double dt, double mach, double pitch)
		{
			double stabDflt = toDegrees(stabilizer);
			double bungeeTrimDeg = (stabDflt + 1.0) / (-13.25) * (-0.65306 - 7.3469) - 0.65306;
			double bungeeTrimStick = bungeeTrimDeg / 20.0; // transformation from control surface deflection to stick normalized coordinate goes here
			double speedbrakeTrim = -0.15 * spdBrkPos;
			double eleSpd = clamp(1.0 - 1.2 * pow(mach, 3.0), 0.1, 1.0);
			actLeftEle.setActuatorFactor(eleSpd);
			actRightEle.setActuatorFactor(eleSpd);
			// printf("factor: %lf\n", clamp(1.0 - 1.2 * pow(m_state.getMach(), 3.0), 0.1, 1.0));

			double eleZeroForceDflt = bungeeTrimStick + speedbrakeTrim;
			double input = pitch + eleZeroForceDflt;
			leftElePos = actLeftEle.inputUpdate(input, dt);
			rightElePos = actRightEle.inputUpdate(input, dt);
		}

		double getStabilizer() const { return stabilizer; }

		void updateStabilizer(double dt, double ptichTrim)
		{
			stabilizer = toRad((ptichTrim - 1.0) / (-2.0) * (-13.25) + 12.25);
		}

		double getSpdBrkPos() const { return spdBrkPos; }
		void setSpdBrkPos(double spdBrkPos_) { spdBrkPos = spdBrkPos_; }

		void updateActLeftAlrn(double dt, double roll, double rollTrim)
		{
			double input = roll + rollTrim;
			leftAlrnPos = actLeftAlrn.inputUpdate(-input, dt);
		}

		void updateActRightAlrn(double dt, double roll, double rollTrim)
		{
			double input = roll + rollTrim;
			rightAlrnPos = actRightAlrn.inputUpdate(input, dt);
		}

		void updateActRudder(double dt, double yaw, double yawDamper, double yawTrim)
		{
			double input = yaw + yawDamper + yawTrim;
			rudderPos = actRudder.inputUpdate(input, dt);
		}

		double getLeftAlrnPos() const { return leftAlrnPos; }

		double getRightAlrnPos() const { return rightAlrnPos; }

		double getLeftElePos() const { return leftElePos; }

		double getRightElePos() const { return rightElePos; }

		double getRudderPos() const { return rudderPos; }

		double getStabAnim() const
		{
			double stab = toDegrees(stabilizer);
			if (stab > 0.0)
			{
				return stab / 12.25;
			}
			else
			{
				return stab;
			}
		}

		double getLeftSltPos() const { return leftSltPos; }
		void setLeftSltPos(double leftSltPos_) { leftSltPos = leftSltPos_; }

		double getRightSltPos() const { return rightSltPos; }
		void setRightSltPos(double rightSltPos_) { rightSltPos = rightSltPos_; }

		double getLeftFlpPos() const { return leftFlpPos; }
		void setLeftFlpPos(double leftFlpPos_) { leftFlpPos = leftFlpPos_; }

		double getRightFlpPos() const { return rightFlpPos; }
		void setRightFlpPos(double rightFlpPos_) { rightFlpPos = rightFlpPos_; }

		void simulate(double dt, double mach, double pitch, double pitchTrim, double roll, double rollTrim, double yaw, double yawDamper, double yawTrim)
		{
			updateWheels(dt);
			updateStabilizer(dt, pitchTrim);
			updateActEle(dt, mach, pitch);
			updateActLeftAlrn(dt, roll, rollTrim);
			updateActRudder(dt, yaw, yawDamper, yawTrim);
		}

		void updateWheels(double dt)
		{
			static constexpr double whlRdus = 0.609;
			static constexpr double whlfctr = 2.0 * PI * whlRdus;
			leftWhlSpd = whlfctr * calWhlArgChange(leftWhlArg, leftWhlPreArg) / dt;
			rightWhlSpd = whlfctr * calWhlArgChange(rightWhlArg, rightWhlPreArg) / dt;

			leftWhlPreArg = leftWhlArg;
			rightWhlPreArg = rightWhlArg;

			const Vec3 noseWhlVct = noseWhlForce.pos - pivotPos;
			const Vec3 noseTq = cross(noseWhlVct, noseWhlForce.force);
			const double dmpTq = noseWhlAngV * noseWhlDmp;
			const double tqSign = copysign(1.0, noseTq.y);
			static constexpr double maxBrkOutSpd = 0.1; // m/s
			const double weight = clamp(noseWhlGS / maxBrkOutSpd, 0.0, 1.0);
			const double brkOutTq = lerpWeight(brkOutTq, 0.0, weight);
			const double tqAftBrkOut = tqSign * std::max(abs(noseTq.y) - brkOutTq, 0.0);
			const double tqTotal = tqAftBrkOut - dmpTq;
			noseWhlAngV += tqTotal * dt;
			noseWhlAng += noseWhlAngV * dt;
		}

		double getLeftGrPos() const { return leftGrPos; }
		void setLeftGrPos(double leftGrPos_) { leftGrPos = leftGrPos_; }

		double getRightGrPos() const { return rightGrPos; }
		void setRightGrPos(double rightGrPos_) { rightGrPos = rightGrPos_; }

		double getNoseGrPos() const { return noseGrPos; }
		void setNoseGrPos(double noseGrPos_) { noseGrPos = noseGrPos_; }

		static double calWhlArgChange(double arg, double preArg)
		{
			double dltUpper = (1.0 - preArg) + arg;
			double dltLower = (arg - preArg);

			if (abs(dltUpper) < abs(dltLower))
				return dltUpper;
			else
				return dltLower;
		}

		void setRightWhlArg(double rightWhlArg_) { rightWhlArg = rightWhlArg_; }

		void setLeftWhlArg(double leftWhlArg_) { leftWhlArg = leftWhlArg_; }

		void setNoseWhlForce(const Force& noseWhlForce_) { noseWhlForce = noseWhlForce_; }

		double getNoseWhlAng() const { return noseWhlAng; }

		double getNoseWhlGS() const { return noseWhlGS; }
		void setNoseWhlGS(double noseWhlGS_) { noseWhlGS = noseWhlGS_; }

		double getLeftWhlComp() const { return leftWhlComp; }
		void setLeftWhlComp(double leftWhlComp_) { leftWhlComp = leftWhlComp_; }

		double getRightWhlComp() const { return rightWhlComp; }
		void setRightWhlComp(double rightWhlComp_) { rightWhlComp = rightWhlComp_; }

		double getNoseWhlComp() const { return noseWhlComp; }
		void setNoseWhlComp(double noseWhlComp_) { noseWhlComp = noseWhlComp_; }

		double getLeftWhlGS() const { return leftWhlGS; }
		void setLeftWhlGS(double leftWhlGS_) { leftWhlGS = leftWhlGS_; }

		double getRightWhlGS() const { return rightWhlGS; }
		void setRightWhlGS(double rightWhlGS_) { rightWhlGS = rightWhlGS_; }

	private:
		// Control Surfaces
		double stabilizer = 0.0;
		Actuator actLeftAlrn{};
		double leftAlrnPos = 0.0;

		Actuator actRightAlrn{};
		double rightAlrnPos = 0.0;

		Actuator actLeftEle{};
		double leftElePos = 0.0;

		Actuator actRightEle{};
		double rightElePos = 0.0;

		Actuator actRudder{};
		double rudderPos = 0.0;

		// Speed Brake
		double spdBrkPos = 0.0;

		// Flaps
		double leftFlpPos = 0.0;
		double rightFlpPos = 0.0;

		// Slats
		double leftSltPos = 0.0;
		double rightSltPos = 0.0;

		// Gears
		double leftGrPos = 0.0;
		double rightGrPos = 0.0;
		double noseGrPos = 0.0;

		// Wheels
		double leftWhlArg = 0.0;
		double leftWhlPreArg = 0.0;
		double leftWhlSpd = 0.0;
		double leftWhlGS = 0.0;
		double leftWhlComp = 0.0;

		double rightWhlArg = 0.0;
		double rightWhlPreArg = 0.0;
		double rightWhlSpd = 0.0;
		double rightWhlGS = 0.0;
		double rightWhlComp = 0.0;

		double noseWhlGS = 0.0;
		double noseWhlComp = 0.0;
		Force noseWhlForce = Force{};
		double noseWhlAng = 0.0;
		double noseWhlAngV = 0.0;
		static constexpr double noseWhlMass = 10.0;
		static constexpr double noseWhlDmp = 150;

		static constexpr double brkOutTq = 200;
		Vec3 pivotPos = Vec3{ 2.696969, -2.271201, 0.0 };
	};
}

#endif
