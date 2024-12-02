#include "vex.h"
using namespace vex;

Robot::Robot(
    driveTrain *dt,
    clamp* MC
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

/* Expansion */