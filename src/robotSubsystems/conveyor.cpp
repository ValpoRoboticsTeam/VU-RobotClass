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
    driver->setBrake(hold);


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

}
