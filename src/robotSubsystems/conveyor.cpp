/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       conveyor.hpp                                              */
/*    Author:       Nathan Beals                                              */
/*    Created:      Wed Jan 22 2024                                           */
/*    Description:  file for storing intake class code                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
using namespace vex;

conveyor::conveyor(motor *hookDriver) {
    driver = hookDriver;
    driver->setVelocity(100, velocityUnits::pct);
    driver->setBrake(hold );


    currentPos = 0;
}

conveyor::~conveyor(){}

void conveyor::run(directionType dir) {
    driver->spin(dir);
}

void conveyor::stop() {
    driver->stop();
}

void conveyor::loadRing() {
    //stage 1: 224
    //stage 2: 64
    //stage 3: 87

    driver->resetPosition();
    driver->spinFor(fwd, 224, rotationUnits::deg, true);
    wait(500, msec);

    int longdist = 65;
    int shortdist = 45;
    int delay = 300;

    driver->spinFor(reverse, longdist, rotationUnits::deg, true);
    wait(delay, msec);
    driver->spinFor(fwd, longdist, rotationUnits::deg, true);

    driver->spinFor(reverse, shortdist, rotationUnits::deg, true);
    wait(delay, msec);
    driver->spinFor(fwd, shortdist, rotationUnits::deg, true);
    wait(delay, msec);
    

    //driver->spinFor(fwd, longdist-shortdist, rotationUnits::deg, true);
    
    

    
    driver->spinFor(fwd, 209-(longdist), rotationUnits::deg, true);
}
