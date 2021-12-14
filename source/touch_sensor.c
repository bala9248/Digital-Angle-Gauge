/**************************************************************************************************
*@File touch_sensor.c
*
*This file Initializes the touch sensor to be used with interrupts and also houses the TSI Interrupt handler
*and a function to check if the touch sensor was pressed
*
*@Author Balapranesh Elango
*
*References :  "https://github.com/alexander-g-dean/ESF/blob/master/NXP/Misc/Touch%20Sense/TSI/src/main.c"
*
***************************************************************************************************/
#include "touch_sensor.h"


#define TOUCH_OFFSET   (550)                  // offset value to be subtracted
#define TOUCH_DATA     (TSI0->DATA & 0xFFFF)  //macro for extracting the count from data register
#define LEAST_VALUE    (130)                  //Values above which touch is detected
#define CHANNEL_NO     (10u)                  //Channel => 10

static volatile int status = 0;               //Global variable that is set in the IRQ when touch sensor is pressed

/*
 * @void Touch_Init()
 *
 * Initializes the Touch sensor to be used with an Interrupt
 *
 * Parameters : None
 *
 * Returns : None
 */
void Touch_Init(){
    // Enable clock for TSI PortB 16 and 17
    SIM->SCGC5 |= SIM_SCGC5_TSI_MASK;


	TSI0->GENCS = TSI_GENCS_MODE(0u) |
								TSI_GENCS_REFCHRG(0u) |
								TSI_GENCS_DVOLT(0u) |
								TSI_GENCS_EXTCHRG(0u) |
								TSI_GENCS_PS(0u) |
								TSI_GENCS_NSCN(31u) |
								TSI_GENCS_TSIEN_MASK |
								TSI_GENCS_STPE_MASK |  // enabling the TSI in low power modes
								TSI_GENCS_EOSF_MASK |
								TSI_GENCS_ESOR_MASK | //enabling interrupt using end of scan
								TSI_GENCS_TSIIEN_MASK; //enabling the TSI interrupt

	TSI0->DATA = 	TSI_DATA_TSICH(CHANNEL_NO); // selecting channel 10

	//enaling interrupt in NVIC
	NVIC_SetPriority(TSI0_IRQn, 2);
	NVIC_ClearPendingIRQ(TSI0_IRQn);
	NVIC_EnableIRQ(TSI0_IRQn);

	// Allow low leakage stop mode
	SMC->PMPROT = SMC_PMPROT_ALLS_MASK; //
	// Enable low-leakage stop mode and regular run mode
	SMC->PMCTRL = SMC_PMCTRL_STOPM(3) | SMC_PMCTRL_RUNM(0);
	SMC->STOPCTRL = SMC_STOPCTRL_PSTOPO(0) | SMC_STOPCTRL_VLLSM(3);

	// Enable LLWU - allow TSI0 to wake LLWU
	LLWU->ME |= LLWU_ME_WUME4_MASK;

}

/*
 * Touch Sensor IRQ handler
 */
void TSI0_IRQHandler (){
	int touch_val = TOUCH_DATA - TOUCH_OFFSET;

	if(touch_val > LEAST_VALUE)
		status = 1;
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK ; 	//writing one to clear the flag
}


/*
 * @int Touch_Scan_LH()
 *
 * Function to check if touch sensor was pressed
 *
 * Parameters : None
 *
 * Returns : 1  -> if touch sensor was pressed
 * 	         0  -> if touch sensor was not pressed
 */
int Touch_Scan_LH() {

	uint32_t masking_state = __get_PRIMASK();
	__disable_irq(); //to avoid race

	int ret = status;
	status = 0; //reset global variable after reading button status

	__set_PRIMASK(masking_state);
	return ret;
}

/*
 * void reset_touch()
 *
 * Function to reset previous touch detections by resetting the global variable
 *
 * Parameters : None
 *
 * Returns : None

 */
void reset_touch() {
	uint32_t masking_state = __get_PRIMASK();
	__disable_irq(); //to avoid race

	status = 0; //reset global variable to reset previous touch detection

	__set_PRIMASK(masking_state);
}
