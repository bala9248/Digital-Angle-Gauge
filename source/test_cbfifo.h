/*******************************************************************************
*@File test_cbfifo.h
*
*This file contains various test cases for cbfifo.c that tests both instances
*of the CBFIFO
*
*References: Howdy's Test Suite
*
*@Author Balapranesh Elango
*******************************************************************************/

#ifndef _TEST_CBFIFO_H_
#define _TEST_CBFIFO_H_


#include"cbfifo.h"
#include<stdio.h>
#include<assert.h>
#include<string.h>

/*
 * int test_cbfifo(int RxQ_t, int TxQ_t)
 *
 * Function to test both instances of the CBFIFO
 *
 * Parameters:
 * 		RxQ_t -> RX Buffer Instance
 * 		TxQ_t -> TX Buffer Instance
 * Returns:
 *  		1 -> after all asserts pass
 */
int test_cbfifo(int RxQ_t, int TxQ_t);


#endif // _TEST_CBFIFO_H_

