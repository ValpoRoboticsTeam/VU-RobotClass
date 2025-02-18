/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       drivetrain.hpp                                            */
/*    Author:       Nathan Beals                                              */
/*    Created:      Sun March 17 2024                                         */
/*    Description:  file for storing drivetrain class declerations            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef DRIVETRAIN_HPP
#define DRIVETRAIN_HPP

using namespace vex;

class driveTrain{
    private:

        wheelSide* leftSide;
        wheelSide* rightSide;

        double MotorOffset;
        double gearRatio;
        double wheelCircumference;
        double motorConversion;
        double deadzone = 5;

        double leftpos;
        double rightpos;

        // Classifications for User Control Modes
        enum UserControlMode {
            tankDrive,
            arcadeDrive
        };

        UserControlMode controlMode = arcadeDrive;
        void setControlMode(UserControlMode mode){controlMode = mode;}
        UserControlMode getControlMode() {return controlMode;}

        /**
         * @brief checks weather the joysticks are outside of the robot's deadzone
         * @param x the input value of the controller that's being checked
         */
        bool withinDeadzone(int x);


        /* ----------  Movement functions for PID algorithms ----------- */

        /**
         * @brief 
         * 
         * @param dir
         * @param leftVelocity
         * @param rightVelocity
         */
        void pointTurn(int dir, double turnVelocity);


    public:
        sensorUnit* sensors;

        driveTrain();

        /**
         * @brief
         * 
         * @param robotlength
         * @param gearratio
         * @param wheelDiameter
         */
        driveTrain(
            motor* FrontLeft, motor* FrontRight,
            motor* BackLeft, motor* BackRight,
            sensorUnit* senosrs,
            double robotlength,
            double gearratio,
            double wheelDiameter
        );

        /**
         * @brief
         * 
         * @param robotlength
         * @param gearratio
         * @param wheelDiameter
         */
        driveTrain(
            motor* FrontLeft, motor* FrontRight,
            motor* MiddleLeft, motor* MiddleRight,
            motor* BackLeft, motor* BackRight,
            sensorUnit* senosrs,
            double robotlength,
            double gearratio,
            double wheelDiameter
        );

        /**
         * @brief
         * 
         * @param robotlength
         * @param gearratio
         * @param wheelDiameter
         */
        driveTrain(
            motor* FrontLeft, motor* FrontRight,
            motor* FrontMiddleLeft, motor* FrontMiddleRight,
            motor* BackMiddleLeft, motor* BackMiddleRight,
            motor* BackLeft, motor* BackRight,
            sensorUnit* senosrs,
            double robotlength,
            double gearratio,
            double wheelDiameter
        );

        ~driveTrain();

        /*---------------------------------------------------------------------------*/
        /*-----------------------Drivetrain Utility Functions------------------------*/
        /*---------------------------------------------------------------------------*/

        /**
         * @brief
         */
        void autostraight(double input, double* leftspeedinput, double* rightspeedinput);
        
        /**
         * @brief gets an average position of all motors
        */
        double getMotorAve();
        
        /**
         * @brief resets Drivetrain encoders
        */
        void resetDrivePositions();

        /**
         * @brief stops all motors in the drivetrain
         * @param Brake the braketype to stop with
        */
        void stopDriveTrain(brakeType Brake);

        /**
         * @brief sets velocities of all motors in drivetrain
         * @param velocity the velocity of the drivetrain in units
         * @param units the units of velocity in; pct, rpm, or dps
        */
        void setVelocities(double velocity, velocityUnits units);

        /**
         * @brief gets the current heading of the robot
         * @param dir specifies whether the robot is looking left or right
         */
        double getHeading(int dir){
            return sensors->getHeading(dir);
        }

        /*---------------------------------------------------------------------------*/
        /*-------------------------------PID ALROGITHMS------------------------------*/
        /*---------------------------------------------------------------------------*/

        /**
         * @brief
         * 
         * @param desiredPos
         */
        void drivePD(double desiredPos);

        /**
         * @brief
         * 
         * @param desiredPos
         */
        void arcPD(double desiredPos, int dir, double radius, double theta);        

        /**
         * @brief 
         * 
         * @param dir
         * @param desiredPos
         */
        void gyroTurn(int dir, double desiredPos);


        /*---------------------------------------------------------------------------*/
        /*----------------------------Drivetrain Movements---------------------------*/
        /*---------------------------------------------------------------------------*/

        /**
         * @brief
         * 
         * @param dir
         * @param theta
         * @param velocity
         */
        void sidePivot(int dir, double theta, double velocity);

        /**
         * @brief
         * 
         * @param dir
         * @param desiredPos
         * @param velocity
         */
        void driveStraight(double velocity, double desiredPos);

        /**
         * @brief
         * 
         * @param dir
         * @param radius
         * @param theta
         * @param velocity
         */
        void driveArc(int dir, double radius, double theta, double velocity);
        


        /*-------------------------------------------------------------------------------*/
        /*-----------------------------Specialty PID Movements---------------------------*/
        /*-------------------------------------------------------------------------------*/

        /**
         * 
         */
        void MogoRush();
        
        /*-------------------------------------------------------------------------------*/
        /*----------------------------Driver Control Movements---------------------------*/
        /*-------------------------------------------------------------------------------*/

        /**
         * @brief toggles the drivetrain between Tank Drive and Arcade Drive Control Modes. Drive Train starts in Tank Drive Mode.
         */
        void switchControlMode(){
            if(controlMode == tankDrive){
                setControlMode(arcadeDrive);
            } else {
                setControlMode(tankDrive);
            }
        }

        /**
         * @brief checks if the joystick inputs are correct and moves accordingly
         */
        int drive(double leftNS, double leftEW, double rightNS, double rightEW);

};

aivision::object* findMogo();

bool hasMogo();

#endif