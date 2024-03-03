#pragma once

#ifndef ENGINE2_H
#define ENGINE2_H

#include "vec3.h"
#include "force.h"
#include "enginedata.h"
#include "utilities.h"
#include "maths.h"

namespace Aircraft
{
    enum StationNo {
        FREESTREAM,
        INLET_ENTRY,
        COMP_ENTRY,
        BURNER_ENTRY,
        TURBINE_ENTRY,
        TURBINE_EXIT,
        PRE_AB,
        NOZZLE_ENTRY,
        NOZZLE_THROAT,
        NINE,
        TEN,
        ELEVEN,
        TWELVE,
        FAN_EXIT,
        FOURTEEN,
        LP_TURBINE_EXIT
    };

    class Engine2
    {
    public:
        Engine2() {
            init();
        };
        Engine2(Vec3& pos_)
        {
            pos = pos_;
            init();
        };
        ~Engine2() {};

        inline void simulate(double dt, double throttle, double ps0_, double ts0_, double alt_, double u0d_);
        inline Vec3 getPos();
        inline void setPos(Vec3& pos_);
        inline double getThrustVal();
        inline double getFuelRate();

    private:
        // specific energy, energy per mass. const value 1718 ft^2/s^2
        double rgas = 1718;
        // atmosphere temperature
        double ts0;
        // atmosphere pressure
        double ps0;
        // speed of sound (ft/sec)
        double a0;
        // gama value
        double gama = 1.4;
        // relative airspeed to speed of sound a0
        double fsmach;
        // dynamic pressure. q0 = gamma/2 * mach * mach * ps0
        double q0;
        /**
        *  density, unused
        *  if air speed < 0.001, value is 1, else calculate from q0 and u0
        */
        double rho0;
        // air speed (ft/sec), converted from u0d
        double u0;
        // altitude
        double alt;
        // altitude (ft - m) conversion factor, m to ft
        double lconv1 = 1;
        // airspeed (km/h - ft/sec) conversion factor
        double lconv2 = 1;
        // thrust force (lbs - N) conversion factor
        double fconv = 1;
        // mass (lbs - kg) conversion factor
        double mconv1 = 1;
        // gamma option. correspond to Gamma/Gam(T) options in flight panel UI
        int gamopt = 1;

        /** specific energy, energy per mass. if Gamma option is selected, value is .2399.
        * if Gamma(T) option is selected, calculate from temperature tt[1]
        */
        double cpair;
        // equal to ts0
        double tsout;

        // equal to ps0
        double psout;

        // engine exit pressure, output panel Pexit
        double pexit;

        // engine inlet end / compressor entrance sectional area
        double a2;

        // ac = 0.9 * a2
        double ac;

        // engine core diameter
        double diameng;

        /**
        *  burner temperature. Normally, tt[4] = tt4 = tt4d
        */
        double tt4;

        // burner exit/ turbine entrance sectional area
        double a4;

        // burner exit/ turbine entrance pressure
        double a4p;

        /**
        *  nozzle temperature. Normally, tt[7] = tt7 = tt7d
        */
        double tt7;

        // engine nozzle throat sectional area
        double a8;

        // used to calculate delan
        double a8d;

        double a8max;

        //a8rat = a8/acore
        double a8rat;

        // temperature at station 8
        double t8;

        // throtl value
        double throtl;

        //afterburner flag
        int abflag;

        // engine core sectional area
        double acore;

        // engine overall pressure ratio
        double epr;

        // engine compressor pressure ratio
        double cpr;

        // engine overall temperature ratio
        double etr;

        // engine overall NPR
        double npr;

        // engine thermal efficiency
        double eteng;

        // 9.81 m/s^2 in metric, 32.2 ft/s^2 in imperial/percent
        double g0;

        double uexit;

        double ues;

        // engine airflow
        double eair;

        // engine inlet end / compressor entrance (STATION No.2) section mach number
        double m2;

        // gross thrust
        double fgros;

        // net thrust
        double fnet;

        // ram drag
        double dram;

        // mass flow ratio
        double mfr;

        // net thrust in lbs
        double fnlb;

        // gross thrust in lbs
        double fglb;

        // ram drag in lbs
        double drlb;

        // output panel ISP value
        double isp;

        // fuel-to-air ratio
        double fa;

        double fuelHeatValue;

        // TFSC output (lbm/(lbs*hr))
        double sfc;

        /**
        * fuel flow. flflo = sfc * fnlb
        */
        double flflo;


        // compressor temperature limit, default is 1500.
        double tcomp;

        // fan temperature limit, default is 1500.
        double tfan;

        // turbine temperature limit, default is 2500
        double tturbin;

        // burner temperature limit, default is 2500
        double tburner;

        // inlet temperature limit, default is 900
        double tinlt;

        // nozzle temperature limit
        double tnozl;

        // temp limits exceeded flag. If set, show temp limits exceeded alert.
        int fireflag;

        // engine weight
        double weight;

        /**
        * engine component temperature rates
        * trat[i] = tt[i] / tt[i-1]
        */
        double trat[ENGINE_MAX_STAGE] = {};

        /** engine components temperatures
         * 0 - free stream temp
         * 1 - inlet entrance temp
         * 2 - inlet end (compressor entrance) temp
         * 3 - compressor end (burner entrance) temp
         * 4 - burner end (turbine entrance) temp
         * 5 - turbine exit temp
         * 6 - before afterburner start temp
         * 7 - nozzle entrance temp
         * 8 - nozzle throat temp
         * 13 - fan temp
        */
        double tt[ENGINE_MAX_STAGE] = {};

        /**
         * engine components pressure ratios
         * 0 - free stream pressure ratio
         * 1 - inlet entrance  pressure ratio
         * 2 - inlet end (compressor entrance) pressure ratio
         * 3 - compressor end (burner entrance) pressure ratio
         * 4 - burner end (turbine entrance) pressure ratio
         * 5 - turbine exit pressure ratio
         * 6 - before afterburner start pressure ratio
         * 7 - nozzle entrance pressure ratio
         * 8 - nozzle throat pressure ratio
         * 13 - fan pressure ratio
         */
        double pressureRatio[ENGINE_MAX_STAGE] = {};

        /**
         * engine components pressures
         * pt[1] = pt [0]
         * pt[i] = pt[i-1]* pressureRatio[i]
         */
        double pt[ENGINE_MAX_STAGE] = {};

        // engine components efficiency
        double efficiency[ENGINE_MAX_STAGE] = {};

        // engine components Gamma
        double gam[ENGINE_MAX_STAGE] = {};

        double cp[ENGINE_MAX_STAGE] = {};

        // engine components entropy
        double s[ENGINE_MAX_STAGE] = {};

        // engine components Spec Vol - v 
        double v[ENGINE_MAX_STAGE] = {};

        // engine mount position
        Vec3 pos = Vec3(0, 0, 0);

        // init engine spec
        inline void init();
        inline void getFreeStream(double ps0_, double ts0_, double alt_, double u0d_);
        inline void getThermo();
        inline void getPerform();
    };

    void inline Engine2::simulate(double dt, double throttle, double ps0_, double ts0_, double alt_, double u0d_) {
        fireflag = 0;
        throtl = throttle;
        getFreeStream(ps0_, ts0_, alt_, u0d_);
        getThermo();
        a8 = a8d * sqrt(trat[NOZZLE_ENTRY]) / pressureRatio[NOZZLE_ENTRY];
        getPerform();
    }

    void inline Engine2::init() {
        /* Metric Units */
        lconv1 = 0.3048;
        lconv2 = 1.609;
        fconv = 4.448;
        mconv1 = 0.04536;

        g0 = 32.2;

        fireflag = 0;
        gama = 1.4;
        gamopt = 1;

        for (int i = 0; i < ENGINE_MAX_STAGE; ++i) {
            trat[i] = 1.0;
            tt[i] = 518.6;
            pressureRatio[i] = 1.0;
            pt[i] = 14.7;
            efficiency[i] = 1.0;
        }

        tt[TURBINE_ENTRY] = tt4 = 2999;
        tt[NOZZLE_ENTRY] = tt7 = 3905;
        pressureRatio[BURNER_ENTRY] = 31.0;
        pressureRatio[FAN_EXIT] = 1.745;
        acore = 6.711;
        a2 = acore;
        diameng = sqrt(4 * a2 / PI);
        a4 = 0.472;
        a4p = 1.524;
        ac = 0.9 * a2;
        weight = 3902;

        efficiency[COMP_ENTRY] = 1.0;
        pressureRatio[COMP_ENTRY] = 1.0;
        pressureRatio[TURBINE_ENTRY] = 1.0;
        efficiency[BURNER_ENTRY] = .965;
        efficiency[TURBINE_ENTRY] = .984;
        efficiency[TURBINE_EXIT] = .985;
        efficiency[NOZZLE_ENTRY] = .92;
        efficiency[FAN_EXIT] = 1.0;

        fuelHeatValue = 18600;
        acore = 2.0;

        a8 = 0.7;
        a8d = 1.524;
        a8max = 0.335;
        a8rat = 0.335;
        a4 = 0.418;

        tinlt = 900;
        tfan = 1500;
        tcomp = 1500;
        tburner = 3000;
        tturbin = 3000;
        tnozl = 4100;
        u0 = 0;
        alt = 0;
    };

    Vec3 Engine2::getPos()
    {
        return pos;
    }

    void inline Engine2::setPos(Vec3& pos_)
    {
        pos = pos_;
    }

    /**
     * getFreeStream()
     * @param ps0_ atmosphere pressure
     * @param ts0_ atmosphere temperature
     * @param alt_ altitude
     * @param u0d_ airspeed
     * **/
    void inline Engine2::getFreeStream(double ps0_, double ts0_, double alt_, double u0d_) {
        ps0 = ps0_ * 144;
        alt = alt_ * lconv1;
        ts0 = ts0_;

        a0 = sqrt(gama * rgas * ts0);
        u0 = u0d_ / lconv2 * 5280 / 3600;
        fsmach = u0 / a0;

        q0 = gama / 2.0 * fsmach * fsmach * ps0;
        if (u0 > 0.0001) {
            rho0 = q0 / (u0 * u0);
        }
        else {
            rho0 = 1;
        }

        tt[FREESTREAM] = ts0 * (1.0 + 0.5 * (gama - 1.0) * fsmach * fsmach);
        pt[FREESTREAM] = ps0 * pow(tt[FREESTREAM] / ts0, gama / (gama - 1.0));
        ps0 = ps0 / 144;
        pt[FREESTREAM] = pt[FREESTREAM] / 144;

        cpair = getCp(tt[FREESTREAM], gamopt);              /*BTU/lbm R */
        tsout = ts0;
        psout = ps0;
    }

    void inline Engine2::getThermo() {
        double dela;
        double t5t4n;
        double deriv;
        double delan;
        double m5;
        double delhc;
        double delhht;
        double delhf;
        double delhlt;
        double deltc;
        double deltht;
        double deltf;
        double deltlt;
        int itcount;

        if (fsmach > 1.0) {          /* supersonic */
            pressureRatio[COMP_ENTRY] = 1.0 - 0.075 * pow(fsmach - 1.0, 1.35);
        }
        else {
            pressureRatio[COMP_ENTRY] = 1.0;
        }
        efficiency[COMP_ENTRY] = pressureRatio[COMP_ENTRY];

        trat[NOZZLE_ENTRY] = 1.0;
        pressureRatio[NOZZLE_ENTRY] = 1.0;
        tt[COMP_ENTRY] = tt[INLET_ENTRY] = tt[FREESTREAM];
        pt[INLET_ENTRY] = pt[FREESTREAM];
        gam[COMP_ENTRY] = getGamma(tt[COMP_ENTRY], gamopt);
        cp[COMP_ENTRY] = getCp(tt[COMP_ENTRY], gamopt);
        pt[COMP_ENTRY] = pt[INLET_ENTRY] * pressureRatio[COMP_ENTRY];

        /* analysis -assume flow choked at both turbine entrances */
                             /* and nozzle throat ... then*/
        tt[TURBINE_ENTRY] = tt4 * throtl / 100.0;
        gam[TURBINE_ENTRY] = getGamma(tt[TURBINE_ENTRY], gamopt);
        cp[TURBINE_ENTRY] = getCp(tt[TURBINE_ENTRY], gamopt);
        if (a4 < 0.02) {
            a4 = 0.02;
        }

        dela = 0.2;                           /* iterate to get t5t4 */
        trat[TURBINE_EXIT] = 1.0;
        t5t4n = 0.5;
        itcount = 0;
        while (abs(dela) > 0.001 && itcount < 20) {
            ++itcount;
            delan = a8d / a4 - sqrt(t5t4n) *
                pow((1.0 - (1.0 / efficiency[TURBINE_EXIT]) * (1.0 - t5t4n)),
                    -gam[TURBINE_ENTRY] / (gam[TURBINE_ENTRY] - 1.0));
            deriv = (delan - dela) / (t5t4n - trat[TURBINE_EXIT]);
            dela = delan;
            trat[TURBINE_EXIT] = t5t4n;
            t5t4n = trat[TURBINE_EXIT] - dela / deriv;
        }
        tt[TURBINE_EXIT] = tt[TURBINE_ENTRY] * trat[TURBINE_EXIT];
        gam[TURBINE_EXIT] = getGamma(tt[TURBINE_EXIT], gamopt);
        cp[TURBINE_EXIT] = getCp(tt[TURBINE_EXIT], gamopt);
        deltht = tt[TURBINE_EXIT] - tt[TURBINE_ENTRY];
        delhht = cp[TURBINE_ENTRY] * deltht;
        pressureRatio[TURBINE_EXIT] = pow((1.0 - (1.0 / efficiency[TURBINE_EXIT]) * (1.0 - trat[TURBINE_EXIT])),
            gam[TURBINE_ENTRY] / (gam[TURBINE_ENTRY] - 1.0));
        delhc = delhht;           /* compressor work */
        deltc = -delhc / cp[COMP_ENTRY];
        tt[BURNER_ENTRY] = tt[COMP_ENTRY] + deltc;
        gam[BURNER_ENTRY] = getGamma(tt[BURNER_ENTRY], gamopt);
        cp[BURNER_ENTRY] = getCp(tt[BURNER_ENTRY], gamopt);
        trat[BURNER_ENTRY] = tt[BURNER_ENTRY] / tt[COMP_ENTRY];
        pressureRatio[BURNER_ENTRY] = pow((1.0 + efficiency[BURNER_ENTRY] * (trat[BURNER_ENTRY] - 1.0)),
            gam[COMP_ENTRY] / (gam[COMP_ENTRY] - 1.0));
        trat[TURBINE_ENTRY] = tt[TURBINE_ENTRY] / tt[BURNER_ENTRY];
        pt[BURNER_ENTRY] = pt[COMP_ENTRY] * pressureRatio[BURNER_ENTRY];
        pt[TURBINE_ENTRY] = pt[BURNER_ENTRY] * pressureRatio[TURBINE_ENTRY];
        pt[TURBINE_EXIT] = pt[TURBINE_ENTRY] * pressureRatio[TURBINE_EXIT];
        /* fanPanel conditions */
        pressureRatio[FAN_EXIT] = 1.0;
        trat[FAN_EXIT] = 1.0;
        tt[FAN_EXIT] = tt[COMP_ENTRY];
        pt[FAN_EXIT] = pt[COMP_ENTRY];
        gam[FAN_EXIT] = gam[COMP_ENTRY];
        cp[FAN_EXIT] = cp[COMP_ENTRY];
        pressureRatio[LP_TURBINE_EXIT] = 1.0;
        pt[LP_TURBINE_EXIT] = pt[TURBINE_EXIT];
        trat[LP_TURBINE_EXIT] = 1.0;
        tt[LP_TURBINE_EXIT] = tt[TURBINE_EXIT];
        gam[LP_TURBINE_EXIT] = gam[TURBINE_EXIT];
        cp[LP_TURBINE_EXIT] = cp[TURBINE_EXIT];

        if (abflag == 1) {
            tt[NOZZLE_ENTRY] = tt7;
        }

        pressureRatio[PRE_AB] = 1.0;
        pt[PRE_AB] = pt[LP_TURBINE_EXIT];
        trat[PRE_AB] = 1.0;
        tt[PRE_AB] = tt[LP_TURBINE_EXIT];
        gam[PRE_AB] = getGamma(tt[PRE_AB], gamopt);
        cp[PRE_AB] = getCp(tt[PRE_AB], gamopt);
        if (abflag > 0) {                   /* afterburner */
            trat[NOZZLE_ENTRY] = tt[NOZZLE_ENTRY] / tt[PRE_AB];
            m5 = getMach(0, getAirflowPerArea(1.0, gam[TURBINE_EXIT]) * a4 / acore, gam[TURBINE_EXIT]);
            pressureRatio[NOZZLE_ENTRY] = getRayleighLoss(m5, trat[NOZZLE_ENTRY], tt[PRE_AB], gamopt);
        }
        tt[NOZZLE_ENTRY] = tt[PRE_AB] * trat[NOZZLE_ENTRY];
        pt[NOZZLE_ENTRY] = pt[PRE_AB] * pressureRatio[NOZZLE_ENTRY];
        gam[NOZZLE_ENTRY] = getGamma(tt[NOZZLE_ENTRY], gamopt);
        cp[NOZZLE_ENTRY] = getCp(tt[NOZZLE_ENTRY], gamopt);
        /* engine press ratio EPR*/
        epr = pressureRatio[NOZZLE_ENTRY] * pressureRatio[LP_TURBINE_EXIT] * pressureRatio[TURBINE_EXIT] * pressureRatio[TURBINE_ENTRY] * pressureRatio[BURNER_ENTRY] * pressureRatio[FAN_EXIT];
        /* compressor press ratio CPR*/
        cpr = pressureRatio[BURNER_ENTRY];
        /* engine temp ratio ETR */
        etr = trat[NOZZLE_ENTRY] * trat[LP_TURBINE_EXIT] * trat[TURBINE_EXIT] * trat[TURBINE_ENTRY] * trat[BURNER_ENTRY] * trat[FAN_EXIT];
    }

    /**
     *  determines engine performance
     * **/
    void inline Engine2::getPerform() {
        double fac1;
        double game;
        double cpe;
        double cp3;
        double rg;
        double p8p5;
        double rg1;
        int index;

        rg1 = 53.3;
        rg = cpair * (gama - 1.0) / gama;
        cp3 = getCp(tt[BURNER_ENTRY], gamopt);                  /*BTU/lbm R */
        g0 = 32.2;
        ues = 0.0;
        game = getGamma(tt[TURBINE_EXIT], gamopt);
        fac1 = (game - 1.0) / game;
        cpe = getCp(tt[TURBINE_EXIT], gamopt);

        /*  specific net thrust  - thrust / (g0*airflow) -   lbf/lbm/sec  */
        // turbine engine core

         /* airflow determined at choked nozzle exit */
        pt[NOZZLE_THROAT] = epr * pressureRatio[COMP_ENTRY] * pt[FREESTREAM];
        eair = getAirflowPerArea(1.0, game) * 144 * a8 * pt[NOZZLE_THROAT] / 14.7 /
            sqrt(etr * tt[FREESTREAM] / 518);
        m2 = getMach(0, eair * sqrt(tt[FREESTREAM] / 518) /
            (pressureRatio[COMP_ENTRY] * pt[FREESTREAM] / 14.7 * acore * 144.), gama);
        npr = pt[NOZZLE_THROAT] / ps0;
        uexit = sqrt(2.0 * rgas / fac1 * etr * tt[FREESTREAM] * efficiency[NOZZLE_ENTRY] *
            (1.0 - pow(1.0 / npr, fac1)));
        if (npr <= 1.893) {
            pexit = ps0;
        }
        else {
            pexit = 0.52828 * pt[NOZZLE_THROAT];
        }
        fgros = (uexit + (pexit - ps0) * 144 * a8 / eair) / g0;

        // ram drag
        dram = u0 / g0;

        // mass flow ratio
        if (fsmach > .01) {
            mfr = getAirflowPerArea(m2, gama) * pressureRatio[COMP_ENTRY] / getAirflowPerArea(fsmach, gama);
        }
        else {
            mfr = 5.0;
        }

        // net thrust
        fnet = fgros - dram;

        // thrust and drag in pounds
        fnlb = fnet * eair;
        fglb = fgros * eair;
        drlb = dram * eair;

        //fuel-air ratio and sfc
        fa = (trat[TURBINE_ENTRY] - 1.0) / (efficiency[TURBINE_ENTRY] * fuelHeatValue / (cp3 * tt[BURNER_ENTRY]) - trat[TURBINE_ENTRY]) +
            (trat[NOZZLE_ENTRY] - 1.0) / (fuelHeatValue / (cpe * tt[LP_TURBINE_EXIT]) - trat[NOZZLE_ENTRY]);
        if (fnet > 0.0) {
            sfc = 3600 * fa / fnet;
            flflo = sfc * fnlb;
            isp = (fnlb / flflo) * 3600;
        }
        else {
            fnlb = 0.0;
            flflo = 0.0;
            sfc = 0.0;
            isp = 0.0;
        }

        tt[NOZZLE_THROAT] = tt[NOZZLE_ENTRY];
        t8 = etr * tt[FREESTREAM] - uexit * uexit / (2.0 * rgas * game / (game - 1.0));
        trat[NOZZLE_THROAT] = 1.0;
        p8p5 = ps0 / (epr * pressureRatio[COMP_ENTRY] * pt[FREESTREAM]);
        cp[NOZZLE_THROAT] = getCp(tt[NOZZLE_THROAT], gamopt);
        pt[NOZZLE_THROAT] = pt[NOZZLE_ENTRY];
        pressureRatio[NOZZLE_THROAT] = pt[NOZZLE_THROAT] / pt[NOZZLE_ENTRY];
        /* thermal effeciency */

        eteng = (a0 * a0 * ((1.0 + fa) * (uexit * uexit / (a0 * a0))
            - fsmach * fsmach)) / (2.0 * g0 * fa * fuelHeatValue * 778.16);

        s[FREESTREAM] = s[INLET_ENTRY] = .2;
        v[FREESTREAM] = v[INLET_ENTRY] = rg1 * ts0 / (ps0 * 144.);
        for (index = 2; index <= 7; ++index) {     /* compute entropy */
            s[index] = s[index - 1] + cpair * log(trat[index])
                - rg * log(pressureRatio[index]);
            v[index] = rg1 * tt[index] / (pt[index] * 144.);
        }
        s[FAN_EXIT] = s[COMP_ENTRY] + cpair * log(trat[FAN_EXIT]) - rg * log(pressureRatio[FAN_EXIT]);
        v[FAN_EXIT] = rg1 * tt[FAN_EXIT] / (pt[FAN_EXIT] * 144.);
        s[LP_TURBINE_EXIT] = s[TURBINE_EXIT] + cpair * log(trat[LP_TURBINE_EXIT]) - rg * log(pressureRatio[LP_TURBINE_EXIT]);
        v[LP_TURBINE_EXIT] = rg1 * tt[LP_TURBINE_EXIT] / (pt[LP_TURBINE_EXIT] * 144.);
        s[NOZZLE_THROAT] = s[NOZZLE_ENTRY] + cpair * log(t8 / (etr * tt[FREESTREAM])) - rg * log(p8p5);
        v[NOZZLE_THROAT] = rg1 * t8 / (ps0 * 144.);
        cp[FREESTREAM] = getCp(tt[FREESTREAM], gamopt);

        if (tt[COMP_ENTRY] > tinlt) {
            fireflag = 1;
        }
        if (tt[FAN_EXIT] > tfan) {
            fireflag = 1;
        }
        if (tt[BURNER_ENTRY] > tcomp) {
            fireflag = 1;
        }
        if (tt[TURBINE_ENTRY] > tburner) {
            fireflag = 1;
        }
        if (tt[TURBINE_EXIT] > tturbin) {
            fireflag = 1;
        }
        if (tt[NOZZLE_ENTRY] > tnozl) {
            fireflag = 1;
        }

    }

    /**
     * getThrustVal returns engine net thrust in N
     * **/
    inline double Engine2::getThrustVal() {
        return fnlb * fconv;
    }

    /**
     * getFuelRate returns engine fuel rate in kg/hr
     * **/
    inline double Engine2::getFuelRate() {
        return flflo * mconv1;
    }

}
#endif // ENGINE2_H
