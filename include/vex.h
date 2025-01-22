/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"

#include "drivetrainSubsystem/sensorUnit.hpp"

#include "drivetrainSubsystem/wheelSide.hpp"
#include "drivetrainSubsystem/twoWheelSide.hpp"
#include "drivetrainSubsystem/threeWheelSide.hpp"
#include "drivetrainSubsystem/fourWheelSide.hpp"
#include "drivetrainSubsystem/drivetrain.hpp"

#include "robotSubsystems/clamp.hpp"
#include "robotSubsystems/intake.hpp"

#include "robotSubsystems/robot.hpp"


#include "robot-config.h"
#include "Autons.h"


#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)