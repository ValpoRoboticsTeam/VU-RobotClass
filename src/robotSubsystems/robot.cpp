#include "vex.h"
using namespace vex;

Robot::Robot(
    driveTrain *dt,
    clamp* MC,
    intake* I
) {
    coords.x=0;
    coords.y=0;
    driveT = dt;
    mogoClamp = MC;    
}

Robot::~Robot(){}

/* Drive Controlls */

int Robot::drive(double leftNS, double leftEW, double rightNS, double rightEW) {
    return driveT->drive(leftNS, leftEW, rightNS, rightEW);
}

/* Subsystem Controlls */

/* MOGO Clamp */

void Robot::toggleMogoClamp() {
    mogoClamp->toggle();
}

/* Intake Commands */

void Robot::runIntake() {
    frontIntake->runIntake();
}

void Robot::runReversedIntake() {
    frontIntake->runReversedIntake();
}
/* Expansion */

void Robot::autonomous(){
    //testing autonomous drive functions
    //driveT->driveStraight(1, 5, 15);      test successful
    //driveT->pointTurn(2,90,15);           test successful
    //driveT->sidePivot(1,90,15);           test successful
    //driveT->driveArc(1, 27, 90, 15);      test successful
    //driveT->gyroTurn(1, 90);              test successful
    //driveT->drivePD(35);                  test successful
    
}