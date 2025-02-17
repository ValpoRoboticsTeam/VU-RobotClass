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
  robot.driveT->driveStraight(2, tileLength, 40);
}

void match15(){

}

void match24(){
  robot.driveT->driveStraight(2, 5, tileLength*sqrt(2));
  robot.toggleMogoClamp();
  wait(500, msec);

  robot.runIntake();
  wait(700,msec);

  robot.stopIntake();
  wait(500, msec);

  robot.driveT->gyroTurn(1, 180);
  wait(500, msec);

  robot.driveT->driveStraight(2, 90, 100);
}

//note 1 tile = 23.56 in

void skills24(){
    robot.driveT->sensors->resetRotation();
    robot.driveT->resetDrivePositions();
    
    //drive straight & grab ring
    robot.runPureIntake();
    robot.driveT->driveStraight(1, tileLength/2, 30);
    
    wait(1500, msec);
    robot.stopIntake();
    
    // turn to grab other ring
    robot.driveT->gyroTurn(1, 40);
    robot.hookConveyor->loadRing();
    wait(1, sec);

    // drive straight & grab ring
    robot.runPureIntake();
    robot.driveT->driveStraight(1, tileLength*sqrt(2), 30);
    robot.stopIntake();
    wait(1, sec);

    // line up to grab mobile goal
    robot.driveT->gyroTurn(1, 40);
    wait(1, sec);

    //move backward & grab goal
    robot.driveT->driveStraight(2, tileLength, 40);
    wait(500, msec);
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
    robot.driveT->driveStraight(1, tileLength, 50);
    robot.stopIntake();
    wait(1, sec);

    // back up
    robot.driveT->driveStraight(2, tileLength*sqrt(2)/2, 40);
    wait(500, msec);

    // turn around
    robot.driveT->gyroTurn(1, 180);
    wait(500, msec);

    // back into zone
    robot.driveT->driveStraight(2, tileLength*sqrt(2)/2, 40);
    wait(300, msec);

    // drop mogo & drive away
    robot.toggleMogoClamp();
    robot.driveT->driveStraight(1, tileLength*sqrt(2)/2, 70);

}

void skills15(){

}