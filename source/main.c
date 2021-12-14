/**************************************************************************************************
*@File main.c
*
*Application Entry point
*Initializes all the peripherals
*Performs Automatic and Semi-Automatic tests
*Invokes the UART Command Processor for Digital Angle Gauge Application
*
*@Author Balapranesh Elango
*
*
*         External Hardware Interface
*
*                  KL25Z
*            +-----------------+
*            |                 |
*            |                 |
*	         |                 |   +--------+
*	         |             PTD3|-->|        |
*	         |             GND |-->| Switch |
*	         |                 |   |        |
*	         |                 |   +--------+
*	         |                 |
*	         |                 |
*	         |                 |
*	         |                 |
*	         |                 |
*	         +-----------------+
*
*
***************************************************************************************************/

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#include "i2c.h"
#include "accelerometer.h"
#include "switch.h"
#include "sysclock.h"
#include "uart.h"
#include "LED.h"
#include "Command_handler.h"
#include "touch_sensor.h"

#include "test_DAG.h"

/*
 * @brief   Application entry point.
 */

int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif


    /* Initializaing Peripherals */
    init_i2c();      //Initialize I2C
    init_mma();      //Initialize Accelerometer
    switch_init();   //Initialize external switch
    led_init();      //Initialize LEDs for PWM
    Touch_Init();    //Initialize touch sensor
    sysclock_init(); //Initializing system clock
	Init_UART0();    //Intializing UART0 for processing commands
	init_systick();  //Initialize systick to interrupt every 1 millisecond


   /* Testing in DEBUG mode only */
#ifdef DEBUG
	test_DAG();
#endif

    /* UART Command Processor */
	command_line_interface();

    return 0 ;
}
