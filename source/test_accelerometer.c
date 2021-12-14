/**************************************************************************************************
*@File test_accelerometer.c
*
*This file tests the accelerometer which (in-turn tests if I2C is working) by asking
*the user to tilt the DAG to various angles and checking if it has been tilted
*
*@Author Balapranesh Elango
*
*
***************************************************************************************************/

#include "test_accelerometer.h"


#define   abs(x)     (x) < 0 ? (-x) : (x)   //To find the absolute value

#define   DEG_0        (00)                   //0 degrees
#define   DEG_30       (30)                   //30 degrees
#define   DEG_60       (60)                   //60 degrees
#define   DEG_90	   (90)                   //90 Degrees
#define   DEG_120	   (120)                  //120 degrees
#define   DEG_150      (150)                  //150 degrees
#define   DEG_180      (179)                  //180 degrees

#define   TEN_SECONDS  (10000)                //Ten seconds in msecs
/*
 * int test_acclerometer()
 *
 * Tests the accelerometer sensor by asking the user to tilt the DAG to a number of angles
 * Verification of the working of the Accelerometer sensor also ensures that I2C is working
 *
 * Paramaters : None
 *
 * Returns : 1 -> after successfully completing sequence
 *           0 -> Failure
 */
int test_acclerometer(){

	bool fail_status = false;  //To keep track of failed test cases
	bool return_val  = true;   //To keep track of return value (1 or 0)

	printf("\n\r***************Testing I2C and Accelerometer*****************");
	int roll;

	printf("\n\rPlace the DAG at 0 degrees relative to the surface of the table");
	reset_timer();
	while(1){
		if( get_timer() > TEN_SECONDS){   //if angle is not attained within 10 seconds - timeout error
			fail_status = true;
			break;
		}
		 roll = abs(read_roll());
		 if(roll == DEG_0)            //If current roll is 0 break out of while loop
			 break;
	}

	if(fail_status == false)   //success
		printf("\n\rDAG placed at 0 degrees successfully!\n\r");

	else{  //fail case
		printf("\n\rTimeout - DAG not placed at 0 degrees\n\r");
		return_val = false;
	}

	printf("\n\rPlace the DAG at 30 degrees relative to the surface of the table");
	reset_timer();
	fail_status = false;
	while(1){
		if( get_timer() > TEN_SECONDS){  //if angle is not attained within 10 seconds - timeout error
			fail_status = true;
			break;
		}
		 roll = abs(read_roll());
		 if(roll == DEG_30)            //If current roll is 30 break out of while loop
			 break;
	}

	if(fail_status == false)   //success case
		printf("\n\rDAG placed at 30 degrees successfully!\n\r");

	else{ //fail case
		printf("\n\rTimeout - DAG not placed at 30 degrees\n\r");
		return_val = false;
	}


	printf("\n\rPlace the DAG at 60 degrees relative to the surface of the table");
	reset_timer();
	fail_status = false;
	while(1){
		if( get_timer() > TEN_SECONDS){ //if angle is not attained within 10 seconds - timeout error
			fail_status = true;
			break;
		}
		 roll = abs(read_roll());
		 if(roll == DEG_60)            //If current roll is 60 break out of while loop
			 break;
	}

	if(fail_status == false)  //success case
		printf("\n\rDAG placed at 60 degrees successfully!\n\r");

	else{                //fail case
		printf("\n\rTimeout - DAG not placed at 60 degrees\n\r");
		return_val = false;
	}



	printf("\n\rPlace the DAG at 90 degrees relative to the surface of the table");
	reset_timer();
	fail_status = false;
	while(1){
		if( get_timer() > TEN_SECONDS){ //if angle is not attained within 10 seconds - timeout error
			fail_status = true;
			break;
		}
		 roll = abs(read_roll());
		 if(roll == DEG_90)            //If current roll is 90 break out of while loop
			 break;
	}

	if(fail_status == false)   //success case
		printf("\n\rDAG placed at 90 degrees successfully!\n\r");

	else{             //fail case
		printf("\n\rTimeout - DAG not placed at 90 degrees\n\r");
		return_val = false;
	}



	printf("\n\rPlace the DAG at 120 degrees relative to the surface of the table");
	reset_timer();
	fail_status = false;
	while(1){
		if( get_timer() > TEN_SECONDS){  //if angle is not attained within 10 seconds - timeout error
			fail_status = true;
			break;
		}
		 roll = abs(read_roll());
		 if(roll == DEG_120)            //If current roll is 120 break out of while loop
			 break;
	}

	if(fail_status == false)  //success case
		printf("\n\rDAG placed at 120 degrees successfully!\n\r");

	else{                     //fail cases
		printf("\n\rTimeout - DAG not placed at 120 degrees\n\r");
		return_val = false;
	}



	printf("\n\rPlace the DAG at 150 degrees relative to the surface of the table");
	reset_timer();
	fail_status = false;
	while(1){
		if( get_timer() > TEN_SECONDS){ //if angle is not attained within 10 seconds - timeout error
			fail_status = true;
			break;
		}
		 roll = abs(read_roll());
		 if(roll == DEG_150)            //If current roll is 150 break out of while loop
			 break;
	}

	if(fail_status == false)      //success case
		printf("\n\rDAG placed at 150 degrees successfully!\n\r");

	else{                         //fail case
		printf("\n\rTimeout - DAG not placed at 150 degrees\n\r");
		return_val = false;
	}


	printf("\n\rPlace the DAG at 180 degrees relative to the surface of the table");
	reset_timer();
	fail_status = false;
	while(1){
		if( get_timer() > TEN_SECONDS){  //if angle is not attained within 10 seconds - timeout error
			fail_status = true;
			break;
		}
		 roll = abs(read_roll());
		 if(roll == DEG_180)            //If current roll is 180 break out of while loop
			 break;
	}

	if(fail_status == false) //success case
		printf("\n\rDAG placed at 180 degrees successfully!\n\r");

	else{  //fail case
		printf("\n\rTimeout - DAG not placed at 180 degrees\n\r");
		return_val = false;
	}



	printf("\n\rPlace the DAG at 0 degrees relative to the surface of the table");
	reset_timer();
	fail_status = false;
	while(1){
		if( get_timer() > TEN_SECONDS){ //if angle is not attained within 10 seconds - timeout error
			fail_status = true;
			break;
		}
		 roll = abs(read_roll());
		 if(roll == DEG_0)            //If current roll is 0 break out of while loop
			 break;
	}

	if(fail_status == false) //success case
		printf("\n\rDAG placed at 0 degrees successfully!\n\r");

	else{  //fail case
		printf("\n\rTimeout - DAG not placed at 0 degrees\n\r");
		return_val = false;
	}


	if(return_val == true)  //all cases passed
		printf("\n\r\n\r***************Accelerometer and I2C working as expected!!****************\n\r");
	else
		printf("\n\r\n\r***************Accelerometer and I2C NOT working as expected!!!!!*********\n\r");

	return return_val;
}
