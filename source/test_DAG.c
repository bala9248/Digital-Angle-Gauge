/**************************************************************************************************
*@File test_DAG.c
*
*This file invokes all of the test functions for different peripherals
*
*@Author Balapranesh Elango
*
***************************************************************************************************/
#include "test_DAG.h"


/*
 * void test_DAG()
 *
 * Tests all the peripherals by invoking all the test functions
 *
 * Parameters : None
 *
 * Returns    : None
 */
void test_DAG(){
	bool success_flag = true;  //To keep track of test cases success/ failure

	success_flag &= test_cbfifo(RxQ, TxQ); //Automatic Test
	success_flag &= test_LED();            //Semi - Automatic Test
	success_flag &= test_interrupts();     //Semi - Automatic Test
	success_flag &= test_acclerometer();   //Semi - Automatic Test


	if(success_flag){  //If flag is still true, all the cases have passed
		printf("\n\r\n\r*******************************************************************************");
		printf("\n\r\n\r***********************ALL TESTS COMPLETED SUCCESSFULLY!!!*********************");
    	printf("\n\r\n\r*******************************************************************************");
	}
	else{
		printf("\n\r\n\r***********FAILED TESTS EXISTS - Check Terminal Log************");
		printf("\n\rExiting program!!!");
		exit(0);
	}

}
