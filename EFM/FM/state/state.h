#pragma once

#ifndef STATE_H
#define STATE_H
#include "../common/vec3.h"
#include "../common/force.h"

namespace Aircraft {
	class State {
		public:
			State() {};
			~State() {};

			double getAoa() const { 
				return aoa;
			}

			void setAoa(double aoa_) { 
				aoa = aoa_;
			}

			Vec3 getCg() const { 
				return cg; 
			}

			void setCg(const Vec3 &cg_) { 
				cg = cg_;
			}

			Vec3 getAirspeed() const { 
				return airspeed;
			}

			void setAirspeed(const Vec3 &airspeed_) { 
				airspeed = airspeed_;
			}

			Vec3 getMoment() const { 
				return moment;
			}

			void setMoment(const Vec3 &moment_) { 
				moment = moment_;
			}

			Vec3 getForce() const { 
				return force; 
			}

			void setForce(const Vec3 &force_) { 
				force = force_; 
			}

			inline void addForce(const Force &force_);

			double getMach() const { return mach; }
			void setMach(double mach_) { mach = mach_; }

			double getDyPre() const { return dyPre; }
			void setDyPre(double dyPre_) { dyPre = dyPre_; }

			double getMass() const { return mass; }
			void setMass(double mass_) { mass = mass_; }

			double getAos() const { return aos; }
			void setAos(double aos_) { aos = aos_; }

			Vec3 getAngle() const { return angle; }
			void setAngle(const Vec3 &angle_) { angle = angle_; }

			Vec3 getAngAcc() const { return angAcc; }
			void setAngAcc(const Vec3 &angAcc_) { angAcc = angAcc_; }

			Vec3 getAngVelo() const { return angVelo; }
			void setAngVelo(const Vec3 &angVelo_) { angVelo = angVelo_; }

			Vec3 getLocalSpeed() const { return localSpeed; }
			void setLocalSpeed(const Vec3 &localSpeed_) { localSpeed = localSpeed_; }

			Vec3 getAccel() const { return accel; }
			void setAccel(const Vec3 &accel_) { accel = accel_; }
		
		private:
			double aoa = 0;
			double aos = 0;
			Vec3 angle = (0,0,0);
			Vec3 angAcc = (0,0,0);
			Vec3 angVelo = (0,0,0);

			Vec3 localSpeed = (0,0,0);
			Vec3 airspeed = (0,0,0);
			Vec3 accel = (0,0,0);


			double mach = 0;
			double dyPre = 0;
			double mass = 0;
			
			Vec3 cg = (0, 0, 0);
			Vec3 moment = (0,0,0);
			Vec3 force =  (0,0,0);

	};

	void State::addForce(const Force &force_){
		force = force + force_.force;
		Vec3 deltaPos = force_.pos - cg;
		Vec3 deltaMoment = cross(deltaPos, force_.force);

		moment = moment + deltaMoment;
	}
};

#endif // STATE_H
