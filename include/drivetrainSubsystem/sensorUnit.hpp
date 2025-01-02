/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       sensorUnit.hpp                                            */
/*    Author:       Nathan Beals                                              */
/*    Created:      Fri Dec 6                                                 */
/*    Description:  file for storing Odom Sensor managment class declerations */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef SENSORUNIT_HPP
#define SENSORUNIT_HPP
using namespace vex;

class sensorUnit
{
    private:
        inertial* leftGyro;
        inertial* rightGyro;

        rotation* NSPod;
        rotation* EWPod;

    public:

        /**
         * @brief creates a new odomUnit to manage drivetrain sensors
         * 
         * @param gyro1 the left gyro
         * @param gyro2 the right gyro
         * @param pod1 The Pod facing North and South
         * @param pod2 The Pod facing East and West
         */
        sensorUnit(
            inertial* gyro1,
            inertial* gyro2,
            rotation* pod1,
            rotation* pod2
        );

        ~sensorUnit();

        /* GYRO FUNCTIONS */
        /**
         * @brief 
         */
        void resetRotation(){
            leftGyro->resetRotation();
            rightGyro->resetRotation();
            }

        /**
         * @brief resets the gyroscope's heading value to 0.
         */
        void resetHeading(){
            leftGyro->resetHeading();
            rightGyro->resetHeading();
        }

        /**
         * @brief 
         */
        double getRotation(){
            double rot1 = leftGyro->rotation();
            double rot2 = rightGyro->rotation();
            return (rot1+rot2)/2;
        }

        /**
         * @brief gets the current heading of the robot
         * @param dir specifies whether the robot is looking left or right
         */
        double getHeading(int dir);


        /* ODOM FUNCTIONS */
        double getPosNS();
};

#endif