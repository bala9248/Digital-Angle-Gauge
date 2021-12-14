/**************************************************************************************************
*@File I2C.h
*
*This file Initializes I2C and enables I2C communication
*
*@Author Balapranesh Elango
*
*References : Dean's Github
*
***************************************************************************************************/

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include <MKL25Z4.H>


/*
 * @void init_i2c()
 *
 * Initializes i2c communication interface in standard 100k baud
 *
 * Returns : None
 *
 * Paramaters : None
 */
void init_i2c(void);


/*
 * @void i2c_start()
 *
 * Transmit mode is set after which start bit is placed on the bus
 *
 * Returns : None
 *
 * Paramaters : None
 */
void i2c_start(void);

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
void i2c_read_setup(uint8_t dev, uint8_t address);

/*
 * @uint8_t i2c_repeated_read(uint8_t isLastRead)
 *
 * Reads bytes in repeated mode if read is already setup
 *
 * Returns : data -> data being read
 *
 * Paramaters : isLastRead to Nack/Ack as appropriate
 */
uint8_t i2c_repeated_read(uint8_t);

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
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data);


#endif /* I2C_H_ */
