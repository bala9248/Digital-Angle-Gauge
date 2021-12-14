/**************************************************************************************************
*@File test_interrupts.c
*
*This file tests both the interrupts of this application. Namely, GPIO interrupt and Touch Sensor
*Interrupt
*
*@Author Balapranesh Elango
*
*
***************************************************************************************************/

#include "test_interrupts.h"

#define   START_SCAN	 (TSI0->DATA |= TSI_DATA_SWTS_MASK)   //Software Trigger start
#define   TWO_SECONDS	 (2000)   //2 seconds in msecs
#define   TEN_SECONDS    (10000)  //10 seconds in msecs
/*
 * @int test_interrupts()
 *
 * Tests the GPIO switch interrupt and Touch Sensor interrupt
 *
 * Parameters : None
 *
 * Returns : 1 -> after successfully completing sequence
 *           0 -> failure
 */
int test_interrupts() {


	bool fail_status = false;  //To keep track of fail cases
	bool return_value = true;  //if true --> all cases passes succesfully

	reset_touch();
	restart_switch();

	printf("\n\r************Testing Touch Sensor Interrupt and GPIO Switch Interrupt************");

	printf("\n\rPress the switch");
	reset_timer();
	while( !gpio_button_pressed()){  //Wait till switch is pressed

		if( get_timer() > TEN_SECONDS){ //if switch press is not detected within 10 seconds - timeout error
			fail_status = true;
			break;
		}
	}

	if(fail_status == false)  //success case
		printf("\n\rSwitch was pressed - GPIO Interrupt WORKING\n\r");
	else{  //fail case
		printf("\n\rSwitch press not detected!!!!!!!!!!\n\r");
		return_value = false;
	}

	fail_status = false;
	printf("\n\rPress the touch sensor in the left side");
	reset_timer();
	START_SCAN;             //Enable software trigger
	while(!Touch_Scan_LH()){   //Wait till Touch sensor is pressed
		START_SCAN;
		if(get_timer() > TEN_SECONDS){    //if touch is not detected within 10 seconds - timeout error
			fail_status = true;
			break;
		}
	}
	if(fail_status == false)   //success case
		printf("\n\rPress detected!!!\n\r");
	else{                     //fai case
		printf("\n\rTouch not detected!!!!!!!!!!\n\r");
		return_value = false;
	}

	delay(TWO_SECONDS);
	reset_touch();
	fail_status = false;
	printf("\n\rPress the touch sensor in the middle");
	reset_timer();
	START_SCAN;             //Enable software trigger
	while(!Touch_Scan_LH()){   //Wait till Touch sensor is pressed
		START_SCAN;
		if(get_timer() > TEN_SECONDS){ //if touch is not detected within 10 seconds - timeout error
			fail_status = true;
			break;
		}
	}
	if(fail_status == false)     //success case
		printf("\n\rPress detected!!!\n\r");

	else{  //fail case
		printf("\n\rTouch not detected!!!!!!!!!!\n\r");
		return_value = false;
	}


	delay(TWO_SECONDS);
	reset_touch();
	fail_status = false;
	printf("\n\rPress the touch sensor in the right");
	reset_timer();
	START_SCAN;             //Enable software trigger
	while(!Touch_Scan_LH()){   //Wait till Touch sensor is pressed
		START_SCAN;
		if(get_timer() > TEN_SECONDS){   //if touch is not detected within 10 seconds - timeout error
			fail_status = true;
			break;
		}
	}
	if(fail_status == false)   //sucesss
		printf("\n\rPress detected!!!\n\r");
	else{              //fail
		printf("\n\rTouch not detected!!!!!!!!!!\n\r");
		return_value = false;
	}

	if(return_value){  // all cases passed
		printf("\n\rTSI Interrupt WORKING\n\r");
		printf("\n\r**************All Interrupts working successfully!! ****************");
	}

	else            //Failures exist
		printf("\n\rInterrupt not working as expected!!!");

	return return_value ;
}
