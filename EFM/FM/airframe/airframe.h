#pragma once

#ifndef AIRFRAME_H
#define AIRFRAME_H

#include "../common/vec3.h"
#include "../common/units.h"
#include "../common/utilities.h"
#include "airframedata.h"

namespace Aircraft {
    class AirFrame {
        public: 
            AirFrame();
            ~AirFrame();

            inline Vec3 getLift(double dyPre, double aoa, double mach);
            inline Vec3 getDrag(double dyPre, double aoa, double mach);
            inline Vec3 getAeroForce(double dyPre, double aoa, double mach);
            inline Vec3 getPos();

        private:

            inline void calAeroCoeffs(double mach, double aoa);
            inline void calCy(double aoa);
            inline void calCx();
            double wingArea = 29;
            double cyAlpha = 0;
            double cxZero = 0;
            double cyMax = 0;
            double b = 0;
            double b4 = 0;
            double cx = 0;
            double cy = 0;
            
            //aerodynamic center
            Vec3 pos = (1.0, 0, 0);
    };

    Vec3 AirFrame::getLift(double dyPre, double aoa, double mach) {
        //double asMag = magnitude(airspeed);
        //double mach = getMach(asMag);
        calAeroCoeffs(mach, aoa);
        //double dyPre = 0.5 * airDensity*asMag*asMag;
        return cy * dyPre * wingArea;
    }

    Vec3 AirFrame::getDrag(double dyPre, double aoa, double mach){
        //double asMag = magnitude(airspeed);
        //double mach = getMach(asMag);
        calAeroCoeffs(mach, aoa);
        //double dyPre = 0.5 * airDensity*asMag*asMag;
        return cx * dyPre * wingArea;
    }

    Vec3 AirFrame::getAeroForce(double dyPre, double aoa, double mach){
        calAeroCoeffs(mach, aoa);
        double lift = cy * dyPre * wingArea;
        double drag = cx * dyPre * wingArea;
        return (-drag, lift, 0)
    }

    void AirFrame::calAeroCoeffs(double mach, double aoa) {
        	cyAlpha = lerp(MATCH_TABLE,CYA  ,sizeof(MATCH_TABLE)/sizeof(double),mach);
	        cxZero   = lerp(MATCH_TABLE,CX0  ,sizeof(MATCH_TABLE)/sizeof(double),mach);
	        cyMax   = lerp(MATCH_TABLE,CY_MAX,sizeof(MATCH_TABLE)/sizeof(double),mach);
	        b	    = lerp(MATCH_TABLE,B    ,sizeof(MATCH_TABLE)/sizeof(double),mach);
	        b4    = lerp(MATCH_TABLE,B4   ,sizeof(MATCH_TABLE)/sizeof(double),mach);

            calCy(aoa);
            calCx();
    }

    void AirFrame::calCy(double aoa) {
        cy = cyAlpha*57.3*aoa;
        if (fabs(aoa)> 90/57.3){
            cy = 0;
        }

        if (cy> cyMax){
            cy = cyMax;
        }
    }

    void AirFrame::calCx(){
        cx =  0.05 + b*cy*cy + b4*cy*cy*cy*cy;
    }

}

#endif
