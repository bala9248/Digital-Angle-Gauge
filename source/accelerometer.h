/**************************************************************************************************
*@File accelerometer.h
*
*This file Initializes the switch for GPIO interrupt and has the GPIO interrupt handler and an
*associated helper function to check if a swithch was pressed
*
*@Author Balapranesh Elango
*
*References : Dean's Github
*
***************************************************************************************************/
#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include <stdint.h>
#include <MKL25Z4.H>
#include "i2c.h"
#include <math.h>

/*
 * @int init_mma()
 *
 * Initializes the accelerometer sensor after I2C has been
 * initialized
 *
 * Parameters : None
 *
 * Returns : 1 after writing to the Control Register 1 of the Sensor
 */
int init_mma(void);


/*
 * int read_roll()
 *
 * Function to read the roll after reading y_val and z_val
 *
 * Parameters : None
 *
 * Returns : roll -> the calculated value of the roll
 */
int read_roll();



#endif /* ACCELEROMETER_H_ */
