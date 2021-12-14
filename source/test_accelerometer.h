/**************************************************************************************************
*@File test_accelerometer.h
*
*This file tests the accelerometer which (in-turn tests if I2C is working) by asking
*the user to tilt the DAG to various angles and checking if it has been tilted
*
*@Author Balapranesh Elango
*
*
***************************************************************************************************/
#ifndef TEST_ACCELEROMETER_H_
#define TEST_ACCELEROMETER_H_

#include <stdio.h>
#include <stdbool.h>

#include "uart.h"
#include "accelerometer.h"
#include "timer.h"


/*
 * int test_acclerometer()
 *
 * Tests the accelerometer sensor by asking the user to tilt the DAG to a number of angles
 * Verification of the working of the Accelerometer sensor also ensures that I2C is working
 *
 * Paramaters : None
 *
 * Returns : 1 -> after successfully completing sequence
 *           0 -> Failure
 */
int test_acclerometer();


#endif /* TEST_ACCELEROMETER_H_ */
