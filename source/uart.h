/**************************************************************************************************
*@File uart.h
*
*This file Initializes UART0 with the given requirements and also has the IRQ handler for UART0
*
*@Author Balapranesh Elango
*
*References : Howdy's Lecture and Dean
*
***************************************************************************************************/

#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <MKL25Z4.H>
#include "cbfifo.h"
#include "user_io.h"

/*
 * void Init_UART0()
 *
 * Function to Intialize UART0 with 8bits, 2 Stop bits , and no parity
 *
 * Parameters:
 *      	None
 * Returns:
 * 		 	None
**/
void Init_UART0();






#endif //UART_H
