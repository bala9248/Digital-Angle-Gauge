/**************************************************************************************************
*@File Command_handler.h
*This file handles the supported commands entered by the user by doing the following things:
*i)  Accumulates a line
*ii) Performs lexing on the accumulated line and seperates the string into argv[]
*iii)Calls the appropriate handler to perform the command
*
*@Author Balapranesh Elango
*
*Citations : Howdy Pierce's Lecture
*
***************************************************************************************************/

#ifndef _COMMAND_HANDLER_H_
#define _COMMAND_HANDLER_H_

#include<stdio.h>
#include<string.h>
#include "uart.h"
#include "switch.h"
#include "accelerometer.h"
#include "LED.h"
#include "touch_sensor.h"
#include "timer.h"


/*
 * Receives the User input from the Serial terminal and accumulates into
 * a line buffer and sends it for lexical processing
 *
 * Parameters:
 *   none
 *
 * Returns:
 *   None
 */
void command_line_interface();








#endif //_COMMAND_HANDLER_H_
