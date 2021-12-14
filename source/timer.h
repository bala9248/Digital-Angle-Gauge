/**************************************************************************************************
*@File timer.h
*
*This file Initializes the systick timer to interrupt every 1msec
*This file also contains functions to generate a delay, find the time elapsed, etc.
*
*@Author Balapranesh Elango
*
*References : Howdy's Lecture
*
***************************************************************************************************/
#ifndef TIMER_H_
#define TIMER_H_

#include "MKL25Z4.h"
#include <stdio.h>

typedef uint32_t ticktime_t;  //uint32_t typedef

/*
 * @void init_systick()
 *
 * Initializes systick timer and interrupt to interrupt
 * every 1msec
 *
 * Returns : None
 *
 * Paramaters : None
 */
void init_systick();


/*
 * @void reset_timer()
 *
 * resets get_timer to 0 but does not affect now()
 *
 * Returns : None
 *
 * Parameters : None
 */
void reset_timer();


/*
 * @void delay(uint32_t delay_msec)
 *
 * Generated a delay of delay_msec
 *
 * Returns : None
 *
 * Parameters : delay_msec: used to create delay
 */
void delay(uint32_t delay_msec);


/*
 * @ticktime_t get_timer()
 *
 * calculates the time since the last startup
 *
 * Returns : returns the time since the last reset
 *
 * Parameters : none
 */
ticktime_t get_timer();


/*
 * @ticktime_t now()
 *
 * Calculates the time elapsed since the program startup
 *
 * Returns : returns the time since the program startup
 *
 * Parameters : none
 *
 */
ticktime_t now();

#endif /*TIMER_H_*/
