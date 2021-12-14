/**************************************************************************************************
*@File accelerometer.c
*
*This file Initializes the switch for GPIO interrupt and has the GPIO interrupt handler and an
*associated helper function to check if a swithch was pressed
*
*@Author Balapranesh Elango
*
*References : Dean's Github
*
***************************************************************************************************/
#include "accelerometer.h"


#define   MMA_ADDR     (0x3A)  //Accelerometer Device Address

#define   REG_XHI      (0x01)  //Register for X output - MSB

#define   REG_WHOAMI   (0x0D)  //Device ID Register address
#define   WHOAMI       (0x1A)  //Default Device ID

#define   REG_CTRL1    (0x2A)  //Control Register 1 Address
#define   REG_CTRL4    (0x2D)  //Control Register 4 Address

#define   ACTIVE_MODE  (0x01) //Setting Bit 0 of Control register1 for active mode


#define   COUNTS_PER_G (4096.0)      //Sensitivity - 2g mode
#define   M_PI         (3.14159265)  //PI
#define   PI_RAD       (180)         //19

#define   REPEAT_MODE  (0)           //0 -> Repeat mode
#define   END_REPEAT   (1)           //1 -> last byte in repeat mode

#define   Y_VAL        (1)  //Array element of Y_Val
#define   Z_VAL        (2)  //Array element of X_Val


/*
 * @int init_mma()
 *
 * Initializes the accelerometer sensor after I2C has been
 * initialized
 *
 * Parameters : None
 *
 * Returns : 1 after writing to the Control Register 1 of the Sensor
 */
int init_mma() {

	//set active mode, 14 bit samples and 800 Hz ODR
	i2c_write_byte(MMA_ADDR, REG_CTRL1, ACTIVE_MODE);
	return 1;
}


/*
 * int read_roll()
 *
 * Function to read the roll after reading y_val and z_val
 *
 * Parameters : None
 *
 * Returns : roll -> the calculated value of the roll
 */
int read_roll(){

	int i;
	uint8_t data[6];
	int16_t temp[3];
	int16_t roll = 0;
	int y_val, z_val;

	i2c_start();                        //Start bit is sent
	i2c_read_setup(MMA_ADDR , REG_XHI); //Device addr is sent, Read address is sent and set to receive mode

	// Read five bytes in repeated mode
	for( i=0; i<5; i++)	{
		data[i] = i2c_repeated_read(REPEAT_MODE);
	}
	// Read last byte ending repeated mode
	data[i] = i2c_repeated_read(END_REPEAT);

	//Extracting 16 bits of data from the data array and putting it in the temp array
	for (i = 0; i < 3; i ++)
		temp[i] = (int16_t) ((data[2*i]<<8) | data[2*i+1]);

	// Align for 14 bits
	y_val = temp[Y_VAL]/4;
	z_val = temp[Z_VAL]/4;

	//Convert angles to roll
	roll = atan2(y_val, z_val)* PI_RAD / M_PI;

	//return computed roll
	return roll;
}



