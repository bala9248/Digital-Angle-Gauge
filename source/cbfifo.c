/**************************************************************************************************
*@File cbfifo.c
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

#include "cbfifo.h"


#define  MAX  256 // Max size of buffer


/*Structure contains the following items:
 A buffer of 256 (MAX) bytes
 write and read for operations
 len to indicate the number of elements in the buffer
 cap to indicate the maximum capacity
 is_full flag to check if buffer is full */
typedef struct {
     uint8_t write;
     uint8_t read;
     uint8_t len;   //length of the fifo
     uint16_t cap;   //capacity of the fifo
     bool is_full; //flag to check if full
     uint8_t buffer[MAX]; //buffer to hold the queue elements
     }cbfifo_t;

cbfifo_t cbfifo[] = { {0, 0, 0, MAX, 0}, //Initializing the cbfifos
         			  {0, 0, 0, MAX, 0}
     				       };

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
void clear_buffer(int current_instance){ /*Used only after testing of CBFIFO in DEBUG mode*/
    cbfifo[current_instance].read =  0;
    cbfifo[current_instance].write = 0;
    cbfifo[current_instance].len = 0;
    cbfifo[current_instance].is_full = 0;

    for(int i = 0; i < MAX; i++)
    	cbfifo[current_instance].buffer[i] = 0;
}

/*bool cbfifo_isempty(int current_instance)
*
* Function to check if buffer is empty
*
* Parameters: current_instance - the instance that is being passed(RxQ or TxQ)
*
* Returns: 1 if buffer is empty, and 0 if buffer is not empty
*/
bool cbfifo_isempty(int current_instance){
    return ( (cbfifo[current_instance].is_full == 0) && (cbfifo[current_instance].write == cbfifo[current_instance].read));
}

/*
* bool cbfifo_isfull(int current_instance)
*
* Function to check if buffer is full
*
* Parameters: current_instance - the instance that is being passed(RxQ or TxQ)
*
* Returns: 1 if buffer is full, and 0 if buffer is not full
*/
bool cbfifo_isfull(int current_instance){
	return (cbfifo[current_instance].is_full); //returning the is_full flag
}

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
size_t cbfifo_enqueue(int current_instance, void *buf, size_t nbytes){
	uint32_t masking_state = __get_PRIMASK();
	__disable_irq(); //to avoid race

   if(buf == NULL){ //error check
	   __set_PRIMASK(masking_state);
	   return -1;
   }
    //Checking if Buffer is full and returning 0 if its full
    if  (cbfifo[current_instance].is_full == 1 ){
    	__set_PRIMASK(masking_state);
    	return 0;
    }


    //Writing values into the buffer
    uint8_t *element = (uint8_t *) buf;
    int i;
    for (i = 0; i < nbytes ;i++){

        if (cbfifo[current_instance].is_full == 1) { //if buffer is full, return i+1
        	__set_PRIMASK(masking_state);
           return i;
        }

        cbfifo[current_instance].buffer[cbfifo[current_instance].write] = * (element + i);//writing the current element into the buffer
        cbfifo[current_instance].write = (cbfifo[current_instance].write + 1) & (MAX -1); //Moving write
        cbfifo[current_instance].len++;  //Incrementing Length of the buffer
        cbfifo[current_instance].is_full = (cbfifo[current_instance].write == cbfifo[current_instance].read); //updating is_full flag
     }
     __set_PRIMASK(masking_state);
     return(i);  //i contains the number of elements enqueued

}


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
 *   nbyte.
 *
 * To further explain the behavior: If the FIFO's current length is 24
 * bytes, and the caller requests 30 bytes, cbfifo_dequeue should
 * return the 24 bytes it has, and the new FIFO length will be 0. If
 * the FIFO is empty (current length is 0 bytes), a request to dequeue
 * any number of bytes will result in a return of 0 from
 * cbfifo_dequeue.
 */
size_t cbfifo_dequeue(int current_instance, void *buf, size_t nbyte){
	  uint32_t masking_state = __get_PRIMASK();
	  __disable_irq(); //to avoid race
	  if(buf == NULL){
		  __set_PRIMASK(masking_state);
		  return -1; //error case
	  }


	   if (cbfifo_isempty(current_instance) == 1){//checking if buffer is empty
		   __set_PRIMASK(masking_state);
		   return 0;
	   }


	   int i;
	   for (i = 0; i < nbyte; i++){
		   if (cbfifo_length(current_instance) ==0){ //Checking if buffer is empty while dequeueing byte by byte
			   __set_PRIMASK(masking_state);
			   return i;
		   }
	       *((uint8_t*)buf + i) = cbfifo[current_instance].buffer[cbfifo[current_instance].read] ;
	       cbfifo[current_instance].read = ((cbfifo[current_instance].read + 1) &
	    		   	   	   	   	   	   	   	(cbfifo[current_instance].cap - 1) );//updating read
	       cbfifo[current_instance].len--;
	       cbfifo[current_instance].is_full = 0; //Reseting the is_full flag as buffer can't be full after dequeue
	   }
	   __set_PRIMASK(masking_state);
	   return i; //i contains the number of elements dequeued
}



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
size_t cbfifo_length(int current_instance){

	if (cbfifo[current_instance].is_full == 0)  //if it's not full, we calculate it as follows
      return (cbfifo[current_instance].write - cbfifo[current_instance].read) &
    		                                   (cbfifo[current_instance].cap - 1);
    else
      return MAX; //if its full we return MAX

}

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
size_t cbfifo_capacity(){
    return MAX;
}


