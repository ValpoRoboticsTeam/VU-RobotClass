/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       clamp.cpp                                                 */
/*    Author:       Nathan Beals                                              */
/*    Created:      Mon Dec 2 2024                                            */
/*    Description:  file for storing MOGO clamp class code                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
using namespace vex;

clamp::clamp(digital_out* MC){
    MogoClamp = MC;
    clampState = false;
    MogoClamp->set(false);
}

clamp::~clamp(){}


// Clamp functionality

void clamp::open() {
    MogoClamp->set(true);
    clampState = true;
}

void clamp::close() {
    MogoClamp->set(false);
    clampState = false;
}

void clamp::toggle() {
    if (clampState) {
        close();
    } else {
        open();
    }
}
