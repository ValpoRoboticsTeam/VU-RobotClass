/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       fourWheelSide.hpp                                         */
/*    Author:       Nathan Beals                                              */
/*    Created:      Mon Dec 2                                                 */
/*    Description:  file for storing fourWheelSide class declerations         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef FOURWHEELSIDE_HPP
#define FOURWHEELSIDE_HPP

using namespace vex;

class fourWheelSide: public wheelSide{
    private:
        motor* front;
        motor* fmiddle;
        motor* bmiddle;
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
        fourWheelSide(
            motor* Frontm,
            motor* Middlem1,
            motor* Middlem2,
            motor* Backm,
            double gearratio,
            double wheelDiameter
        );
        ~fourWheelSide();

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