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

    driver->setVelocity(highspeed, velocityUnits::pct);
    driver->setBrake(hold);

    cycleLength = 475;
    loadLength = 90;
}

conveyor::~conveyor(){}

void conveyor::run(directionType dir) {
    driver->spin(dir);
}

void conveyor::stop() {
    driver->stop();
}

void conveyor::cycleRing() {
    int cycleLength = 475;
    resetCycle(0);

    driver->resetPosition();
    driver->setVelocity(highspeed, velocityUnits::pct);
    driver->spinFor(fwd, cycleLength, rotationUnits::deg, true);
    wait(500, msec);
}

void conveyor::resetCycle(int speedtype) {
    int remainder = cycleLength - currentPos%cycleLength;

    if(speedtype==0){
        driver->setVelocity(lowspeed, velocityUnits::pct);
    } else {
        driver->setVelocity(highspeed, velocityUnits::pct);
    }
    
    driver->spinFor(fwd, remainder, rotationUnits::deg, true);
}

void conveyor::loadRing() {
    driver->setVelocity(lowspeed, velocityUnits::pct);

    currentPos+=loadLength;
    driver->spinFor(fwd, loadLength, rotationUnits::deg, true);
    wait(500, msec);
}
