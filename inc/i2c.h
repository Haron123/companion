#ifndef I2C_H
#define I2C_H

#include "stdint.h"
#include <avr/io.h>

// Change these to fit ur system
#define CORE_CLOCK 16000000ULL
#define SCL_FREQ 40000ULL

// Gets calcualted by the core clock and scl freq macros
#define TWBR_VALUE (((CORE_CLOCK / SCL_FREQ) - 16) / 2)

#define READ_OPERATION 1
#define WRITE_OPERATION 0

/**
 * @brief initializes the i2c communication registers
*/
void i2c_init();

/**
 * @brief resets the i2c communication registers
*/
void i2c_close();

/**
 * @brief send the start signal for the i2c communication
*/
void i2c_start();

/**
 * @brief send the stop signal for the i2c communication
*/
void i2c_stop();

/**
 * @brief writes a byte on the i2c lines, needs to be used with i2c_start() and i2c_stop()
 * @param data the byte that you wanna write on the line
*/
void i2c_write(uint8_t data);

/**
 * @brief todo
*/
int8_t i2c_read_ack();

int8_t i2c_read_nak();

#endif