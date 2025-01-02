/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       robot-config.cpp                                          */
/*    Author:       auto genorated                                            */
/*    Created:      Sun Feb. 18 2024                                          */
/*    Description:  creates global instances of all vex devices               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
controller Controller;

// Unique robot variables for management objects
double robotLength = 14.25; // in inches
double gearRatio = double(60)/double(36);
double wheelDiameter = 4; // in inches


// VEXcode device constructors
// DriveTrain Set up
motor FLeft = motor(PORT11, ratio18_1, false);
//motor MidLeft = motor(PORT14, ratio18_1, true);
motor BLeft = motor(PORT12, ratio18_1, false);
motor FRight = motor(PORT20, ratio18_1, true);
//motor MidRight = motor(PORT11, ratio18_1, false);
motor BRight = motor(PORT19, ratio18_1, true);

// DriveTrain Sensors
inertial gyro1 = inertial(PORT12);
inertial gyro2 = inertial(PORT19);
rotation nspod = rotation(PORT1);
rotation ewpod = rotation(PORT1);

sensorUnit* driveSensors = new sensorUnit(&gyro1, &gyro2, &nspod, &ewpod);


motor IntakeDriver = motor(PORT1, ratio18_1, false);

// Sensors Set up
aivision vis = aivision(PORT5, aivision::ALL_AIOBJS);

// Pneumatics Set up
digital_out MogoClamp = digital_out(Brain.ThreeWirePort.A);
digital_out intakePiston = digital_out(Brain.ThreeWirePort.B);


// Management object constructors
driveTrain* drive = new driveTrain(
  &FLeft, &FRight, 
  //&MidLeft, &MidRight, 
  &BLeft, &BRight, 
  driveSensors, 
  robotLength, gearRatio, wheelDiameter);

clamp* MC = new clamp(&MogoClamp);
intake* i = new intake(&IntakeDriver, &intakePiston);

// Robot Object construction
Robot robot(drive, MC, i);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  vis.modelDetection(true);

  // Nothing to initialize
}
