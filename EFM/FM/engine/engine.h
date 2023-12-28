#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include "../common/vec3.h"
#include "../common/force.h"

namespace Aircraft {
    class Engine {
        public: 
            Engine() {};
            Engine(Vec3& pos_){
                pos = pos_;
            };
            ~Engine() {};

            inline Force getThrust(double throttle);
            inline Vec3 getPos();
            inline void setPos(Vec3& pos_);
            inline double getRPM(double throttle);
            inline double getRPMNorm();

        private:
            double maxThrustVal = 157000;
            Vec3 pos = (0, 0, 0);
    };

    Force Engine::getThrust(double throttle) {
        return Force((throttle * maxThrustVal, 0, 0 ), pos);
    }

    Vec3 Engine::getPos(){
        return pos;
    }

    void inline Engine::setPos(Vec3& pos_){
        pos = pos_;
    }

    double Engine::getRPM(double throttle){
        return throttle * 3000;
    }

    double Engine::getRPMNorm(){
        return  13000;
    }

}
#endif
