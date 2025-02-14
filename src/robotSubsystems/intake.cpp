/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       intake.cpp                                                */
/*    Author:       Nathan Beals                                              */
/*    Created:      Mon Dec 2 2024                                            */
/*    Description:  file for storing intake class code                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
using namespace vex;

intake::intake(
    motor* DriveMotor
    //digital_out* ActuatingPiston
) {
    driver = DriveMotor;
    driver->setVelocity(100, velocityUnits::pct);
    driver->setBrake(hold);
    //actuator = ActuatingPiston;
}

intake::~intake(){}

void intake::extend() {
    //actuator->set(true);
}

void intake::retract() {
    //actuator->set(false);
}

void intake::setVelocity(double velocity, velocityUnits units) {
    driver->setVelocity(velocity, units);
}

void intake::run(directionType dir){
    driver->spin(dir);
}

void intake::stop() {
    driver->stop();    
}

void intake::runConveyor() {
    
}
