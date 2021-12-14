/*******************************************************************************
*@File test_LED.h
*
*Semi-Automatic testing of the on-board RBG LED and PWM functionality using
*Systick Timer interrupt
*
*@Author Balapranesh Elango
********************************************************************************/
#ifndef TEST_LED_H_
#define TEST_LED_H_

#include "timer.h"
#include "LED.h"
#include "uart.h"


/*
 * @int test_LED()
 *
 * Tests the on-board LEDs and PWM functionality of LEDs
 *
 * Parameters : None
 *
 * Returns : 1 -> after completion of sequence
 */
int test_LED();

#endif /* TEST_LED_H_ */
