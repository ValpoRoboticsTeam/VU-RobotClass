/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       odomUnit.cpp                                              */
/*    Author:       Nathan Beals                                              */
/*    Created:      Fri Dec 6                                                 */
/*    Description:  file for storing Odom Sensor managment class code         */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
using namespace vex;

sensorUnit::sensorUnit(
    inertial* gyro1,
    inertial* gyro2,
    rotation* pod1,
    rotation* pod2
) {
    leftGyro = gyro1;
    rightGyro = gyro2;
    NSPod = pod1;
    EWPod = pod2;

    leftGyro->calibrate();
    rightGyro->calibrate();

    leftGyro->resetHeading();
    rightGyro->resetHeading();
}

sensorUnit::~sensorUnit(){}


/* GYRO FUNCTIONS */

double sensorUnit::getHeading(int dir){
    
    double heading = 360+getRotation();

    while (true){
        if(heading < 360.00) {break;}
        heading -= 360;
    }
    return heading;
}

double sensorUnit::getPosNS(){
    return NSPod->position(rotationUnits::deg);
}