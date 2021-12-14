/**************************************************************************************************
*@File LED.c
*
*This file Initializes the RGB leds for PWM and also controls the LEDs using PWM
*
*@Author Balapranesh Elango
*
*References : Dean Chapter 7
*
***************************************************************************************************/

#include "LED.h"

//#defines for LED Initialization
#define    RED_LED_GPIO_PORT       (GPIOB)    //GPIO Port B
#define    GREEN_LED_GPIO_PORT     (GPIOB)	  //GPIO Port B
#define    BLUE_LED_GPIO_PORT      (GPIOD)    //GPIO Port D

#define    RED_LED_PIN             (18)       //RED LED Pin number
#define    GREEN_LED_PIN           (19)       //GREEN LED Pin Number
#define    BLUE_LED_PIN            (1)        //BLUE LED Pin Number

#define    RED_LED_SCGC5_MASK      (SIM_SCGC5_PORTB_MASK)  //Clock Gating Mask for PORT B
#define    BLUE_LED_SCGC5_MASK     (SIM_SCGC5_PORTD_MASK)  //Clock Gating Mask for PORT D

#define    RED_LED_PIN_CTRL_REG    (PORTB->PCR[RED_LED_PIN])    //RED LED - Port Control Register
#define    GREEN_LED_PIN_CTRL_REG  (PORTB->PCR[GREEN_LED_PIN])  //Green LED - Port Control Register
#define    BLUE_LED_PIN_CTRL_REG   (PORTD->PCR[BLUE_LED_PIN])   //BLUE  LED - Port Control Register

#define    PERIOD                  (47999)     //Modulo value for counter
#define    SHIFT_BITS		       (8)         //8 -Bit shift

#define    START_TPM               (1)         //Starting TPM

/*
 * @void led_int()
 * Initializes the LED for PWM
 * Returns : None
 * Paramaters : None
 */
void led_init(){

	/*Setting up the clock for Port B and port D */
	SIM->SCGC5 |= RED_LED_SCGC5_MASK;
	SIM->SCGC5 |= BLUE_LED_SCGC5_MASK;

	/*Setting up the port multiplexing to I/O for all three LEDs */
	RED_LED_PIN_CTRL_REG &= ~PORT_PCR_MUX_MASK;
	RED_LED_PIN_CTRL_REG |= PORT_PCR_MUX(3);

	GREEN_LED_PIN_CTRL_REG &= ~PORT_PCR_MUX_MASK;
	GREEN_LED_PIN_CTRL_REG |= PORT_PCR_MUX(3);

	BLUE_LED_PIN_CTRL_REG &= ~PORT_PCR_MUX_MASK;
	BLUE_LED_PIN_CTRL_REG |= PORT_PCR_MUX(4);


	/* Configuring TPM */

	/*Enable Clock to TPM0 and TPM2 */
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;

	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK); //Set clock source for tpm: 48 MHz

	/*Load the counter and mod */
	TPM0->MOD = PERIOD;
	TPM2->MOD = PERIOD;

	/*set TPM count direction to up*/
	TPM0->SC =  TPM_SC_PS(0);
	TPM2->SC =  TPM_SC_PS(0);

	/*Continue operation in debug mode*/
	TPM0->CONF |= TPM_CONF_DBGMODE(3);
	TPM2->CONF |= TPM_CONF_DBGMODE(3);

	/*Set channel 1 and 0 to edge-aligned low-true PWM*/
	TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	TPM2->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;

	/*Set initial duty cycle*/
	TPM0->CONTROLS[1].CnV = 0;//Blue LED
	TPM2->CONTROLS[0].CnV = 0;//RED LED
	TPM2->CONTROLS[1].CnV = 0;//GREEN LED

	/*Start TPM*/
	TPM0->SC |= TPM_SC_CMOD(START_TPM);
	TPM2->SC |= TPM_SC_CMOD(START_TPM);
}

/*
 * @void led_con(int red, int green, int blue)
 * Used to Control LED with PWM
 * Returns : None
 * Paramaters : red, green, blue -> used to control the PWM for "Web Colors"
 */
void led_con(int red, int green, int blue){
	//Converting to 16 bits
	TPM2->CONTROLS[0].CnV = (red << SHIFT_BITS) ;//RED
	TPM2->CONTROLS[1].CnV = (green << SHIFT_BITS);//GREEN LED
	TPM0->CONTROLS[1].CnV = (blue << SHIFT_BITS);//Blue LED
}







