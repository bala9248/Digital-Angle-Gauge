/**************************************************************************************************
*@File switch.h
*
*This file Initializes the switch for GPIO interrupt and has the GPIO interrupt handler and an
*associated helper function to check if a swithch was pressed
*
*@Author Balapranesh Elango
*
*References : Howdy's Lecture
*
***************************************************************************************************/


#ifndef SWITCH_H_
#define SWITCH_H_

#include "MKL25Z4.h"

/*
 * @void switch_init()
 *
 * Initializes switch for GPIO interrupt
 *
 * Paramaters : None
 *
 * Returns : None
 */
void switch_init();


/*
 * @int gpio_button_pressed()
 *
 * Function to check if switch is pressed
 *
 * Paramaters : None
 *
 * Returns : 1 if switch was pressed andd 0 if switch was not pressedd
 */
int gpio_button_pressed(void);


/*
 * void restart_switch()
 *
 * Function to reset global variable that keeps track of the switch press
 *
 * Paramaters : None
 *
 * Returns : 1 if switch was pressed andd 0 if switch was not pressedd
 */
void restart_switch();

#endif /* SWITCH_H_ */
