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
        //int currentPos;

        int cycleLength;
        int loadLength;

        int highspeed = 100;
        int lowspeed = 40;

        bool isMoving = false;
        
        motor* driver;
    public:
        conveyor(
            motor* hookDriver,
            double cycle,
            double load
        );
        
        ~conveyor();

        void run(directionType dir);

        void stop();

        void cycleRing();
        
        void resetCycle(int speedtype);

        void loadRing(void);

        bool Moving() {return isMoving;}
};


#endif