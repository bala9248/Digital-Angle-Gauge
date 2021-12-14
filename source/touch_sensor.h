/**************************************************************************************************
*@File touch_sensor.h
*
*This file Initializes the touch sensor to be used with interrupts and also houses the TSI Interrupt handler
*and a function to check if the touch sensor was pressed
*
*@Author Balapranesh Elango
*
*References :  "https://github.com/alexander-g-dean/ESF/blob/master/NXP/Misc/Touch%20Sense/TSI/src/main.c"
*
***************************************************************************************************/
#ifndef TOUCH_SENSOR_H_
#define TOUCH_SENSOR_H_

#include <stdbool.h>
#include "MKL25Z4.h"


/*
 * @void Touch_Init()
 *
 * Initializes the Touch sensor to be used with an Interrupt
 *
 * Parameters : None
 *
 * Returns : None
 */
void Touch_Init();

/*
 * @int Touch_Scan_LH()
 *
 * Function to check if touch sensor was pressed
 *
 * Parameters : None
 *
 * Returns : 1  -> if touch sensor was pressed
 * 	         0  -> if touch sensor was not pressed
 */
int Touch_Scan_LH(void);



/*
 * void reset_touch()
 *
 * Function to reset previous touch detections by resetting the global variable
 *
 * Parameters : None
 *
 * Returns : None

 */
void reset_touch();

#endif /* TOUCH_SENSOR_H_ */
