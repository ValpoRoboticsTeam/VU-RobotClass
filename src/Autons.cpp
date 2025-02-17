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
    drive.driveStraight(2, tileLength, 40);
}

void match(){

}

void match24(){
  drive.driveStraight(2, 5, tileLength*sqrt(2));
  robot.toggleMogoClamp();
  wait(500, msec);

  robot.runIntake();
  wait(700,msec);

  robot.stopIntake();
  wait(500, msec);

  drive.gyroTurn(1, 180);
  wait(500, msec);

  drive.driveStraight(2, 90, 100);
}

//note 1 tile = 23.56 in

void skills24(){
    driveSensors.resetRotation();
    drive.resetDrivePositions();
    
    robot.runPureIntake();
    drive.driveStraight(1, tileLength/2, 30);
    
    wait(1500, msec);
    robot.stopIntake();
    
    drive.gyroTurn(1, 40);
    robot.hookConveyor->loadRing();
    wait(1, sec);

    robot.runPureIntake();
    drive.driveStraight(1, tileLength*sqrt(2), 30);
    robot.stopIntake();
    wait(1, sec);


    drive.gyroTurn(1, 40);
    wait(1, sec);

    drive.driveStraight(2, tileLength, 40);
    wait(500, msec);

    robot.toggleMogoClamp();
    drive.gyroTurn(2, 45);
    wait(1, sec);

    drive.driveStraight(2, tileLength, 90);

}

void skills15(){

}