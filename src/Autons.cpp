/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       Autons.h                                                  */
/*    Author:       Nathan Beals                                              */
/*    Created:      Sun March 17 2024                                         */
/*    Description:  file for storing autonomous programs                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

double tileLength = 23.5; //inches

int ticks = 0;
bool intakeOn = false;
bool passedRampUP = false;
int jamVelocity = 5;

void runIntake(void) {
  while (true){
    if(intakeOn){
      robot.runIntake();
      if(!passedRampUP && robot.frontIntake->getVelocity() > jamVelocity){
        passedRampUP = true;
        
      }
      if(passedRampUP && robot.frontIntake->getVelocity()<jamVelocity){
        robot.frontIntake->unJam();
        passedRampUP = false;
        wait(100, msec);

      }
    } else{
      robot.stopIntake();
    }
  }
}

bool skillsloaded = false; 
void skillsLinetrackerCallback(void) {
  Brain.Screen.print("Line switch Triggered");
  Brain.Screen.newLine();

  intakeOn = false;

  if (!skillsloaded) { // hook is unloaded;
    skillsloaded = true;
    robot.hookConveyor->loadRing();

  } else { // hook is loaded and needs to be unloaded first
    waitUntil(robot.hasMogo()); // needs mogo to be attatched first
    wait(1, sec); // buffer time for mogo to settle
    robot.hookConveyor->resetCycle(1); //score current loaded ring
    skillsloaded = false;

    skillsLinetrackerCallback(); // call function again to load new ring
  }
  intakeOn = true;
}

void test(){
  thread intakeThread = thread(runIntake);
  intakeOn = true;
}

void match15(){

}

void skills15(){

}

void match24(){
  robot.hookConveyor->loadRing();

  robot.driveT->driveStraight(tileLength*sqrt(2), 5);
  waitUntil(!robot.driveT->Moving());
  robot.toggleMogoClamp();
  wait(300, msec);

  robot.hookConveyor->resetCycle(1);
  wait(300, msec);

  robot.driveT->gyroTurn(1, 180);
  waitUntil(!robot.driveT->Moving());

  robot.driveT->driveStraight(100, 90);
  waitUntil(!robot.driveT->Moving());

}

//note 1 tile = 23.56 in

void skills24(){
    linetracker.low(skillsLinetrackerCallback);
    robot.driveT->sensors->resetRotation();
    robot.driveT->resetDrivePositions();

    //drive straight & grab ring
    robot.frontIntake->run(fwd);
    robot.driveT->driveStraight(30, 10);
    waitUntil(!robot.driveT->Moving());
    wait(100, msec);
    
    // turn to grab other ring
    robot.driveT->gyroTurn(1, 45);
    waitUntil(!robot.driveT->Moving());
    if(!skillsloaded){
      skillsLinetrackerCallback();
    }
    wait(300, msec);

    // drive straight & grab ring
    robot.driveT->driveStraight(30, tileLength*sqrt(2));
    waitUntil(!robot.driveT->Moving());
    wait(300, msec);
    

    // line up to grab mobile goal
    robot.driveT->gyroTurn(1, 45);
    waitUntil(!robot.driveT->Moving());

    //move backward & grab goal
    robot.driveT->driveStraight(-40, tileLength);
    waitUntil(!robot.driveT->Moving());
    wait(300, msec);
    robot.toggleMogoClamp();
    robot.driveT->gyroTurn(2, 60);
    robot.hookConveyor->resetCycle(1);
    robot.hookConveyor->resetCycle(1);
    robot.frontIntake->stop();

    // line up to score goal
    waitUntil(!robot.driveT->Moving());
    robot.frontIntake->stop();
    wait(500, msec);

    robot.driveT->sensors->resetRotation();
    robot.toggleMogoClamp();
    // move to goal zone
    robot.driveT->driveStraight(-50, sqrt(pow(tileLength,2)+pow(2*tileLength, 2)));
    waitUntil((!robot.driveT->Moving()) || (robot.driveT->getVelocities() > -10));
    wait(200, msec);

    double heading = robot.driveT->sensors->getRotation();
    if(heading<0){
      robot.driveT->gyroTurn(2, -heading);      
    } else{
      robot.driveT->gyroTurn(1, heading);      
    }
    waitUntil(!robot.driveT->Moving());

    robot.driveT->driveStraight(70, 27);
    waitUntil(!robot.driveT->Moving());
    wait(200, msec);

    //robot.hookConveyor->resetCycle(1);
    //robot.hookConveyor->loadRing();

    
    robot.driveT->gyroTurn(2, 15);
    waitUntil(!robot.driveT->Moving());   
    wait(200, msec);

    
    robot.frontIntake->run(fwd);
    robot.driveT->driveStraight(50, tileLength*2.5);
    waitUntil(!robot.driveT->Moving());
    robot.frontIntake->stop();
    wait(200, msec);

    /*
    robot.driveT->gyroTurn(2, 90);
    waitUntil(!robot.driveT->Moving());
    robot.frontIntake->stop();

    robot.driveT->driveStraight(-50, tileLength);
    waitUntil(!robot.driveT->Moving());
    robot.toggleMogoClamp();
    wait(200, msec);

    robot.frontIntake->run(fwd);
    robot.driveT->driveStraight(50, tileLength);
    robot.hookConveyor->resetCycle(1);
    robot.hookConveyor->resetCycle(1);
    waitUntil(!robot.driveT->Moving());

    robot.driveT->gyroTurn(2, 120);
    waitUntil(!robot.driveT->Moving());
    wait(300, msec);
    robot.toggleMogoClamp();

    // move to goal zone
    robot.driveT->driveStraight(-50, sqrt(pow(tileLength,2)+pow(2*tileLength, 2)));
    waitUntil((!robot.driveT->Moving()) || (robot.driveT->getVelocities() > -5));
    wait(200, msec);
    robot.frontIntake->stop();
  
    robot.driveT->driveStraight(70, tileLength*sqrt(2));
    waitUntil(!robot.driveT->Moving());
    wait(200, msec);

    /*

    
    */
}