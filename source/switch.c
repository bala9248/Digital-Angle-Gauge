/**************************************************************************************************
*@File switch.c
*
*This file Initializes the switch for GPIO interrupt and has the GPIO interrupt handler and an
*associated helper function to check if a swithch was pressed
*
*@Author Balapranesh Elango
*
*References : Howdy's Lecture
*
***************************************************************************************************/

#include "switch.h"


#define    SWITCH_SCGC5_MASK    (SIM_SCGC5_PORTD_MASK)    //Clock enable for PORT D
#define    SWITCH_PIN           (3)                       //Gpio pin 3
#define    SWITCH_CTRL_REG      (PORTD->PCR[SWITCH_PIN])  //Port Control register for switch
#define    SWITCH_GPIO_PORT     (GPIOD)                   //GPIO Port D
#define    SWITCH_ISFR          (PORTD->ISFR)             //Interrupt Status Flag Register
#define    LOGIC_LOW_INT        (8)                       //Interrupt on Logic Low

static volatile int g_button_pressed = 0;  //To keep track of button press


/*
 * @void switch_init()
 *
 * Initializes switch for GPIO interrupt
 *
 * Parameters : None
 *
 * Returns : None
 */
void switch_init(){

	SIM->SCGC5 |= SWITCH_SCGC5_MASK;       //Setting the clock

	SWITCH_CTRL_REG &= ~PORT_PCR_MUX_MASK; //Setting PCR Value
	SWITCH_CTRL_REG |= PORT_PCR_MUX(1);

	SWITCH_CTRL_REG |= PORT_PCR_PE(1) | PORT_PCR_PS(1); //Enable pull-up

	SWITCH_GPIO_PORT->PDDR &= ~(1 << SWITCH_PIN);  //Clear port data direction register for switch

	SWITCH_CTRL_REG |= PORT_PCR_IRQC(LOGIC_LOW_INT);  //Interrupt on logic LOW


	NVIC_SetPriority (PORTD_IRQn, 3);
	NVIC_EnableIRQ(PORTD_IRQn);          // Enabling the interrupt

}


/*
 * IRQ handler for GPIO Interrupt
 */
void PORTD_IRQHandler(void){

	if ( ( (SWITCH_ISFR) & (1 << SWITCH_PIN) ) == 0)
		return;
	g_button_pressed = 1;  //SET if switch is pressed

	SWITCH_ISFR &= (1 << SWITCH_PIN);  //Clear Interrupt status flag
}

/*
 * void restart_switch()
 *
 * Function to reset global variable that keeps track of the switch press
 *
 * Paramaters : None
 *
 * Returns : None
 */
void restart_switch(){

	uint32_t masking_state = __get_PRIMASK();
	__disable_irq();

	g_button_pressed = 0;  //reset global variable

	__set_PRIMASK(masking_state); //Enable interrupt state
}


/*
 * @int gpio_button_pressed()
 *
 * Function to check if switch is pressed
 *
 * Paramaters : None
 *
 * Returns : 1 if switch was pressed and 0 if switch was not pressedd
 */
int gpio_button_pressed(void){

		uint32_t masking_state = __get_PRIMASK();
		__disable_irq();               //to avoid race

		int ret = g_button_pressed;
		g_button_pressed = 0;         //reset global variable after reading button status

		__set_PRIMASK(masking_state); //Enable interrupt state
		return ret;
}

