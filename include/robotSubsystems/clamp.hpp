/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       clamp.hpp                                                 */
/*    Author:       Nathan Beals                                              */
/*    Created:      Mon Dec 2 2024                                            */
/*    Description:  file for storing MOGO clamp class declerations            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#ifndef CLAMP_HPP
#define CLAMP_HPP
using namespace vex;

class clamp {
    private:
        bool clampState = true;
        digital_out* MogoClamp;

    public:
    
        /**
         * @brief
         * @param MC the mogo clamp being controlled
         */
        clamp(digital_out* MC);
        ~clamp();

        // Clamp functionality
        
        /**
         * @brief
         */
        void open();
        
        /**
         * @brief
         */
        void close();
        
        /**
         * @brief
         */
        void toggle();
};

#endif