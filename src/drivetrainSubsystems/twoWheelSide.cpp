/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       twoWheelSide.cpp                                          */
/*    Author:       Nathan Beals                                              */
/*    Created:      Sun March 17 2024                                         */
/*    Description:  file for storing twoWheelSide class code                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
using namespace vex;

twoWheelSide::twoWheelSide(
        motor* frontm,
        motor* backm,
        double gearratio,
        double wheelDiameter
):wheelSide(2) {
    front = frontm;
    back = backm;

    gearRatio = gearratio;
    wheelCircumference = wheelDiameter*M_PI;

    motorConversion = gearRatio*(wheelCircumference)*(360);
}

twoWheelSide::~twoWheelSide(){}

/*---------------------------------------------------------------------------*/
/*-----------------------Drivetrain Utility Functions------------------------*/
/*---------------------------------------------------------------------------*/

double twoWheelSide::getMotorAve(){
    double ave = 0;
    if(front->position(degrees)>0){ave += front->position(degrees);
    } else {ave -= front->position(degrees);}
    if(back->position(degrees)>0){ave += back->position(degrees);
    } else {ave -= back->position(degrees);}
    return ave/getNumOfWheels();
}

void twoWheelSide::resetDrivePositions(){
    front->resetPosition();
    back->resetPosition();
}

void twoWheelSide::stopDriveSide(brakeType Brake){
    front->stop(brake);
    back->stop(brake);
}

void twoWheelSide::setVelocity(double velocity, velocityUnits units){
    front->setVelocity(velocity, units);
    back->setVelocity(velocity, units);
}

double twoWheelSide::getMotorWattage(){
    double ave = 0;
    ave += front->power(watt);
    ave += back->power(watt);
    return ave/getNumOfWheels();
}

double twoWheelSide::getMotorVelocity(){
    double ave = 0;
    ave += front->velocity(velocityUnits::pct);
    ave += back->velocity(velocityUnits::pct);
    return ave/getNumOfWheels();
}

/*---------------------------------------------------------------------------*/
/*----------------------------DriveSide Movements----------------------------*/
/*---------------------------------------------------------------------------*/

void twoWheelSide::spinTo(double rotation, double velocity, velocityUnits units, bool waitForCompletion){
    setVelocity(velocity, units);
    
    front->spinTo(rotation, degrees, false);
    front->spinTo(rotation, degrees, false);
    front->spinTo(rotation, degrees, waitForCompletion);
}

void twoWheelSide::spin(vex::directionType dir, double velocity, velocityUnits units){
    setVelocity(velocity, units);

    front->spin(dir);
    back->spin(dir);
}