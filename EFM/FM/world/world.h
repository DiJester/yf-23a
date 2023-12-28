#pragma once

#ifndef WORLD_H
#define WORLD_H

#include "../common/vec3.h"

namespace Aircraft {
	class World {
        public:
            World() {};
            ~World() {};

            Vec3 getWind() const { return wind; }
            void setWind(const Vec3 &wind_) { wind = wind_; }

            double getAtmTemp() const { return atmTemp; }
            void setAtmTemp(double atmTemp_) { atmTemp = atmTemp_; }

            double getAtmDensity() const { return atmDensity; }
            void setAtmDensity(double atmDensity_) { atmDensity = atmDensity_; }

            double getAtmPre() const { return atmPre; }
            void setAtmPre(double atmPre_) { atmPre = atmPre_; }

            double getSoundSpeed() const { return soundSpeed; }
            void setSoundSpeed(double soundSpeed_) { soundSpeed = soundSpeed_; }

            double getAltitude() const { return altitude; }
            void setAltitude(double altitude_) { altitude = altitude_; }

            Vec3 getPos() const { return pos; }
            void setPos(const Vec3 &pos_) { pos = pos_; }

            Vec3 getVelocity() const { return velocity; }
            void setVelocity(const Vec3 &velocity_) { velocity = velocity_; }

            Vec3 getDirection() const { return direction; }
            void setDirection(const Vec3 &direction_) { direction = direction_; }

            Vec3 getGlobalDown() const { return globalDown; }
            void setGlobalDown(const Vec3 &globalDown_) { globalDown = globalDown_; }
        
        private:
            Vec3 wind = (0,0,0);
            double atmTemp = 0; // Kelwins
            double atmDensity = 0;
            double atmPre = 0;
            double soundSpeed = 0; 
            double altitude = 0;

            Vec3 pos = (0,0,0);
            Vec3 velocity = (0,0,0);
            Vec3 direction = (0,0,0);
            Vec3 globalDown = (0,0,0);

    };
};

#endif // WORLD_H
