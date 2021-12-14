/**************************************************************************************************
*@File user_io.c
*
*This file redirects the stdio to uart using syswrite and sysread
*This file also contains a non-blocking getchar() function that is used by the command processor
*
*@Author Balapranesh Elango
*
*
***************************************************************************************************/
#ifndef USER_IO_H_
#define USER_IO_H_

#include "cbfifo.h"

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
char non_blocking_getchar();


#endif /* USER_IO_H_ */
