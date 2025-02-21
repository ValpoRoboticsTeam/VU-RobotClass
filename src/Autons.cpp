/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       Autons.h                                                  */
/*    Author:       Nathan Beals                                              */
/*    Created:      Sun March 17 2024                                         */
/*    Description:  file for storing autonomous programs                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

double tileLength = 23.56; //inches

void test(){
  robot.driveT->driveStraight(40, tileLength);
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
    robot.driveT->sensors->resetRotation();
    robot.driveT->resetDrivePositions();
    
    //drive straight & grab ring
    robot.runPureIntake();
    robot.driveT->driveStraight(30, tileLength/2);
    waitUntil(!robot.driveT->Moving());
    robot.stopIntake();
    
    // turn to grab other ring
    robot.driveT->gyroTurn(1, 40);
    robot.hookConveyor->loadRing();
    wait(1, sec);

    // drive straight & grab ring
    robot.runPureIntake();
    robot.driveT->driveStraight(30, tileLength*sqrt(2));
    waitUntil(!robot.driveT->Moving());
    robot.stopIntake();
    wait(1, sec);

    // line up to grab mobile goal
    robot.driveT->gyroTurn(1, 40);
    wait(1, sec);

    //move backward & grab goal
    robot.driveT->driveStraight(-40, tileLength);
    waitUntil(!robot.driveT->Moving());
    robot.toggleMogoClamp();
    wait(500, msec);

    // line up to score goal
    robot.driveT->gyroTurn(1, 90+sin(1/2));
    robot.hookConveyor->resetCycle(1);
    robot.runIntake();
    wait(1, sec);
    robot.stopIntake();


    // move to goal zone
    robot.runPureIntake();
    robot.driveT->driveStraight(50, tileLength);
    waitUntil(!robot.driveT->Moving());
    robot.stopIntake();
    wait(1, sec);

    // back up
    robot.driveT->driveStraight(-40, tileLength*sqrt(2)/2);
    waitUntil(!robot.driveT->Moving());

    // turn around
    robot.driveT->gyroTurn(1, 180);
    waitUntil(!robot.driveT->Moving());

    // back into zone
    robot.driveT->driveStraight(-40, tileLength*sqrt(2)/2);
    waitUntil(!robot.driveT->Moving());

    // drop mogo & drive away
    robot.toggleMogoClamp();
    robot.driveT->driveStraight(70, tileLength*sqrt(2)/2);
    waitUntil(!robot.driveT->Moving());

}