/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       threeWheelSide.hpp                                        */
/*    Author:       Nathan Beals                                              */
/*    Created:      Thurs Nov 21                                              */
/*    Description:  file for storing threeWheelSide class declerations        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef THREEWHEELSIDE_HPP
#define THREEWHEELSIDE_HPP

using namespace vex;

class threeWheelSide: public wheelSide{
    private:
        motor* front;
        motor* middle;
        motor* back;

        double gearRatio;
        double wheelCircumference;
        double motorConversion;

    public:

        /**
         * @brief
         * 
         * @param gearratio
         * @param wheelDiameter
         */
        threeWheelSide(
            motor* Frontm,
            motor* Middlem,
            motor* Backm,
            double gearratio,
            double wheelDiameter
        );
        ~threeWheelSide();

        /*---------------------------------------------------------------------------*/
        /*-----------------------Drivetrain Utility Functions------------------------*/
        /*---------------------------------------------------------------------------*/

        double getMotorAve();
        void resetDrivePositions();
        void stopDriveSide(brakeType Brake);
        void setVelocity(double velocity, velocityUnits units);
        double getMotorWattage();

        /*---------------------------------------------------------------------------*/
        /*----------------------------DriveSide Movements----------------------------*/
        /*---------------------------------------------------------------------------*/

        void spinTo(double rotation, double velocity, velocityUnits units, bool waitForCompletion);
        void spin(directionType dir, double velocity, velocityUnits units);

};

#endif