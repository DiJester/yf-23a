#pragma once

#ifndef FLIGHTCONTROL_H
#define FLIGHTCONTROL_H

#include "../common/vec3.h"
#include "../common/force.h"

namespace Aircraft{
    class FlightControl {
        public:
            FlightControl() {};
            ~FlightControl() {};

            inline Vec3 getLeftAlrnPos();
            inline Vec3 getRightAlrnPos();
            
            inline Vec3 getLeftElePos();
            inline Vec3 getRightElePos();
            inline Vec3 getRudderPos();

            inline Force getLeftAlrnForce(double cy, double dyPre, double stickRoll);
            inline Force getRightAlrnForce(double cy, double dyPre, double stickRoll);

            inline Force getLeftEleForce(double dyPre, double stickPitch);
            inline Force getRightEleForce(double dyPre, double stickPitch);

            inline Force getRudderForce(double dyPre, double stickRaw);

            double getLeftAlrnDflt() const { return leftAlrnDflt; }
            void setLeftAlrnDflt(double leftAlrnDflt_) { leftAlrnDflt = leftAlrnDflt_; }

            double getRightAlrnDflt() const { return rightAlrnDflt; }
            void setRightAlrnDflt(double rightAlrnDflt_) { rightAlrnDflt = rightAlrnDflt_; }

            double getLeftEleDflt() const { return leftEleDflt; }
            void setLeftEleDflt(double leftEleDflt_) { leftEleDflt = leftEleDflt_; }

            double getRightEleDflt() const { return rightEleDflt; }
            void setRightEleDflt(double rightEleDflt_) { rightEleDflt = rightEleDflt_; }

            double getRudderDflt() const { return rudderDflt; }
            void setRudderDflt(double rudderDflt_) { rudderDflt = rudderDflt_; }
        
        private:
            Vec3 leftAlrnPos = (0,0,-5.0);
            double leftAlrnDflt = 0.0;

            Vec3 rightAlrnPos = (0,0,5.0);
            double rightAlrnDflt = 0.0;
            
            double alronArea = 5;

            Vec3 leftElePos = (0,-8,-2.0);
            double leftEleDflt = 0.0;

            Vec3 rightElePos = (0,-8,2.0);
            double rightEleDflt = 0.0;

            double eleArea = 2;

            Vec3 rudderPos = (1, -5, 0);
            double rudderDflt = 0.0;
            double rudderArea = 2;

    };

    Vec3 FlightControl::getLeftAlrnPos(){
        return leftAlrnPos;
    }

    Vec3 FlightControl::getRightAlrnPos(){
        return rightAlrnPos;
    }

    Vec3 FlightControl::getLeftElePos(){
        return leftElePos;
    }

    Vec3 FlightControl::getRightElePos(){
        return rightElePos;
    }

    Vec3 FlightControl::getRudderPos(){
        return rudderPos;
    }

    Force FlightControl::getLeftAlrnForce(double cy, double dyPre, double stickRoll){
        return Force((0, 0.05 * cy * stickRoll * dyPre * alronArea, 0), leftAlrnPos);
    }

    Force FlightControl::getRightAlrnForce(double cy, double dyPre, double stickRoll){
        return Force((0, -0.05* cy* stickRoll*dyPre*alronArea, 0),rightAlrnPos);
    }

    Force FlightControl::getLeftEleForce(double dyPre, double stickPitch){
        return Force((0, 0.05 * stickPitch * dyPre * eleArea, 0), leftElePos);
    }

    Force FlightControl::getRightEleForce(double dyPre, double stickPitch){
        return Force((0, 0.05 * stickPitch * dyPre * eleArea, 0), rightElePos);
    }

    Force FlightControl::getRudderForce(double dyPre, double stickRaw){
        return Force((0, 0, 0.05 * stickRaw * dyPre * eleArea), rudderPos);
    }

}

#endif
