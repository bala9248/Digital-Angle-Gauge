/**************************************************************************************************
*@File I2C.c
*
*This file Initializes I2C and enables I2C communication
*
*@Author Balapranesh Elango
*
*References : Dean's Github
*
***************************************************************************************************/
#include "I2C.h"


#define I2C_M_START 	I2C0->C1 |= I2C_C1_MST_MASK    //Start Bit
#define I2C_M_STOP  	I2C0->C1 &= ~I2C_C1_MST_MASK   //Stop Bit
#define I2C_M_RSTART 	I2C0->C1 |= I2C_C1_RSTA_MASK   //Repeated Start

#define I2C_TRAN		I2C0->C1 |= I2C_C1_TX_MASK     //Transmit Mode select
#define I2C_REC			I2C0->C1 &= ~I2C_C1_TX_MASK    //Transmit Mode Disable -- Receive mode

#define BUSY_ACK 	    while(I2C0->S & 0x01)          //Poll for Ack Signal
#define TRANS_COMP		while(!(I2C0->S & 0x80))       //Poll for Transfer Completion

#define NACK 	        I2C0->C1 |= I2C_C1_TXAK_MASK   //Transmit Ack enable  - NACK is sent on the following rx byte
#define ACK             I2C0->C1 &= ~I2C_C1_TXAK_MASK  //Transmit Ack Disable - Ack is sent  on the following rx byte

#define SCL	            (24)        //SCL line
#define SDA             (25)        //SDA line
#define SCL_DIV         (0x10)      //64
#define FREQ_MULT	    (0)         //Frequency multiplier => 0
#define SDA_REG         (I2C0->D)   //I2C SDA Register


/*
 * @void init_i2c()
 *
 * Initializes i2c communication interface in standard 100k baud
 *
 * Returns : None
 *
 * Paramaters : None
 */
void init_i2c() {
	//Enable clock to i2c peripheral and port E
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
	SIM->SCGC5 |= (SIM_SCGC5_PORTE_MASK);

	//set pins to I2C function
	PORTE->PCR[SCL] |= PORT_PCR_MUX(5);
	PORTE->PCR[SDA] |= PORT_PCR_MUX(5);

	//set to 100k baud
	//baud = bus freq/(scl_div+mul)
 	//~400k = 24M/(64); icr=0x12 sets scl_div to 64
 	I2C0->F = (I2C_F_ICR(SCL_DIV) | I2C_F_MULT(FREQ_MULT));

	//enable i2c and set to master mode
	I2C0->C1 |= (I2C_C1_IICEN_MASK);

	// Select high drive mode
	I2C0->C2 |= (I2C_C2_HDRS_MASK);
}

/*
 * @void i2c_wait()
 *
 * Waits for the completion of I2C transfer
 *
 * Returns : None
 *
 * Paramaters : None
 */
static void i2c_wait() {

	while(!(I2C0->S & I2C_S_IICIF_MASK))
		;//Wait for Interrupt flag to get set after transfer complete

	I2C0->S |= I2C_S_IICIF_MASK; //Clear Interrupt flag by writing one to it
}


/*
 * @void i2c_start()
 *
 * Transmit mode is set after which start bit is placed on the bus
 *
 * Returns : None
 *
 * Paramaters : None
 */
void i2c_start() {
	I2C_TRAN;		     /*set to transmit mode */
	I2C_M_START;	     /*send start	*/
}

/*
 * @void i2c_read_setup(uint8_t dev, uint8_t address)
 *
 * Sets up a read transaction by sending device addr,
 * read address in read mode
 *
 * Returns : None
 * Paramaters : dev     -> Device addr
 * 				address -> Read address
 */
void i2c_read_setup(uint8_t dev, uint8_t address)
{
	SDA_REG = dev;			  /*send dev address	*/
	i2c_wait();				  /*wait for completion */

	SDA_REG =  address;		  /*send read address	*/
	i2c_wait();				  /*wait for completion */

	I2C_M_RSTART;			  /*repeated start */
	SDA_REG = (dev|0x1);	  /*send dev address (read)	*/
	i2c_wait();				  /*wait for completion */

	I2C_REC;				  /*set to receive mode */

}

/*
 * @uint8_t i2c_repeated_read(uint8_t isLastRead)
 *
 * Reads bytes in repeated mode if read is already setup
 *
 * Returns : data -> data being read
 *
 * Paramaters : isLastRead to Nack/Ack as appropriate
 */
uint8_t i2c_repeated_read(uint8_t isLastRead) {

	uint8_t data;

	if(isLastRead)
		NACK;				/*set NACK after read	*/
	 else
		ACK;				/*ACK after read	*/


	data = SDA_REG;			/*dummy read	*/
	i2c_wait();				/*wait for completion */

	if(isLastRead)
		I2C_M_STOP;			/*send stop	*/

	data = SDA_REG;			/*read data	*/

	return  data;           /* Return Data that was read*/
}




/*
 * @void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data)
 *
 * To write a byte using 7-Bit mode to the given device and write address
 *
 * Returns : None
 *
 * Paramaters : dev     -> Device addr
 * 				address -> write address
 * 				data    -> data to be written
 */
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data) {

	I2C_TRAN;						   /*set to transmit mode */
	I2C_M_START;					   /*send start	*/
	SDA_REG = dev;			           /*send dev address	*/
	i2c_wait();						   /*wait for ack */

	SDA_REG =  address;		           /*send write address	*/
	i2c_wait();

	SDA_REG = data;				       /*send data	*/
	i2c_wait();
	I2C_M_STOP;

}
