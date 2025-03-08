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

conveyor::conveyor(motor *hookDriver, double cycle, double load) {
    driver = hookDriver;
    driver->resetPosition();
    driver->setVelocity(highspeed, velocityUnits::pct);
    driver->setBrake(brake);
    //driver->setTimeout(700, msec);

    cycleLength = cycle;
    loadLength = load;
}

conveyor::~conveyor(){}

void conveyor::run(directionType dir) {

    if(Moving() && (dir== reverse)){
        isMoving = false;
        stop();
        run(dir);

    } else if(!Moving()){
        driver->setVelocity(highspeed, velocityUnits::pct);
        driver->spin(dir);
    }
}

void conveyor::stop() {
    if(!Moving()){
        driver->stop();
    }
}

void conveyor::cycleRing() {
    resetCycle(0);

    driver->resetPosition();
    driver->setVelocity(highspeed, velocityUnits::pct);

    isMoving = true;
    
    driver->spinFor(fwd, cycleLength, rotationUnits::deg, true);
    waitUntil((driver->isDone()) || (!Moving()));
    isMoving = false;
}

void conveyor::resetCycle(int speedtype) {
    int currentPos = driver->position(degrees);
    int remainder = cycleLength - currentPos%cycleLength;


    if(speedtype==0){
        driver->setVelocity(lowspeed, velocityUnits::pct);
    } else {
        driver->setVelocity(highspeed, velocityUnits::pct);
    }
    
    isMoving = true;
    driver->spinFor(fwd, remainder, rotationUnits::deg, true);
    waitUntil((driver->isDone()) || (!Moving()));
    isMoving = false;
}

void conveyor::loadRing(void) {
    driver->setVelocity(lowspeed, velocityUnits::pct);

    isMoving = true;
    driver->spinFor(fwd, loadLength, rotationUnits::deg, true);
    waitUntil((driver->isDone()) || (!Moving()));
    isMoving = false;
}
