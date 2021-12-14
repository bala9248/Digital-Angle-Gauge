/**************************************************************************************************
*@File test_DAG.h
*
*This file invokes all of the test functions for different peripherals
*
*@Author Balapranesh Elango
*
***************************************************************************************************/

#ifndef TEST_DAG_H_
#define TEST_DAG_H_

#include <stdio.h>
#include <stdbool.h>
#include "test_cbfifo.h"
#include "test_LED.h"
#include "test_interrupts.h"
#include "test_accelerometer.h"
#include "uart.h"


/*
 * void test_DAG()
 *
 * Tests all the peripherals by invoking all the test functions
 *
 * Parameters : None
 *
 * Returns    : None
 */
void test_DAG();

#endif /* TEST_DAG_H_ */
