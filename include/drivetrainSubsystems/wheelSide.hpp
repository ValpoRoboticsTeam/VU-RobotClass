/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       wheelSide.hpp                                             */
/*    Author:       Nathan Beals                                              */
/*    Created:      Sun March 17 2024                                         */
/*    Description:  file for storing wheelSide super class code               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef WHEELSIDE_HPP
#define WHEELSIDE_HPP

using namespace vex;

class wheelSide {
    private:
        int numOfWheels;
        
    public:
        wheelSide(int wheels);
        ~wheelSide();
        int getNumOfWheels();

        /*---------------------------------------------------------------------------*/
        /*-----------------------Drivetrain Utility Functions------------------------*/
        /*---------------------------------------------------------------------------*/

        /**
         * @brief gets an average position of all motors
        */
        virtual double getMotorAve() = 0;

        /**
         * @brief resets all driveTrain encoders
        */
        virtual void resetDrivePositions() = 0;
        
        /**
         * @brief stops all motors in the drivetrain
        */
        virtual void stopDriveSide(brakeType Brake) = 0;

        /**
         * @brief sets velocities of all motors in drivetrain
        */
        virtual void setVelocity(double velocity, velocityUnits units) = 0;

        /**
         * @brief gets an average Wattage of all motors
        */
        virtual double getMotorWattage() = 0;

        /*---------------------------------------------------------------------------*/
        /*----------------------------DriveSide Movements----------------------------*/
        /*---------------------------------------------------------------------------*/

        /**
         * @brief moves drivetrain forward to a certain point
         * 
         * @param rotation
         * @param velocity
         * @param untits
         * @param waitForCompletion
         */
        virtual void spinTo(double rotation, double velocity, velocityUnits units, bool waitForCompletion) = 0;
        
        /**
         * @brief Spins motor in a direction at a specified velocity
         * 
         * @param dir
         * @param velocity
         * @param units
         */
        virtual void spin(directionType dir, double velocity, velocityUnits units) = 0;
};

#endif