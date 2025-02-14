/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       fourWheelSide.cpp                                         */
/*    Author:       Nathan Beals                                              */
/*    Created:      Mon Dec 2, 2024                                           */
/*    Description:  file for storing WheelSide class code                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
using namespace vex;

fourWheelSide::fourWheelSide(
        motor* Frontm, 
        motor* Middlem1,
        motor* Middlem2, 
        motor* Backm, 
        double gearratio, 
        double wheelDiameter
):wheelSide(4) {
    front = Frontm;
    fmiddle = Middlem1;
    bmiddle = Middlem2;
    back = Backm;

    gearRatio = gearratio;
    wheelCircumference = wheelDiameter*M_PI;

    motorConversion = gearRatio*(wheelCircumference)*(360);
}

fourWheelSide::~fourWheelSide(){}


/*---------------------------------------------------------------------------*/
/*-----------------------Drivetrain Utility Functions------------------------*/
/*---------------------------------------------------------------------------*/

double fourWheelSide::getMotorAve(){
    double ave = 0;
    if(front->position(degrees)>0){ave += front->position(degrees);
    } else {ave -= front->position(degrees);}
    if(fmiddle->position(degrees)>0){ave += fmiddle->position(degrees);
    } else {ave -= fmiddle->position(degrees);}
    if(bmiddle->position(degrees)>0){ave += bmiddle->position(degrees);
    } else {ave -= bmiddle->position(degrees);}
    if(back->position(degrees)>0){ave += back->position(degrees);
    } else {ave -= back->position(degrees);}
    return ave/getNumOfWheels();
}

void fourWheelSide::resetDrivePositions(){
    front->resetPosition();
    fmiddle->resetPosition();
    bmiddle->resetPosition();
    back->resetPosition();
}

void fourWheelSide::stopDriveSide(brakeType Brake){
    front->stop(brake);
    fmiddle->stop(brake);
    bmiddle->stop(brake);
    back->stop(brake);
}

void fourWheelSide::setVelocity(double velocity, velocityUnits units){
    front->setVelocity(velocity, units);
    fmiddle->setVelocity(velocity, units);
    bmiddle->setVelocity(velocity, units);
    back->setVelocity(velocity, units);
}

double fourWheelSide::getMotorWattage(){
    double ave = 0;
    ave += front->power(watt);
    ave += fmiddle->power(watt);
    ave += bmiddle->power(watt);
    ave += back->power(watt);
    return ave/getNumOfWheels();
}

double fourWheelSide::getMotorVelocity(){
    double ave = 0;
    ave += front->velocity(velocityUnits::pct);
    ave += fmiddle->velocity(velocityUnits::pct);
    ave += bmiddle->velocity(velocityUnits::pct);
    ave += back->velocity(velocityUnits::pct);
    return ave/getNumOfWheels();
}

/*---------------------------------------------------------------------------*/
/*----------------------------DriveSide Movements----------------------------*/
/*---------------------------------------------------------------------------*/

void fourWheelSide::spinTo(double rotation, double velocity, velocityUnits units, bool waitForCompletion){
    setVelocity(velocity, units);

    front->spinTo(rotation, degrees, false);
    fmiddle->spinTo(rotation, degrees, false);
    bmiddle->spinTo(rotation, degrees, false);
    back->spinTo(rotation, degrees, waitForCompletion);
}

void fourWheelSide::spin(directionType dir, double velocity, velocityUnits units){
    setVelocity(velocity, units);

    front->spin(dir);
    fmiddle->spin(dir);
    bmiddle->spin(dir);
    back->spin(dir);
}
