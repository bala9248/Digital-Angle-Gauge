/**************************************************************************************************
*@File user_io.c
*
*This file redirects the stdio through uart using syswrite and sysread
*This file also contains a non-blocking getchar() function that is used by the command processor
*
*@Author Balapranesh Elango
*
*
***************************************************************************************************/
#include "user_io.h"


/*
 * char non_blocking_getchar()
 *
 * A non- blocking getchar() function that does not wait for a byte to arrive
 *
 * Parameters:
 *      	None
 * Returns:
 * 		 	'\0' if no byte was dequeued
 * 		 	byte if a byte was dequeued
**/
char non_blocking_getchar(){
	uint8_t byte;

	if(cbfifo_dequeue(RxQ, &byte, 1) != 1) //Dequeue and check for byte
		return '\0';

	return(byte); //Return receive(dequeued) byte
}


/*
 * int __sys_write(int handle, char *buf, int size)
 *
 * To redirect stdio through uart
 *
 * parameters:
 *          buf  -> contains the bytes to be enqueued
 *          size -> Number of bytes
 *
 * returns:
 *          0  on success
 *          -1 on failure
 */
int __sys_write(int handle, char *buf, int size){

	while( ( cbfifo_capacity() - cbfifo_length(TxQ) ) < ( size ) )  //Wait for enough space to open up
		;

	if( cbfifo_enqueue(TxQ, buf, size) != size)   //enqueue and check for error
		return -1;


	if (!(UART0->C2 & UART0_C2_TIE_MASK)) {  // start transmitter if it isn't already running
		cbfifo_dequeue(TxQ, buf, 1);
		UART0->D = *(buf);
		UART0->C2 |= UART0_C2_TIE(1);
	}
	return 0;
}

/*
 * int __sys_readc(void)
 *
 * To redirect stdio through uart
 *
 * parameters:
 *            None
 *
 * Returns:
 *       Byte on success
 *       -1 on failure
 */
int __sys_readc(void){

	uint8_t byte;
	while (cbfifo_length(RxQ) == 0)
		; // wait for character to arrive

	if(cbfifo_dequeue(RxQ, &byte, 1) != 1) //Dequeue and check for error
		return -1;
	return(byte); //Return receive(dequeued) byte
}
