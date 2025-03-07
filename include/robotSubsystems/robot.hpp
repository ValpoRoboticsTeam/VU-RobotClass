
#ifndef ROBOT_HPP
#define ROBOT_HPP
#include "structures.hpp"
using namespace vex;


class Robot {
    private:
        coordinate coords;

        clamp* mogoClamp;

        bool hooks_ManualOverride = false;
    public:
        driveTrain* driveT;
        intake* frontIntake;
        conveyor* hookConveyor; // for less annoying control over hook mech

        /**
         * @brief creates a robot object to monitor, manage, and control the robots' systems
         * 
         * @param dt the drive train controller
         */
        Robot(
            driveTrain* dt,
            clamp* MC,
            intake* frontIntake,
            conveyor* C
        );
        
        Robot();

        ~Robot();

        void setDriveTrain(driveTrain* DT) {
            driveT = DT;
        }

        driveTrain* getDrive() {return driveT;}

    
        /* Drive Controlls */

        /**
         * @brief Switch between Arcade drive and tank drive
         */
        void switchControlMode(){
            driveT->switchControlMode();
        }
        
        void toggle_HookManualOverride(){if(hooks_ManualOverride){hooks_ManualOverride=false;}else{hooks_ManualOverride=true;}}

        /**
         * @brief
         */
        int drive(double leftNS, double leftEW, double rightNS, double rightEW);


        bool hasMogo(){
            return mogoClamp->hasMogo();
        }

        /**
         * @brief
         */
        void toggleMogoClamp();

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


        void runHooks();

        /**
         * @brief
         */
        void runReversedHooks();

        void stopHooks();

};

#endif