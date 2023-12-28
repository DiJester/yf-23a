#pragma once
#ifndef FUELSYS_H
#define FUELSYS_H

#include "../common/vec3.h"

namespace Aircraft {
    class FuelSys {
        public:
            FuelSys() {
            }

            ~FuelSys() {
            };

            inline void simulate(double dt, double throttle);

            inline void setInternalFuel(double fuel);
            inline void setFuelFlow(double ff);
            
            inline double getInternalFuel();
            inline double getFuelFlow();

            inline double getFuelQtyDelta() const;

            Vec3 getPos() const { return pos; }
            void setPos(const Vec3 &pos_) { pos = pos_; }

            void setPreInterFuel() { preInterFuel = internalFuel; }

        private:
            double internalFuel= 0;
            double preInterFuel = 0;
            double fuelFlow =0; 
            Vec3 pos = (0,0,0);
    };

    void FuelSys::setInternalFuel(double fuel){
        internalFuel = fuel;
    }

    void FuelSys::setFuelFlow(double ff){
        fuelFlow = ff;
    }

    double FuelSys::getInternalFuel(){
        return internalFuel;
    }

    double FuelSys::getFuelFlow(){
        return fuelFlow;
    }

    void FuelSys::simulate(double dt, double throttle){
        double fuelCons = fuelFlow * throttle * dt;
        if (fuelCons> internalFuel){
            fuelCons = internalFuel;
        } 

        preInterFuel = internalFuel;
        internalFuel = internalFuel - fuelCons;
    }

    double FuelSys::getFuelQtyDelta() const{
        return preInterFuel - internalFuel;
    }

}
#endif
