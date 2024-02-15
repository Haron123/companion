#ifndef BATTERY_INDIC_H
#define BATTERY_INDIC_H

#include <avr/io.h>
#include <stdint.h>

#define INDIC_PIN PIND
#define INDIC_PORT PORTD
#define INDIC_DDR DDRD

#define INDIC_25_PIN (1 << PD3)
//#define INDIC_50_PIN PD3
#define INDIC_75_PIN (1 << PD5)
#define INDIC_100_PIN (1 << PD6)

#define LEVEL_0 0x00
#define LEVEL_25 0x01
#define LEVEL_50 0x03
#define LEVEL_75 0x07
#define LEVEL_100 0x0F

/**
 * @brief Sets up the pins as input for the battery indicator
 * @retval none
*/
void setup_battery_indic();

/**
 * @brief returns the battery indication level
 * @retval a number that represents the charge level corresponding to the
 * definitions in this header
*/
uint8_t get_battery_level();

#endif 