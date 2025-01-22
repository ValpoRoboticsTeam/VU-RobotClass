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

// manual vision sensor signature declerations
signature MOGO = signature(1, 47, 997, 522, -4047, -3477, -3762, 2.5, 0);
signature SIG_2 = signature (2, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature SIG_3 = signature (3, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature SIG_5 = signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature SIG_6 = signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature SIG_7 = signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
controller Controller;

// Unique robot variables for management objects
double robotLength = 14.25; // in inches
double gearRatio = double(60)/double(36);
double wheelDiameter = 4; // in inches


// VEXcode device constructors
// DriveTrain Set up
motor FLeft = motor(PORT5, ratio18_1, false);
//motor MidLeft = motor(PORT14, ratio18_1, true);
motor BLeft = motor(PORT12, ratio18_1, false);
motor FRight = motor(PORT6, ratio18_1, true);
//motor MidRight = motor(PORT11, ratio18_1, false);
motor BRight = motor(PORT19, ratio18_1, true);

// DriveTrain Sensors
inertial gyro1 = inertial(PORT11);
inertial gyro2 = inertial(PORT20);
rotation nspod = rotation(PORT10);
rotation ewpod = rotation(PORT10);

sensorUnit* driveSensors = new sensorUnit(&gyro1, &gyro2, &nspod, &ewpod);


motor IntakeDriver = motor(PORT10, ratio18_1, false);
motor  hookDriver = motor(PORT10, ratio18_1, false);

motor armDriver = motor(PORT10, ratio18_1, false);

// Sensors Set up
aivision aivis = aivision(PORT1, aivision::ALL_AIOBJS);
vision vis = vision(PORT1, 50, MOGO, SIG_2, SIG_3, SIG_4, SIG_5, SIG_6, SIG_7);


// Pneumatics Set up
digital_out MogoClamp = digital_out(Brain.ThreeWirePort.A);
//digital_out intakePiston = digital_out(Brain.ThreeWirePort.B);


// Management object constructors
driveTrain* drive = new driveTrain(
  &FLeft, &FRight, 
  //&MidLeft, &MidRight, 
  &BLeft, &BRight, 
  driveSensors, 
  robotLength, gearRatio, wheelDiameter);

clamp* MC = new clamp(&MogoClamp);
intake* i = new intake(&IntakeDriver 
                       //&intakePiston
                       );

conveyor* c = new conveyor(&hookDriver);

arm* lb = new arm(&armDriver);

// Robot Object construction
Robot robot(drive, MC, i, c, lb);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  aivis.modelDetection(true);

  // Nothing to initialize
}
