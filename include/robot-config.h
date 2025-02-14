/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       robot-config.h                                            */
/*    Author:       Nathan Beals                                              */
/*    Created:      Sun Feb. 18 2024                                          */
/*    Description:  declerations of robot motors and devices                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/
using namespace vex;
using signature = vision::signature;

extern brain Brain;
extern controller Controller;

extern driveTrain drive;
extern sensorUnit driveSensors;
// VEXcode devices

//extern inertial gyroscope;
extern digital_in linetracker;

extern aivision aivis;

extern signature MOGO;
extern vision vis;

extern Robot robot;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
