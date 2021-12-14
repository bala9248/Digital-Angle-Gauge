/**************************************************************************************************
*@File test_interrupts.h
*
*This file tests both the interrupts of this application. Namely, GPIO interrupt and Touch Sensor
*Interrupt
*
*@Author Balapranesh Elango
*
*
***************************************************************************************************/

#ifndef TEST_INTERRUPTS_H_
#define TEST_INTERRUPTS_H_

#include <stdio.h>
#include "switch.h"
#include "touch_sensor.h"
#include "uart.h"
#include "timer.h"
#include <stdbool.h>

/*
 * @int test_interrupts()
 *
 * Tests the GPIO switch interrupt and Touch Sensor interrupt
 *
 * Parameters : None
 *
 * Returns : 1 -> after successfully completing sequence
 *           0 -> failure
 */
int test_interrupts();


#endif /* TEST_INTERRUPTS_H_ */
