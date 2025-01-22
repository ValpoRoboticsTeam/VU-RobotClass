/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// BROKEN STUFF 15X15 BOT  
// PORTS 1, 14, 7,8 

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller           controller             
//
// FL                   Motor         19        
// BL                   Motor         10       
// FR                   Motor         15        
// BR                   Motor         17        
// Gyro                 Gyroscope     21
//         
// pneumaticIntake      pneumatics    G
// Intake               Motor         2
//
// CataLeft             Motor         6                
// CataRight            Motor         3
//
// pneumaticWing        pneumatics    H
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
allianceColor matchColor;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void setprogram(void) {  
  bool pressed = false;
  
  Controller.Screen.newLine();
  Controller.Screen.print("color: Red(a) Blue(b)      ");

  while(!pressed){
    if(Controller.ButtonA.pressing()){
      matchColor = redAlliance;
      pressed=true;
    }
    if(Controller.ButtonB.pressing()){
      matchColor = blueAlliance;
      pressed=true;
    }
  }

  Controller.Screen.clearLine();

  switch (matchColor) {
  case redAlliance:
    Brain.Screen.print("Red Alliance Selected");
    break;
  
  case blueAlliance:
    Brain.Screen.print("Blue Alliance Selected");
    break;

  default:
    setprogram();
    break;
  }
  
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  //setprogram();

  if(Brain.SDcard.isInserted()){
    Brain.Screen.drawImageFromFile("Logo2.png",0,0);
  }

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

event checkGameElement = event();

void hasGameElementCallback() {
  Brain.Screen.setFont(mono40);
  Brain.Screen.clearLine(1, black);
  Brain.Screen.clearLine(2,black);
  Brain.Screen.setCursor(Brain.Screen.row(), 1);
  Brain.Screen.setCursor(1, 1);

  aivis.takeSnapshot(aivision::ALL_AIOBJS);
  if (aivis.objectCount > 0) {
    Brain.Screen.print("Game Element Found");
    Brain.Screen.newLine();
    Brain.Screen.print(aivis.largestObject.id);
  } else {
    Brain.Screen.print("No Game Element Found");
  }
}

void hasMogoCallback() {
  Brain.Screen.setFont(mono40);
  Brain.Screen.clearLine(1, black);
  Brain.Screen.setCursor(Brain.Screen.row(), 1);
  Brain.Screen.setCursor(1,1);

  aivis.takeSnapshot(aivision::ALL_AIOBJS);
  if (aivis.largestObject.id == mobileGoal) {
    Brain.Screen.print("Mogo Found");
  } else {
    Brain.Screen.print("NO Mogo Found");
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  robot.autonomous();
  
  test();
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  checkGameElement(hasGameElementCallback);

  double LNS; double LEW;
  double RNS; double REW;
  while (1) {
    //checkGameElement.broadcastAndWait();

    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    if(Controller.ButtonA.pressing()){ // shift key
      if(Controller.ButtonUp.pressing()){ // toggles between 
        robot.switchControlMode();
      }
    }

    if(Controller.ButtonB.pressing()) {
      robot.toggleMogoClamp();
    }

    if(Controller.ButtonL1.pressing()){
      robot.runIntake();
    } else if (Controller.ButtonL2.pressing()) {
      robot.runReversedIntake();
    } else {
      robot.stopIntake();
    }

    if(Controller.ButtonR1.pressing()){
      robot.ladybrownForward();
    } else if (Controller.ButtonR2.pressing()){
      robot.ladybrownBackward();
    } else {
      robot.ladybrownStop();
    }

    int scale = 95;
    double multiplier = 100/cbrt(scale);    
    LNS = cbrt(Controller.Axis3.position())*multiplier;
    LEW = cbrt(Controller.Axis4.position())*multiplier;
    RNS = cbrt(Controller.Axis2.position())*multiplier;
    REW = cbrt(Controller.Axis1.position())*multiplier;    

    robot.drive(LNS,LEW,RNS,REW);

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
