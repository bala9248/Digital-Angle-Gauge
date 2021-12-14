/**************************************************************************************************
*@File uart.c
*
*This file Initializes UART0 with the given requirements and also has the IRQ handler for UART0
*
*@Author Balapranesh Elango
*
*References : Howdy's Lecture and Dean
*
***************************************************************************************************/

#include "UART.h"


#define  UART_OVERSAMPLE_RATE 	  (16)
#define  SYS_CLOCK				  (24e6)        //24Mhz as defined in sysclock.c

#define  BAUD_RATE                (38400)       // Baud rate
#define  STOP_BITS                (1)           // (0)-> 1 stop bit; (1)-> 2 Stop bits
#define  BIT_MODE                 (0)           // (0)-> 8 bit mode; (1)-> 9 bit mode
#define  PARITY_ENABLE            (0)	        // (0)-> Parity Disabled ; (1)-> Parity Enabled


volatile static int g_error_count = 0;//To keep track of errors in the ISR

/*
 * void Init_UART0()
 *
 * Function to Intialize UART0 with 8bits, 2 Stop bits , and no parity
 *
 * Parameters:
 *      	None
 * Returns:
 * 		 	None
**/
void Init_UART0() {
	uint16_t sbr;
	// Enable clock gating for UART0 and Port A
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	// Make sure transmitter and receiver are disabled before init
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

	// Set UART clock to Sys clock
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);

	// Set pins to UART0 Rx and Tx
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Rx
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Tx

	// Set baud rate and oversampling ratio
	sbr = (uint16_t)((SYS_CLOCK)/(BAUD_RATE * UART_OVERSAMPLE_RATE));
	UART0->BDH &= ~UART0_BDH_SBR_MASK;
	UART0->BDH |= UART0_BDH_SBR(sbr>>8);
	UART0->BDL = UART0_BDL_SBR(sbr);
	UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE-1);

	// Disable interrupts for RX active edge and LIN break detect, select two stop bit
	UART0->BDH |= UART0_BDH_RXEDGIE(0) | UART0_BDH_SBNS(STOP_BITS) | UART0_BDH_LBKDIE(0);

	// Don't enable loopback mode, use 8 data bit mode, don't use parity
	UART0->C1 = UART0_C1_LOOPS(0) | UART0_C1_M(BIT_MODE) | UART0_C1_PE(PARITY_ENABLE);
	// Don't invert transmit data, don't enable interrupts for errors
	UART0->C3 = UART0_C3_TXINV(0) | UART0_C3_ORIE(0)| UART0_C3_NEIE(0)
                    			| UART0_C3_FEIE(0) | UART0_C3_PEIE(0);

	// Clear error flags
	UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);

	// Send LSB first, do not invert received data
	UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);

	// Enable interrupts. Listing 8.11 on p. 234
	NVIC_SetPriority(UART0_IRQn, 2); // 0, 1, 2, or 3
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);

	// Enable receive interrupts but not transmit interrupts yet
	UART0->C2 |= UART_C2_RIE(1);

	// Enable UART receiver and transmitter
	UART0->C2 |= UART0_C2_RE(1) | UART0_C2_TE(1);

	// Clear the UART RDRF flag
	UART0->S1 &= ~UART0_S1_RDRF_MASK;
}


/*
 * UART0 IRQ Handler
 */
void UART0_IRQHandler(void) {
	uint8_t byte;
	const uint8_t error_flags = UART_S1_OR_MASK | UART_S1_NF_MASK |
	                            UART_S1_FE_MASK | UART_S1_PF_MASK;
	if (UART0->S1 & error_flags) {
			g_error_count++; //To keep track of erros
			// clear the error flags
			UART0->S1 |= error_flags;
			// read the data register to clear RDRF
			byte = UART0->D;
	}
	if (UART0->S1 & UART0_S1_RDRF_MASK) {
		// received a character
		byte = UART0->D;
		if (cbfifo_enqueue(RxQ, &byte, 1) != 1) {
            g_error_count++; //Buffer is full and byte is dropped
		}
	}
	if ( (UART0->C2 & UART0_C2_TIE_MASK) && // transmitter interrupt enabled
			(UART0->S1 & UART0_S1_TDRE_MASK) ) { // tx buffer empty
		// can send another character
	    if (cbfifo_dequeue(TxQ, &byte, 1)) {
	    	UART0->D = byte;
		} else {
			// queue is empty so disable transmitter interrupt
			UART0->C2 &= ~UART0_C2_TIE_MASK;
		}
	}
}

