/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       robot.hpp                                                 */
/*    Author:       Nathan Beals                                              */
/*    Created:      Sun March 17 2024                                         */
/*    Description:  file for storing robot class declerations                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef ROBOT_HPP
#define ROBOT_HPP
#include "structures.hpp"
using namespace vex;


class Robot {
    private:
        coordinate coords;
        
        driveTrain* driveT;
        clamp* mogoClamp;
        intake* frontIntake;
        conveyor* hookConveyor;
        arm* ladyBrown;
        
    public:

        /**
         * @brief creates a robot object to monitor, manage, and control the robots' systems
         * 
         * @param dt the drive train controller
         * @param MC the mogo clamp controller
         * @param I the intake system controller 
         */
        Robot(
            driveTrain* dt,
            clamp* MC,
            intake* I,
            conveyor* C,
            arm* LB
        );

        ~Robot();

        /* Drive Controlls */

        /**
         * @brief Switch between Arcade drive and tank drive
         */
        void switchControlMode(){
            driveT->switchControlMode();
        }
        
        /**
         * @brief
         */
        int drive(double leftNS, double leftEW, double rightNS, double rightEW);

        /* Subsystem Controlls */

        /* MOGO Clamp */

        /**
         * @brief
         */
        void toggleMogoClamp();

        /* Intake Commands */

        /**
         * @brief
         */
        void runIntake();

        /**
         * @brief
         */
        void runReversedIntake();

        /**
         * @brief
         */
        void stopIntake();

        /* ladyBrown */

        /**
         * @brief
         */
        void ladybrownForward();

        /**
         * @brief
         */
        void ladybrownBackward();

        /**
         * @brief
         */
        void ladybrownStop();

        /* Expansion */

        void autonomous();
};

#endif