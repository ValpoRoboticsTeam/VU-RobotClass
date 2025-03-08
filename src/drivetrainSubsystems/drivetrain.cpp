/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       drivetrain.cpp                                            */
/*    Author:       Nathan Beals                                              */
/*    Created:      Sun March 17 2024                                         */
/*    Description:  file for storing drivetrain class code                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
using namespace vex;

driveTrain::driveTrain(){
    sensors = nullptr;

    MotorOffset = 0;
    gearRatio = 0;
    wheelCircumference = 0;

    motorConversion = gearRatio*(wheelCircumference)/(360);

    leftSide = nullptr;
    rightSide = nullptr;    

}

driveTrain::driveTrain(
        motor* FrontLeft,   motor* FrontRight,
        motor* BackLeft,    motor* BackRight,
        sensorUnit* senosrs,
        double robotlength,
        double gearratio,
        double wheelDiameter
) {
    sensors = senosrs;

    MotorOffset = robotlength/2;
    gearRatio = gearratio;
    wheelCircumference = wheelDiameter*M_PI;

    motorConversion = gearRatio*(wheelCircumference)/(360);

    leftSide = new twoWheelSide(FrontLeft, BackLeft, gearratio, wheelDiameter);
    rightSide = new twoWheelSide(FrontRight, BackRight, gearratio, wheelDiameter);    

    isMoving = false;
}

driveTrain::driveTrain(
        motor* FrontLeft,   motor* FrontRight,
        motor* MiddleLeft,  motor* MiddleRight,
        motor* BackLeft,    motor* BackRight,
        sensorUnit* senosrs,
        double robotlength,
        double gearratio,
        double wheelDiameter
) {
    sensors = senosrs;

    MotorOffset = robotlength/2;
    gearRatio = gearratio;
    wheelCircumference = wheelDiameter*M_PI;

    motorConversion = gearRatio*(wheelCircumference)/(360);


    leftSide = new threeWheelSide(FrontLeft, MiddleLeft, BackLeft, gearratio, wheelDiameter);
    rightSide = new threeWheelSide(FrontRight, MiddleRight, BackRight, gearratio, wheelDiameter);    

    isMoving = false;
}

driveTrain::driveTrain(
        motor* FrontLeft,       motor* FrontRight,
        motor* FrontMiddleLeft, motor* FrontMiddleRight,
        motor* BackMiddleLeft,  motor* BackMiddleRight,
        motor* BackLeft,        motor* BackRight,
        sensorUnit* senosrs,
        double robotlength,
        double gearratio,
        double wheelDiameter
) {
    sensors = senosrs;

    MotorOffset = robotlength/2;
    gearRatio = gearratio;
    wheelCircumference = wheelDiameter*M_PI;

    motorConversion = gearRatio*(wheelCircumference)/(360);

    leftSide = new fourWheelSide(FrontLeft, FrontMiddleLeft, BackMiddleLeft, BackLeft, gearratio, wheelDiameter);
    rightSide = new fourWheelSide(FrontRight, FrontMiddleRight, BackMiddleRight, BackRight, gearratio, wheelDiameter);    

    isMoving = false;
}

driveTrain::~driveTrain(){}

/*---------------------------------------------------------------------------*/
/*-----------------------Drivetrain Utility Functions------------------------*/
/*---------------------------------------------------------------------------*/

void driveTrain::autostraight(double input, double* leftspeedinput, double* rightspeedinput){
    double dif = (leftSide->getMotorVelocity() - rightSide->getMotorVelocity());

    double leftspeed = *leftspeedinput;
    double rightspeed = *rightspeedinput;

    leftspeed = input - dif;
    rightspeed = input + dif;

    if(input >=0) {
        double max = 100;
        if (leftspeed > max){max = leftspeed;}
        if (rightspeed > max){max = rightspeed;}

        if(max > 100){
            leftspeed = leftspeed/max*100;
            rightspeed = rightspeed/max*100;
        }
        
    } else {
        double max = -100;
        if (leftspeed < max){max = leftspeed;}
        if (rightspeed < max){max = rightspeed;}

        if(max < -100){
            leftspeed = leftspeed/max*-100;
            rightspeed = rightspeed/max*-100;
        }
    }

    *leftspeedinput = leftspeed;
    *rightspeedinput = rightspeed;
}

void driveTrain::normalizeDriveSpeeds(double input, double* leftspeedinput, double* rightspeedinput){
    
    double leftspeed = *leftspeedinput;
    double rightspeed = *rightspeedinput;

    int limit = 100;                            // definition of max velocity
    int max = limit;                            // creation of limit
    if(input<0){leftspeed*=-1;rightspeed*=-1;}  // turn reverse velocity into fwd velocity for normalization

    if(leftspeed>=max){max=leftspeed;}          // determine the local maximum of which input is going over the max
    if(rightspeed>=max){max=rightspeed;}

    leftspeed = leftspeed/max*limit;        // scale all speeds to the local maximum
    rightspeed = rightspeed/max*limit;

    if(input<0){leftspeed*=-1;rightspeed*=-1;} // fwd velocity turns back into reverse velocity if needed.

    
}

double driveTrain::getMotorAve(){
    return (leftSide->getMotorAve()+
            rightSide->getMotorAve()
            )/2;
}

void driveTrain::resetDrivePositions(){
    leftSide->resetDrivePositions();
    rightSide->resetDrivePositions();
}

void driveTrain::stopDriveTrain(brakeType Brake){
    leftSide->stopDriveSide(Brake);
    rightSide->stopDriveSide(Brake);
    isMoving = false;
}

void driveTrain::setVelocities(double velocity, velocityUnits units){
    leftSide->setVelocity(velocity, units);
    rightSide->setVelocity(velocity, units);
}


/*---------------------------------------------------------------------------*/
/*----------------------------Drivetrain Movements---------------------------*/
/*---------------------------------------------------------------------------*/

void driveTrain::driveStraight(double velocity, double desiredPos){

    resetDrivePositions();
    isMoving = true;    bool complete = false; 
    double ave;         double errorOffset = 5; 
    double goal = desiredPos/motorConversion;

    double leftPower = 0;
    double rightPower = 0;
    
    while(!complete){
        autostraight(velocity, &leftPower, &rightPower);

        leftSide->spin(forward, leftPower, velocityUnits::pct);
        rightSide->spin(forward, rightPower, velocityUnits::pct);
        ave = getMotorAve();
        
        if (goal-errorOffset < ave && goal+errorOffset > ave ){
                complete = true;
        }
    }

    stopDriveTrain(hold);
}

void driveTrain::sidePivot(int dir, double theta, double velocity){
    resetDrivePositions();
    isMoving = true;
    bool complete = false; sensors->resetHeading(); double errorOffset=4;
    double ave; double head; double goal = theta*MotorOffset/motorConversion;
    
    while (!complete){
        switch (dir) {
        case 1: // Left turn
            rightSide->spin(forward, velocity, velocityUnits::pct);
            ave = rightSide->getMotorAve();
            break;
        case 2: // right turn
            leftSide->spin(forward, velocity, velocityUnits::pct);
            ave = leftSide->getMotorAve();
            break;
        default:
            stopDriveTrain(hold);
            complete=true;
            break;
        }
        head = getHeading(dir);
        if (((theta-errorOffset < head) && (head < theta+errorOffset)) ||
            ((goal-errorOffset < ave) && (ave < goal+errorOffset))){
                complete = true;
        }
    }
    stopDriveTrain(hold);    
}

void driveTrain::driveArc(int dir, double radius, double theta, double velocity){
    resetDrivePositions();
    isMoving = true;
    bool complete = false; double ave; double head; double errorOffset = 4; double goal = (theta*radius)/motorConversion; 
    double leftspeed; double rightspeed; double leftRadius; double rightRadius;
    
    switch(dir){
        case 1: // left
            leftRadius = radius-MotorOffset;
            rightRadius = radius+MotorOffset;
            break;
        case 2: // right
            leftRadius = radius+MotorOffset;
            rightRadius = radius-MotorOffset;
            break;
        default:
            leftRadius=1;
            rightRadius=1;
            break;
    }

    leftspeed = velocity*(leftRadius/radius);
    rightspeed = velocity*(rightRadius/radius);
    
    while(!complete){
        leftSide->spin(forward, leftspeed, velocityUnits::pct);
        rightSide->spin(forward, rightspeed, velocityUnits::pct);

        ave = ((leftSide->getMotorAve()*radius/leftRadius)+ 
               (rightSide->getMotorAve()*radius/rightRadius))/2;
        head = getHeading(dir);
        
        if (((theta-errorOffset < head) && (head < theta+errorOffset)) ||
            ((goal-errorOffset < ave) && (ave < goal+errorOffset))){
                complete = true;
        }
    }
    
    stopDriveTrain(hold);
}

/*---------------------------------------------------------------------------*/
/*-------------------------------PID ALROGITHMS------------------------------*/
/*---------------------------------------------------------------------------*/

/*-----------------------------DRIVE STRAIGHT PID----------------------------*/

void driveTrain::drivePD(double desiredPos){
    // control variables
    double kp = 0.35; // controls how fast the program's rise time 
    double kd = 0.1; // controls how fast the program reacts to approaching the targes
    double ka = 0.05; // controls how fast the program corrects drift


    // status tracking variables
    double goal = desiredPos/motorConversion;
    double error; // desirec Value - sensor value
    double prev_Error = 0; // Error of last loop ran
    double derivative; // Error - prevError
    double ang; // angle at which the bot has turned 
    double progress;
    double RightMotorSpeed; double LeftMotorSpeed;
    int errorCount=0;

    isMoving = true;
    resetDrivePositions();
    sensors->resetHeading();

    while(errorCount<3){

        progress = getMotorAve();
        ang = sensors->getRotation();

        error = goal-progress;

        derivative = error - prev_Error;
        LeftMotorSpeed = (error*kp) + (progress*kd) -(ang*ka);
        RightMotorSpeed = (error*kp) + (progress*kd) +(ang*ka);


        if (LeftMotorSpeed < 1 && LeftMotorSpeed > 0){LeftMotorSpeed=1;}
        if (LeftMotorSpeed > -1 && LeftMotorSpeed < 0){LeftMotorSpeed=-1;}
        if (RightMotorSpeed < 1 && RightMotorSpeed > 0){RightMotorSpeed=1;}
        if (RightMotorSpeed > -1 && RightMotorSpeed < 0){RightMotorSpeed=-1;}


        leftSide->spin(forward, LeftMotorSpeed, velocityUnits::pct);
        rightSide->spin(forward, RightMotorSpeed, velocityUnits::pct);

        prev_Error = error;
        if(error<5 && error>-5){
            errorCount++;
        }
    }
    stopDriveTrain(hold);
}

/*--------------------------------DRIVE ARC PID------------------------------*/

void driveTrain::arcPD(double desiredPos, int dir, double radius, double theta){
    /*
    // control variables
    double kp = 0.35; // controls how fast the program's rise time 
    double kd = 0.1; // controls how fast the program reacts to approaching the targes
    
    resetDrivePositions();
    bool complete = false; double ave; double head; double errorOffset = 4; 
    
    double turngoal = theta;
    
    double leftspeed; double rightspeed; double leftRadius; double rightRadius;
    double RightMotorSpeed; double LeftMotorSpeed;
    int errorCount=0;
    


    double fwdGoal = (theta*radius)/motorConversion;
    double fwdProgress;
    double fwdError; // desirec Value - sensor value
    double prevFwdError = 0; // Error of last loop ran
    double fwdDerivative; // Error - prevError

    double turnGoal = theta;
    double turnProgress;
    double turnError;
    double prevTurnError;
    double fwdDerivative;


    double LeftAvg;         double RightAvg;        double progress;
    double AveRSpeed;       double AveLSpeed;
    double RightMotorSpeed; double LeftMotorSpeed;
    int errorCount=0;


    switch(dir){
        case 1: // left
            leftRadius = radius-MotorOffset;
            rightRadius = radius+MotorOffset;
            break;
        case 2: // right
            leftRadius = radius+MotorOffset;
            rightRadius = radius-MotorOffset;
            break;
        default:
            leftRadius=1;
            rightRadius=1;
            break;
    }

    while (errorCount<3) {



        if(true){
            errorCount++
        }
    }

    stopDriveTrain(hold);
    */
}

/*-------------------------------GYRO TURN PID-------------------------------*/

void driveTrain::pointTurn(int dir, double turnVelocity){
    switch (dir) {
        case 1: // Left turn
            leftSide->spin(reverse, turnVelocity, velocityUnits::pct);
            rightSide->spin(forward, turnVelocity, velocityUnits::pct);
            break;
        case 2: // right turn
            leftSide->spin(forward, turnVelocity, velocityUnits::pct);
            rightSide->spin(reverse, turnVelocity, velocityUnits::pct);
            break;
        default:
            stopDriveTrain(hold);
            break;
    }
}

void driveTrain::gyroTurn(int dir, double desiredPos){
    double kp = 0.57; // controls how fast the program's rise time 
    double kd = 0.05; // controls how fast the program reacts to approaching the targes


    double error; // desirec Value - sensor value
    double prev_Error = 0; // Error of last loop ran
    double derivative; // Error - prevError
    double MotorSpeed;
    int errorCount = 0;

    resetDrivePositions();
    sensors->resetRotation();

    isMoving = true;

    //initial punch so gyro goes in the correct direction
    //pointTurn(dir, 75);
    //wait(30, msec);

    double maxErr = desiredPos - std::abs(sensors->getRotation());
    

    while (errorCount<5){
        // calculate error
        error = (desiredPos-std::abs(sensors->getRotation()))/maxErr*45;

        // calculate derivative
        derivative = error - prev_Error;

        // adjust motor speeds
        MotorSpeed = (error * kp) + (derivative*kd);

        
        if (MotorSpeed < 1 && MotorSpeed > 0){MotorSpeed=1;}
        if (MotorSpeed > -1 && MotorSpeed < 0){MotorSpeed=-1;}
        pointTurn(dir, MotorSpeed);

        prev_Error = error;
        if (error <3 && error > -3){
            errorCount++;
        }
    }
    stopDriveTrain(hold);
}

/*-------------------------------------------------------------------------------*/
/*-----------------------------Specialty PID Movements---------------------------*/
/*-------------------------------------------------------------------------------*/

aivision::object* findMogo() {
  for (int i = 1; i <= aivis.objectCount; i++) {
    if (aivis.objects[i].id == mobileGoal) {
        return &aivis.objects[i];
    }
  }
  return nullptr;
}

bool hasMogo() {
  if (aivis.installed()){
    for (int i = 1; i <= aivis.objectCount; i++) {
        if (aivis.objects[i].id == mobileGoal) {
            return true;
        }
    }
    return false;    
  } else {
    return (vis.objectCount > 0);
  }

}

void driveTrain::MogoRush() {
    resetDrivePositions();
    wait(20, msec);

    isMoving = true;
    double targetWidth = 49;

    int errorcount = 0;

    double YMAX;
    double XMAX;

    if (aivis.installed()){
        YMAX = 240; // max dimensions for ai vision sensor
        XMAX = 320;
    } else {
        YMAX = 212; // max dimensions for older vision sensor
        XMAX = 316;
    }


    double Ytarget = YMAX/2; // center Y FOV
    double centerFOV = XMAX/2; // center X FOV
    
    int offsetX = XMAX*0.1; // 10% of max FOV

    double leftSpeed;
    double rightSpeed;

    double scaleL = 1;
    double scaleR = 1;


    while (errorcount<3){
        aivis.takeSnapshot(aivision::ALL_AIOBJS);
        
        double X = aivis.largestObject.centerX;
        double Y = aivis.largestObject.width;

        double speed = (Y-targetWidth)*(100/targetWidth);

        if (X < (centerFOV - offsetX)) { //drift to the left
            double drift = (centerFOV - X)/XMAX;
            scaleR = 1 - drift;
            scaleL = 1;

        
        } else if (X > (centerFOV + offsetX)) { // drift to the right
            double drift = (X - centerFOV)/XMAX;
            scaleR = 1;
            scaleL = 1 - drift;
        
        } 

        leftSpeed = speed*scaleL*0.4;
        rightSpeed = speed*scaleR*0.4;

        leftSide->spin(reverse, leftSpeed, velocityUnits::pct);
        rightSide->spin(reverse, rightSpeed, velocityUnits::pct);
        wait(30, msec);

        if ((Y < targetWidth) && 
            ((X >= (centerFOV - offsetX)) || 
            (X <= (centerFOV + offsetX)))) {
            errorcount++;
            Brain.Screen.print(aivis.largestObject.width);
            Brain.Screen.newLine();
        
        }
    }
    stopDriveTrain(hold);
}

/*-------------------------------------------------------------------------------*/
/*----------------------------Driver Control Movements---------------------------*/
/*-------------------------------------------------------------------------------*/

bool driveTrain::withinDeadzone(int x){
    return ((x<deadzone) && (x> -deadzone));
}

int driveTrain::drive(double leftNS, double leftEW, double rightNS, double rightEW){

    double leftPower = 0; double rightPower = 0;
    if(withinDeadzone(leftNS)  && withinDeadzone(leftEW) && 
       withinDeadzone(rightNS) && withinDeadzone(rightEW))
    { //no joystick is telling the robot to move
        stopDriveTrain(hold);
        return 1;

    } else{ //if all joystick values are outside the deadzone
        if(getControlMode() == tankDrive){
            if(((leftNS - rightNS) < 10) && ((leftNS - rightNS) > -10)) {
                double dif = (leftSide->getMotorVelocity() - rightSide->getMotorVelocity());

                leftPower = (leftNS + leftEW) + dif;
                rightPower = (rightNS - rightEW) - dif;
            } else {
                leftPower = leftNS + leftEW;
                rightPower = rightNS - rightEW;
            }
        } else if(getControlMode() == arcadeDrive) { 
            if (withinDeadzone(rightEW)) {
                autostraight(leftNS, &leftPower, &rightPower);  
            } else {
                leftPower = leftNS + rightEW;
                rightPower = leftNS - rightEW;


                int limit = 100;
                int max = limit;
                if(leftNS<0){leftPower*=-1;rightPower*=-1;}

                if(leftPower>=max){max=leftPower;}
                if(rightPower>=max){max=rightPower;}

                if(max>= limit){
                    leftPower = leftPower/max*limit;
                    rightPower = rightPower/max*limit;
                } else {
                    leftPower = leftNS + rightEW*0.5;
                    rightPower = leftNS - rightEW*0.5;
                }

                if(leftNS<0){leftPower*=-1;rightPower*=-1;}
            }
        }


        if ((leftPower < 0) && (rightPower < 0)){
            leftPower *= 0.85;
            rightPower *= 0.85;
        }

        leftSide->spin(fwd, leftPower, velocityUnits::pct);
        rightSide->spin(fwd, rightPower, velocityUnits::pct);
    }

    return 1;
}