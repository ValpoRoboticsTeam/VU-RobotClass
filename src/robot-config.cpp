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
// 15" 
double robotLength = 12.1; // in inches
double gearRatio = 36.0/60.0;
double wheelDiameter = 3.25; // in inches


motor FLeft = motor(PORT10, ratio18_1, true);
motor MLeft = motor(PORT9, ratio18_1, false);
motor BLeft = motor(PORT8, ratio18_1, true);

motor FRight = motor(PORT6, ratio18_1, false);
motor MRight = motor(PORT5, ratio18_1, true);
motor BRight = motor(PORT4, ratio18_1, false);

// DriveTrain Sensors
inertial gyro1 = inertial(PORT7);
inertial gyro2 = inertial(PORT3);
rotation nspod = rotation(PORT2);
rotation ewpod = rotation(PORT2);

sensorUnit driveSensors(&gyro1, &gyro2, &nspod, &ewpod);
driveTrain drive(
  &FLeft, &FRight, 
  &MLeft, &MRight,
  &BLeft, &BRight, 
  &driveSensors, 
  robotLength, gearRatio, wheelDiameter);


digital_out MogoClamp = digital_out(Brain.ThreeWirePort.H);
clamp* MC = new clamp(&MogoClamp);


motor IntakeDriver = motor(PORT21, ratio18_1, false);
intake* i = new intake(&IntakeDriver 
                       //&intakePiston
);

double cycleLength = 0;
double loadLength = 0;
motor hookDriver = motor(PORT16, ratio18_1, true);
conveyor* c = new conveyor(&hookDriver, cycleLength, loadLength);


digital_in linetracker = digital_in(Brain.ThreeWirePort.G);

// Robot Object construction
Robot robot(&drive, MC, i, c);




// manual vision sensor signature declerations
//signature SIG_1 = signature(1, 47, 997, 522, -4047, -3477, -3762, 2.5, 0);
signature MOGO = signature(1, -2617, -885, -1751,-5673, -2891, -4282, 2.5, 0 );


// Vision Sensors Set up
aivision aivis = aivision(PORT2, aivision::ALL_AIOBJS);
vision vis = vision(PORT2, 20, MOGO);



void vexcodeInit(void) {
    aivis.modelDetection(true);
    vis.setBrightness(20);

    IntakeDriver.setBrake(coast);
}