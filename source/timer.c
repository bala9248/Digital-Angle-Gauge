/**************************************************************************************************
*@File timer.c
*
*This file Initializes the systick timer to interrupt every 1msec
*This file also contains functions to generate a delay, find the time elapsed, etc.
*
*@Author Balapranesh Elango
*
*References : Howdy's Lecture
*
***************************************************************************************************/
#include "timer.h"

static ticktime_t g_program_start;          //time since beginning of program
static ticktime_t g_timer_start;            //time since reset
static volatile ticktime_t g_time_msec;     //global variable to keep track of time in msec


#define   PERIOD       (12000)      //Load value for the systick counter
#define   ENABLE_MSK   (0x7)        // Enable systick, Enable interrupt, enable with processor clock

/*
 * @void init_systick()
 *
 * Initializes systick timer and interrupt to interrupt
 * every 1msec
 *
 * Returns : None
 *
 * Paramaters : None
 */
void init_systick(){

	SysTick->LOAD = PERIOD; //Interrupts every 1msec
	SysTick->VAL = 0; //Reset VAL
	NVIC_SetPriority (SysTick_IRQn, 3);//Interrupt priority set to 3
	SysTick->CTRL = ENABLE_MSK; // Enable systick, Enable interrupt, enable with processor clock

	//setting all global variables to 0
	g_time_msec = 0;
	g_program_start = g_timer_start = g_time_msec;

}

/*
 * Systick IRQ handler
 */
void SysTick_Handler(void){
	g_time_msec++;  //Interrupts every 1 msec. So g_time_msec keeps track of time in msec
}

/*
 * @ticktime_t now()
 *
 * Calculates the time elapsed since the program startup
 *
 * Returns : returns the time since the program startup
 *
 * Parameters : none
 *
 */
ticktime_t now(){
	return g_time_msec - g_program_start;//Time elapsed since the beginning
}


/*
 * @void reset_timer()
 *
 * resets get_timer to 0 but does not affect now()
 *
 * Returns : None
 *
 * Parameters : None
 */
void reset_timer(){
	g_timer_start = g_time_msec;  //timer_start set to current time
}


/*
 * @ticktime_t get_timer()
 *
 * calculates the time since the last startup
 *
 * Returns : returns the time since the last reset
 *
 * Parameters : none
 */
ticktime_t get_timer(){
	return g_time_msec - g_timer_start; //Time since last reset
}


/*
 * @void delay(uint32_t delay_msec)
 *
 * Generated a delay of delay_msec
 *
 * Returns : None
 *
 * Parameters : delay_msec: used to create delay
 */
void delay(uint32_t delay_msec){

  ticktime_t curr_delay = g_time_msec;
  while ( (g_time_msec - curr_delay) <= delay_msec) //waits till delay time has elapsed
	  __asm volatile("NOP");
 }


