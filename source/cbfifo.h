/**************************************************************************************************
*@File cbfifo.h
*This file contains the following functions:
*
*   i) cbfifo_isempty() to check if the fifo is empty
*     using the is_full flag
*
*   ii) cbfifo_enqueue() is used to enqueue to the fifo
*
*   iii)cbfifo_dequeue() is used to dequeue from the fifo
*
*   iV)cbfifo_length() returns the current length of the fifo
*
*   V)cbfifo_capacity() always returns 128
*
*@Author Balapranesh Elango
*
*@Version: 2.0
*
*Referene : "https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/"
*
***************************************************************************************************/

#ifndef _CBFIFO_H_
#define _CBFIFO_H_

#include <stdlib.h>
#include<stdint.h>
#include "MKL25Z4.h"
#include<stdbool.h>

/*
 * Enum contains the number of CBFIFO instances
 * Used along with array of structures to access a specific instance
 */
typedef enum{
	RxQ,
	TxQ
}Buf;


/*
* void clear_buffer(int current_instance)
*
* Function to reset the buffer after running through test_cbfifo.c
*
* Parameters: current_instance - the instance that is being passed(RxQ or TxQ)
*
* Returns:
* 	none
*/
void clear_buffer(int current_instance);



/*bool cbfifo_isempty(int current_instance)
*
* Function to check if buffer is empty
*
* Parameters: current_instance - the instance that is being passed(RxQ or TxQ)
*
* Returns: 1 if buffer is empty, and 0 if buffer is not empty
*/
bool cbfifo_isempty(int current_instance);



/*
* bool cbfifo_isfull(int current_instance)
*
* Function to check if buffer is full
*
* Parameters: current_instance - the instance that is being passed(RxQ or TxQ)
*
* Returns: 1 if buffer is full, and 0 if buffer is not full
*/
bool cbfifo_isfull(int current_instance);


/*
*size_t cbfifo_enqueue(int current_instance, void *buf, size_t nbytes)
*
* Enqueues data onto the FIFO, up to the limit of the available FIFO
* capacity.
*
* Parameters:
*   current_instance - the instance that is being passed(RxQ or TxQ)
*   buf      Pointer to the data
*   nbyte    Max number of bytes to enqueue
*
* Returns:
*   The number of bytes actually enqueued, which could be 0. In case
*   of an error, returns -1.
*/
size_t cbfifo_enqueue(int current_instance, void *buf, size_t nbytes);


/*
 * size_t cbfifo_dequeue(int current_instance, void *buf, size_t nbyte)
 *
 * Attempts to remove ("dequeue") up to nbyte bytes of data from the
 * FIFO. Removed data will be copied into the buffer pointed to by buf.
 *
 * Parameters:
 *	 current_instance - the instance that is being passed(RxQ or TxQ)
 *   buf      Destination for the dequeued data
 *   nbyte    Bytes of data requested
 *
 * Returns:
 *   The number of bytes actually copied, which will be between 0 and
 * nbyte.
 *
 * To further explain the behavior: If the FIFO's current length is 24
 * bytes, and the caller requests 30 bytes, cbfifo_dequeue should
 * return the 24 bytes it has, and the new FIFO length will be 0. If
 * the FIFO is empty (current length is 0 bytes), a request to dequeue
 * any number of bytes will result in a return of 0 from
 * cbfifo_dequeue.
 */
size_t cbfifo_dequeue(int current_instance, void *buf, size_t nbyte);



/*
 * size_t cbfifo_length(int current_instance)
 *
 * Returns the number of bytes currently on the FIFO.
 *
 * Parameters:
 *   current_instance - the instance that is being passed(RxQ or TxQ)
 *
 * Returns:
 *   Number of bytes currently available to be dequeued from the FIFO
 */
size_t cbfifo_length(int current_instance);



/*size_t cbfifo_capacity()
 *
 * Returns the FIFO's capacity
 *
 * Parameters:
 *   none
 *
 * Returns:
 *   The capacity, in bytes, for the FIFO
 */
size_t cbfifo_capacity();


#endif // _CBFIFO_H_
