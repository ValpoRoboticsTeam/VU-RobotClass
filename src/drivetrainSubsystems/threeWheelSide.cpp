/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       threeWheelSide.cpp                                        */
/*    Author:       Nathan Beals                                              */
/*    Created:      Thurs Nov 21, 2024                                        */
/*    Description:  file for storing WheelSide class code                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
using namespace vex;

threeWheelSide::threeWheelSide(
        motor* Frontm, 
        motor* Middlem, 
        motor* Backm, 
        double gearratio, 
        double wheelDiameter
):wheelSide(3) {
    front = Frontm;
    middle = Middlem;
    back = Backm;

    gearRatio = gearratio;
    wheelCircumference = wheelDiameter*M_PI;

    motorConversion = gearRatio*(wheelCircumference)*(360);
}

threeWheelSide::~threeWheelSide(){}


/*---------------------------------------------------------------------------*/
/*-----------------------Drivetrain Utility Functions------------------------*/
/*---------------------------------------------------------------------------*/

double threeWheelSide::getMotorAve(){
    double ave = 0;
    if(front->position(degrees)>0){ave += front->position(degrees);
    } else {ave -= front->position(degrees);}
    if(middle->position(degrees)>0){ave += middle->position(degrees);
    } else {ave -= middle->position(degrees);}
    if(back->position(degrees)>0){ave += back->position(degrees);
    } else {ave -= back->position(degrees);}
    return ave/getNumOfWheels();
}

void threeWheelSide::resetDrivePositions(){
    front->resetPosition();
    middle->resetPosition();
    back->resetPosition();
}

void threeWheelSide::stopDriveSide(brakeType Brake){
    front->stop(brake);
    middle->stop(brake);
    back->stop(brake);
}

void threeWheelSide::setVelocity(double velocity, velocityUnits units){
    front->setVelocity(velocity, units);
    middle->setVelocity(velocity, units);
    back->setVelocity(velocity, units);
}

double threeWheelSide::getMotorWattage(){
    double ave = 0;
    ave += front->power(watt);
    ave += middle->power(watt);
    ave += back->power(watt);
    return ave/getNumOfWheels();
}

double threeWheelSide::getMotorVelocity(){
    double ave = 0;
    ave += front->velocity(velocityUnits::pct);
    ave += middle->velocity(velocityUnits::pct);
    ave += back->velocity(velocityUnits::pct);
    return ave/getNumOfWheels();
}

/*---------------------------------------------------------------------------*/
/*----------------------------DriveSide Movements----------------------------*/
/*---------------------------------------------------------------------------*/

void threeWheelSide::spinTo(double rotation, double velocity, velocityUnits units, bool waitForCompletion){
    setVelocity(velocity, units);

    front->spinTo(rotation, degrees, false);
    middle->spinTo(rotation, degrees, false);
    back->spinTo(rotation, degrees, waitForCompletion);
}

void threeWheelSide::spin(directionType dir, double velocity, velocityUnits units){
    setVelocity(velocity, units);

    front->spin(dir);
    middle->spin(dir);
    back->spin(dir);
}
