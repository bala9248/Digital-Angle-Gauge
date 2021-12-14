/*******************************************************************************
*@File test_LED.c
*
*Semi-Automatic testing of the on-board RBG LED and PWM functionality using
*Systick Timer interrupt
*
*@Author Balapranesh Elango
********************************************************************************/
#include "test_LED.h"


#define    RED	        (0xFF) //Maximum Intensity for PWM
#define    GREEN   		(0xFF) //Maximum Intensity for PWM
#define    BLUE         (0xFF) //Maximum Intensity for PWM
#define    LED_OFF      (00)   //Minimum Intensity for PWM - LED off

#define    ONE_SECOND   (1000) //One second in milliseconds
#define    TWO_SECONDS	(2000) //Two seconds in milliseconds
#define    FACTOR       (5)    //Color is modified every 5 msecs


/*
 * @int test_LED()
 *
 * Tests the on-board LEDs and PWM functionality of LEDs
 *
 * Parameters : None
 *
 * Returns : 1 -> after completion of sequence
 */
int test_LED(){


	printf("\n\r************TESTING LED************\n\r");
	printf("\n\rWhite LED ON for one second");
	led_con(RED, GREEN, BLUE);        //White LED is lit
	delay(ONE_SECOND);                //One second delay

	printf("\n\rRED LED ON for one second");
	led_con(RED, LED_OFF, LED_OFF);   //RED LED is lit for one second
	delay(ONE_SECOND);

	printf("\n\rGreen LED ON for one second");
	led_con(LED_OFF, GREEN, LED_OFF); //GREEN LED is lit for one second
	delay(ONE_SECOND);

	printf("\n\rBlue LED ON for one second");
	led_con(LED_OFF, LED_OFF, BLUE);  //BLUE LED is lit for one second
	delay(ONE_SECOND);

	printf("\n\r*********TESTING PWM FUNCTIONALITY************");
	printf("\n\rTwo second transition from WHITE to RED");

	float percent = 0.0;                        //percent keeps track of the percent of total time -> current_time/total_time
	int current_red, current_green, current_blue; //to hold the calculated values of the current LED color in each loop

	led_con(RED, GREEN, BLUE);    //white LED is lit

	//Transition from White LED to RED LED over 2 seconds
	reset_timer();
	while(get_timer() < TWO_SECONDS){

		if(get_timer() % FACTOR == 0){

			percent = get_timer();    //percent = 0, 5, 10, .. , 1995, 2000
			percent /= TWO_SECONDS;   //Calculating the percentage of final time

			//PWM transition calculations
			current_red =  RED;
			current_green = (LED_OFF - GREEN) * percent +  GREEN;
			current_blue = (LED_OFF - BLUE) * percent + BLUE;
			led_con(RED, current_green, current_blue);
		}
	}

	printf("\n\rTwo second transition from RED to GREEN");

	//Transition from RED LED to GREEN LED over 2 seconds
	reset_timer();
	while(get_timer() < TWO_SECONDS){

		if(get_timer() % FACTOR == 0){

			percent = get_timer();  //percent = 0, 5, 10, .. , 1995, 2000
			percent /= TWO_SECONDS; //Calculating percent

			//PWM transition calculations
			current_red = (LED_OFF - RED) * percent +  RED;
			current_green = (GREEN - LED_OFF) * percent + LED_OFF;
			current_blue = 0;
			led_con(current_red, current_green, current_blue);
		}
	}

	printf("\n\rTwo second transition from GREEN to BLUE");

	//Transition from GREEN LED to BLUE LED over 2 seconds
	reset_timer();
	while(get_timer() < TWO_SECONDS){

		if(get_timer() % FACTOR == 0){

			percent = get_timer();
			percent /= TWO_SECONDS; //Calculating percent

			//PWM transition calculations
			current_red = 0;
			current_green = (LED_OFF - GREEN) * percent + GREEN;
			current_blue = (BLUE - LED_OFF) * percent + LED_OFF;
			led_con(current_red, current_green, current_blue);
		}
	}

	//Transition from BLUE LED to WHITE LED over 2 seconds
	printf("\n\rTwo second transition from BLUE to WHITE");
	reset_timer();
	while(get_timer() < TWO_SECONDS){

		if(get_timer() % FACTOR == 0){

			percent = get_timer();
			percent /= TWO_SECONDS; //Calculating percent

			//PWM transition calculations
			current_red = (RED - LED_OFF) * percent + LED_OFF;
			current_green = (GREEN - LED_OFF) * percent + LED_OFF;
			current_blue = (BLUE - BLUE) * percent + BLUE;
			led_con(current_red, current_green, current_blue);
		}
	}


	printf("\n\rLED turned OFF");
	printf("\n\r************LED Testing Complete***********\n\r");
	led_con(LED_OFF, LED_OFF, LED_OFF);  //LED turned off

	return 1;

}
