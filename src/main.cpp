/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
allianceColor matchColor;

int CD = 25;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */  //8==D
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */ //penits
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/


void resetHookCallback(void){
  robot.hookConveyor->resetCycle(0);
}

void ringScoreCallback(void){
  robot.hookConveyor->resetCycle(1);
}

bool loaded = false; bool automated = true;
void linetrackerCallback(void) {
  Brain.Screen.print("Line switch Triggered");
  Brain.Screen.newLine();

  if(automated){
    if (!loaded) { // hook is unloaded;
      loaded = true;
      robot.hookConveyor->loadRing();

    } else { // hook is loaded and needs to be unloaded first
      waitUntil(robot.hasMogo()); // needs mogo to be attatched first
      wait(1, sec); // buffer time for mogo to settle
      ringScoreCallback(); //score current loaded ring
      loaded = false;
      
      linetrackerCallback(); // call function again to load new ring

    }
  }
}

void toggleAutomation(void) {
  robot.toggle_HookManualOverride();
  if(automated){automated = false;}else{automated = true;}
}

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

  //robot.hookConveyor->loadRing();
  if(Brain.SDcard.isInserted()){
    Brain.Screen.drawImageFromFile("Logo2.png",0,0);
  }

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
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
  // Insert autonomous user code here.

  bool testing = true;
  bool bigbot = true;
  bool match = true;

  //test();

  if(testing){
    test();
  } else{
    if(bigbot){
      if(match){
        match24();
      } else {
        skills24();
      }
    } else {
      if(match){
        match15();
      } else {
        skills15();
      }
    }
  }

  //robot.toggleMogoClamp();
  //robot.loadRing();
  //linetracker.low(linetrackerCallback);
  
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
  //checkGameElement(hasMogoCallback);
  linetracker.low(linetrackerCallback);
  //Controller.ButtonL1.released(resetHookCallback);
  //Controller.ButtonL2.released(resetHookCallback);
  Controller.ButtonR1.released(ringScoreCallback);
  Controller.ButtonX.released(toggleAutomation);

  //coordinate StakeCoords;
  //StakeCoords.x=0;
  //StakeCoords.y=0;

  //wallStake stake1(blueAlliance, 0,0);
  //wallStake stake2(blueAlliance, StakeCoords);

  int charge = CD;
  int speedLimit = 85;

  double LNS; double LEW;
  double RNS; double REW;
  while(true){
    //checkGameElement.broadcastAndWait();

    //int scale = 95;
    //double multiplier = 100/cbrt(scale);

    if (Controller.Axis3.position() > speedLimit){LNS = speedLimit;}else{LNS = Controller.Axis3.position();}
    if (Controller.Axis4.position() > speedLimit){LEW = speedLimit;}else{LEW = Controller.Axis4.position();}
    if (Controller.Axis2.position() > speedLimit){RNS = speedLimit;}else{RNS = Controller.Axis2.position();}
    if (Controller.Axis1.position() > speedLimit){REW = speedLimit;}else{REW = Controller.Axis1.position();}
    
    //LNS = cbrt(LNS)*multiplier;
    //LEW = cbrt(LEW)*multiplier;
    //RNS = cbrt(RNS)*multiplier;
    //REW = cbrt(REW)*multiplier;    

    //robot.drive(LNS,LEW,RNS,REW);

    if(Controller.ButtonR2.pressing()){
      if(Controller.ButtonUp.pressing()){
        robot.switchControlMode();
      }
    } else {
      if(charge> CD){
        if(Controller.ButtonB.pressing()) {
          robot.toggleMogoClamp();
          charge = 0;
        }
      }

      if(Controller.ButtonL1.pressing()){
        robot.runIntake();
      } else if (Controller.ButtonL2.pressing()) {
        robot.runReversedIntake();
      } else {
        robot.stopIntake();
      }
      
    }

    charge++;
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
