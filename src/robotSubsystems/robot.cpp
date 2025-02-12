#include "vex.h"
using namespace vex;

Robot::Robot(){
    coords.x=0;
    coords.y=0;
    driveT = nullptr;
    mogoClamp = nullptr;
    frontIntake = nullptr;
    hookConveyor = nullptr;
}

Robot::Robot(
    driveTrain *dt,
    clamp* MC,
    intake* I,
    conveyor* C
) {
    coords.x=0;
    coords.y=0;
    driveT = dt;
    mogoClamp = MC;
    frontIntake = I;
    hookConveyor = C;
}

Robot::~Robot(){}

int Robot::drive(double leftNS, double leftEW, double rightNS, double rightEW) {
    return driveT->drive(leftNS, leftEW, rightNS, rightEW);
}

/* Subsystem Controlls */

/* MOGO Clamp */

void Robot::toggleMogoClamp() {
    mogoClamp->toggle();
}

void Robot::runIntake() {
    frontIntake->run(fwd);
    hookConveyor->run(fwd);
}

void Robot::runReversedIntake() {
    frontIntake->run(reverse);
    hookConveyor->run(reverse);
}

void Robot::stopIntake() {
    frontIntake->stop();
    hookConveyor->stop();
}