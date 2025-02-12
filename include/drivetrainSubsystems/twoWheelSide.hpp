/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       twoWheelSide.hpp                                          */
/*    Author:       Nathan Beals                                              */
/*    Created:      Sun March 17 2024                                         */
/*    Description:  file for storing twoWheelSdie class declerations          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef TWOWHEELSIDE_HPP
#define TWOWHEELSIDE_HPP

using namespace vex;

class twoWheelSide: public wheelSide{
    private:
        motor* front;
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
        twoWheelSide(
            motor* Frontm,
            motor* Backm,
            double gearratio,
            double wheelDiameter
        );

        ~twoWheelSide();

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