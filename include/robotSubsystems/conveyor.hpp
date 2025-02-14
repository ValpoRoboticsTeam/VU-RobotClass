/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       conveyor.hpp                                              */
/*    Author:       Nathan Beals                                              */
/*    Created:      Wed Jan 22 2024                                           */
/*    Description:  file for storing intake class code                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#ifndef CONVEYOR_HPP
#define CONVEYOR_HPP
using namespace vex;

class conveyor{
    private:
        const int restPos = 0;
        const int loadedPos = 0;
        int currentPos;
        
        motor* driver;
    public:
        conveyor(
            motor* hookDriver
        );
        ~conveyor();

        void run(directionType dir);

        void stop();

        void loadRing();
};


#endif