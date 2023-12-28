#pragma once
#ifndef UNITS_H
#define UNITS_H

static double SPEED_OF_SOUND = 320;

double getMach(double speed) {
    return speed/SPEED_OF_SOUND;
}

double getAirSpeed(double mach){
    return mach*SPEED_OF_SOUND;
}

#endif
