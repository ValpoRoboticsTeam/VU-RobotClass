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
    sensorControler = nullptr;

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
    sensorControler = senosrs;

    MotorOffset = robotlength/2;
    gearRatio = gearratio;
    wheelCircumference = wheelDiameter*M_PI;

    motorConversion = gearRatio*(wheelCircumference)/(360);

    leftSide = new twoWheelSide(FrontLeft, BackLeft, gearratio, wheelDiameter);
    rightSide = new twoWheelSide(FrontRight, BackRight, gearratio, wheelDiameter);    
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
    sensorControler = senosrs;

    MotorOffset = robotlength/2;
    gearRatio = gearratio;
    wheelCircumference = wheelDiameter*M_PI;

    motorConversion = gearRatio*(wheelCircumference)/(360);


    leftSide = new threeWheelSide(FrontLeft, MiddleLeft, BackLeft, gearratio, wheelDiameter);
    rightSide = new threeWheelSide(FrontRight, MiddleRight, BackRight, gearratio, wheelDiameter);    
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
    sensorControler = senosrs;

    MotorOffset = robotlength/2;
    gearRatio = gearratio;
    wheelCircumference = wheelDiameter*M_PI;

    motorConversion = gearRatio*(wheelCircumference)/(360);

    Brain.Screen.print("%f * %f / 360 = %f ", gearRatio, wheelCircumference, motorConversion );
    Brain.Screen.newLine();

    leftSide = new fourWheelSide(FrontLeft, FrontMiddleLeft, BackMiddleLeft, BackLeft, gearratio, wheelDiameter);
    rightSide = new fourWheelSide(FrontRight, FrontMiddleRight, BackMiddleRight, BackRight, gearratio, wheelDiameter);    
}

driveTrain::~driveTrain(){}

/*---------------------------------------------------------------------------*/
/*-----------------------Drivetrain Utility Functions------------------------*/
/*---------------------------------------------------------------------------*/


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
}

void driveTrain::setVelocities(double velocity, velocityUnits units){
    leftSide->setVelocity(velocity, units);
    rightSide->setVelocity(velocity, units);
}


/*---------------------------------------------------------------------------*/
/*----------------------------Drivetrain Movements---------------------------*/
/*---------------------------------------------------------------------------*/

void driveTrain::sidePivot(int dir, double theta, double velocity){
    resetDrivePositions();
    bool complete = false; sensorControler->resetHeading(); double errorOffset=4;
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

void driveTrain::driveStraight(int dir, double desiredPos, double velocity){

    resetDrivePositions();
    bool complete = false; double ave; double errorOffset = 5; 
    double goal = desiredPos/motorConversion;
    
    while(!complete){
        switch (dir){
        case 1: // forward movement
            leftSide->spin(forward, velocity, velocityUnits::pct);
            rightSide->spin(forward, velocity, velocityUnits::pct);
            break;
        case 2:
            leftSide->spin(reverse, velocity, velocityUnits::pct);
            rightSide->spin(reverse, velocity, velocityUnits::pct);
            break;
        default:            
            stopDriveTrain(hold);
            complete=true;
            break;
        }
        ave = getMotorAve();
        if (goal-errorOffset < ave && goal+errorOffset > ave ){
                
                complete = true;
        }
    }

    stopDriveTrain(hold);
}

void driveTrain::driveArc(int dir, double radius, double theta, double velocity){
    resetDrivePositions();
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

    resetDrivePositions();
    sensorControler->resetHeading();

    while(errorCount<3){

        progress = getMotorAve();
        ang = sensorControler->getRotation();

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
    double kp = 0.6; // controls how fast the program's rise time 
    double kd = 0.05; // controls how fast the program reacts to approaching the targes


    double error; // desirec Value - sensor value
    double prev_Error = 0; // Error of last loop ran
    double derivative; // Error - prevError
    double MotorSpeed;
    int errorCount = 0;

    resetDrivePositions();
    sensorControler->resetRotation();

    //initial punch so gyro goes in the correct direction
    //pointTurn(dir, 75);
    //wait(30, msec);

    while (errorCount<5){
        // calculate error
        error = desiredPos - abs(sensorControler->getRotation());

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
        if (aivis.installed()) { // take snapshot for ai vision sensor
            aivis.takeSnapshot(aivision::ALL_AIOBJS);
        } else {
            vis.takeSnapshot(MOGO); // take snapshot for older vision sensor
        }

        if (vis.objectCount > 0){

            double X; double Y;
            if (aivis.installed()) { //mogo coordinates for ai vision sensor
                aivision::object* mogo = findMogo();
                X = mogo->centerX; 
                Y = mogo->centerY;
            } else { //mogo coordinates for older vision sensor
                X = vis.largestObject.centerX;
                Y = vis.largestObject.centerY;
            }

            Brain.Screen.clearScreen();
            Brain.Screen.setCursor(1,1);
            Brain.Screen.print("Mogo coors:");
            Brain.Screen.newLine();
            Brain.Screen.print("x: ");
            Brain.Screen.print(X);
            Brain.Screen.newLine();
            Brain.Screen.print("y: ");
            Brain.Screen.print(Y);

            double speed = (Ytarget-Y)*(100/Ytarget);

            if (X < (centerFOV - offsetX)) { //drift to the left
                double drift = (centerFOV - X)/XMAX;
                scaleR = 1;
                scaleL = 1 - drift;

            
            } else if (X > (centerFOV + offsetX)) { // drift to the right
                double drift = (X - centerFOV)/XMAX;
                scaleR = 1;
                scaleL = 1 - drift;
            
            } 

            leftSpeed = speed*scaleL;
            rightSpeed = speed*scaleR;

            leftSide->spin(fwd, leftSpeed, velocityUnits::pct);
            rightSide->spin(fwd, rightSpeed, velocityUnits::pct);
            wait(30, msec);

            if ((Y > Ytarget) && 
                ((X >= (centerFOV - offsetX)) || 
                (X <= (centerFOV + offsetX)))) {
                errorcount++;
            }

        } else {
            pointTurn(1, 20);
            wait(30, msec);
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
            leftPower = leftNS + leftEW;
            rightPower = rightNS - rightEW;
        } else if(getControlMode() == arcadeDrive) { 
            leftPower = leftNS + rightEW*0.70;
            rightPower = leftNS - rightEW*0.70;
        }

        leftSide->spin(fwd, leftPower, velocityUnits::pct);
        rightSide->spin(fwd, rightPower, velocityUnits::pct);
    }


    //Brain.Screen.clearLine();
    //Brain.Screen.print("North South Odom Pod value: ");
    //Brain.Screen.print(sensorControler->getPosNS());

    return 1;
}