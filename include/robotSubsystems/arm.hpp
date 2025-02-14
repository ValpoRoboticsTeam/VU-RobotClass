/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       arm.hpp                                                   */
/*    Author:       Nathan Beals                                              */
/*    Created:      Wed Jan 22 2024                                           */
/*    Description:  file for storing intake class code                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#ifndef LADYBROWN_HPP
#define LADYBROWN_HPP
using namespace vex;

class arm {
    private:
        motor* driver;

    public:
        arm(motor* ladyBrown);
        ~arm();


        void spin(directionType dir);
        void stop();
};



#endif