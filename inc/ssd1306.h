#ifndef SSD1306_H
#define SSD1306_H

#include <avr/io.h>
#include "i2c.h"

// To get the oled addr, shift the actual i2c address one to the left
#define OLED_ADDR 0x78
#define OLED_CMD_MODE 0x00
#define OLED_DAT_MODE 0x40

#define FONT_WIDTH 5

/**
 * @brief initializes the OLED with the i2c line
*/
void oled_init(void);

/**
 * @brief clears the oled display
*/
void oled_clear();

/**
 * @brief writes a ascii character onto the display
 * @param c the ascii character that should be written
*/
void oled_write_char(char c);

/**
 * @brief writes a string to the display
 * @param str the string thats to be written
 * @param str_size the size of the given string
*/
void oled_write_str(char* str);

/**
 * @brief prints an integer onto the display
 * @param number the number to be written on the display
*/
void oled_write_int(uint16_t number);

/**
 * @brief changes the cursor position on the oled
 * @param x_pos x position of the cursor (0-127)
 * @param y_pos y position of the cursor (0-7)
*/
void oled_set_cursor(uint8_t x_pos, uint8_t y_pos);

#endif