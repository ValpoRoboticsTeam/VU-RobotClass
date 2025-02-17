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
//signature MOGO = signature(1, 47, 997, 522, -4047, -3477, -3762, 2.5, 0);


// A global instance of brain used for printing to the V5 brain screen
brain Brain;
controller Controller;

// DriveTrain Set up
// 24" 

double robotLength = 14.5; // in inches
double gearRatio = 44.0/20.0;
double wheelDiameter = 3.25; // in inches

motor FLeft = motor(PORT15, ratio18_1, true);
motor MLeft = motor(PORT16, ratio18_1, true);
motor BLeft = motor(PORT18, ratio18_1, true);

motor FRight = motor(PORT18, ratio18_1, false);
motor MRight = motor(PORT19, ratio18_1, false);
motor BRight = motor(PORT20, ratio18_1, false);

inertial gyro1 = inertial(PORT9);
inertial gyro2 = inertial(PORT10);
rotation nspod = rotation(PORT5);
rotation ewpod = rotation(PORT5);

sensorUnit driveSensors(&gyro1, &gyro2, &nspod, &ewpod);
driveTrain drive(
  &FLeft, &FRight, 
  &MLeft, &MRight,
  &BLeft, &BRight, 
  &driveSensors, 
  robotLength, gearRatio, wheelDiameter);

  digital_out MogoClamp = digital_out(Brain.ThreeWirePort.H);
  clamp* MC = new clamp(&MogoClamp);
  
  
  motor IntakeDriver = motor(PORT1, ratio18_1, true);
  intake* i = new intake(&IntakeDriver 
                         //&intakePiston
                         );

  motor hookDriver = motor(PORT2, ratio18_1, true);
  conveyor* c = new conveyor(&hookDriver);
  


// 15" 
/*
double robotLength = 12.1; // in inches
double gearRatio = 36.0/60.0;
double wheelDiameter = 3.25; // in inches


motor FLeft = motor(PORT1, ratio18_1, true);
motor MLeft = motor(PORT16, ratio18_1, true);
motor BLeft = motor(PORT7, ratio18_1, false);

motor FRight = motor(PORT10, ratio18_1, false);
motor MRight = motor(PORT11, ratio18_1, true);
motor BRight = motor(PORT15, ratio18_1, true);

// DriveTrain Sensors
inertial gyro1 = inertial(PORT5);
inertial gyro2 = inertial(PORT5);
rotation nspod = rotation(PORT5);
rotation ewpod = rotation(PORT5);

sensorUnit driveSensors(&gyro1, &gyro2, &nspod, &ewpod);
driveTrain drive(
  &FLeft, &FRight, 
  &MLeft, &MRight,
  &BLeft, &BRight, 
  &driveSensors, 
  robotLength, gearRatio, wheelDiameter);


digital_out MogoClamp = digital_out(Brain.ThreeWirePort.H);
clamp* MC = new clamp(&MogoClamp);


motor IntakeDriver = motor(PORT21, ratio18_1, true);
intake* i = new intake(&IntakeDriver 
                       //&intakePiston
                       );

motor hookDriver = motor(PORT, ratio18_1, true);
conveyor* c = new conveyor(&hookDriver);
*/

digital_in linetracker = digital_in(Brain.ThreeWirePort.G);

// Robot Object construction
Robot robot(&drive, MC, i, c);




// manual vision sensor signature declerations
//signature SIG_1 = signature(1, 47, 997, 522, -4047, -3477, -3762, 2.5, 0);
signature MOGO = signature(1, -2617, -885, -1751,-5673, -2891, -4282, 2.5, 0 );


// Vision Sensors Set up
aivision aivis = aivision(PORT3, aivision::ALL_AIOBJS);
vision vis = vision(PORT4, 20, MOGO);



void vexcodeInit(void) {
    aivis.modelDetection(true);
    vis.setBrightness(20);

    IntakeDriver.setBrake(coast);
}