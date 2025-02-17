/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       Autons.h                                                  */
/*    Author:       Nathan Beals                                              */
/*    Created:      Sun March 17 2024                                         */
/*    Description:  file for storing autonomous programs                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef AUTONS_H
#define AUTONS_H

extern double tileLength; //inches

/**
 * @brief void containing autonomous test code
*/
void test();

/**
 * @brief void containing autonomous match code for the 24" robot
*/
void match24();

/**
 * @brief void containing autonomous match code for the 15" robot
*/
void match15();

/**
 * @brief void containing autonomous skills code for the 24" robot
*/
void skills24();

/**
 * @brief void containing autonomous skills code for the 15" robot
*/
void skills15();

#endif