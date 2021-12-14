/**************************************************************************************************
*@File LED.h
*
*This file Initializes the RGB leds for PWM and also controls the LEDs using PWM
*
*@Author Balapranesh Elango
*
*References : Dean Chapter 7
*
***************************************************************************************************/

#ifndef LED_H_
#define LED_H_

#include "MKL25Z4.h"


/*
 * @void led_int()
 * Initializes the LED for PWM
 * Returns : None
 * Paramaters : None
 */
void led_init();

/*
 * @void led_con(int red, int green, int blue)
 * Used to Control LED with PWM
 * Returns : None
 * Paramaters : red, green, blue -> used to control the PWM for "Web Colors"
 */
void led_con(int red, int green, int blue);

#endif /* LED_H_ */
