/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       arm.cpp                                                   */
/*    Author:       Nathan Beals                                              */
/*    Created:      Wed Jan 22 2024                                           */
/*    Description:  file for storing intake class code                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
using namespace vex;

arm::arm(motor* ladyBrown) {
    driver = ladyBrown;
    driver->setVelocity(100, velocityUnits::pct);
    driver->setBrake(hold);
}

arm::~arm(){}

void arm::spin(directionType dir){
    driver->spin(dir);
}

void arm::stop(){
    driver->stop();
}
