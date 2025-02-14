/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       intake.hpp                                                */
/*    Author:       Nathan Beals                                              */
/*    Created:      Mon Dec 2 2024                                            */
/*    Description:  file for storing intake class code                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#ifndef INTAKE_HPP
#define INTAKE_HPP
using namespace vex;

class intake {
    private:
        //front intake
        motor* driver;
        //digital_out* actuator;

        //motor* ringConveyorBelt;
    public:

        /**
         * @brief
         * 
         * @param DriveMotor the intake gear box
         * @param ActuatingPiston the pneumatic system actuating the intake in and out.
         */
        intake(
            motor* DriveMotor
            //digital_out* ActuatingPiston
        );
        ~intake();

        /**
         * @brief
         */
        void extend();
        
        /**
         * @brief
         */
        void retract();

        /**
         * @brief
         */
        void setVelocity(double velocity, velocityUnits units);
        
        /**
         * @brief
         */
        void run(directionType dir);
        
        /**
         * @brief
         */
        void stop();

        /**
         * @brief
         */
        void runConveyor();
};

#endif