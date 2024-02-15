#include "ssd1306.h"

/** Default 5x7 monospace font */
const uint8_t FONT5X7[] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, /*   */
	0x00, 0x00, 0x5F, 0x00, 0x00, /* ! */
	0x00, 0x07, 0x00, 0x07, 0x00, /* " */
	0x14, 0x7F, 0x14, 0x7F, 0x14, /* # */
	0x24, 0x2A, 0x7F, 0x2A, 0x12, /* $ */
	0x23, 0x13, 0x08, 0x64, 0x62, /* % */
	0x36, 0x49, 0x55, 0x22, 0x50, /* & */
	0x00, 0x00, 0x03, 0x00, 0x00, /* ' */
	0x00, 0x1C, 0x22, 0x41, 0x00, /* ( */
	0x00, 0x41, 0x22, 0x1C, 0x00, /* ) */
	0x14, 0x08, 0x3E, 0x08, 0x14, /* * */
	0x08, 0x08, 0x3E, 0x08, 0x08, /* + */
	0x00, 0x50, 0x30, 0x00, 0x00, /* , */
	0x08, 0x08, 0x08, 0x08, 0x08, /* - */
	0x00, 0x60, 0x60, 0x00, 0x00, /* . */
	0x20, 0x10, 0x08, 0x04, 0x02, /* / */

	0x3E, 0x51, 0x49, 0x45, 0x3E, /* 0 */
	0x00, 0x42, 0x7F, 0x40, 0x00, /* 1 */
	0x62, 0x51, 0x49, 0x49, 0x46, /* 2 */
	0x22, 0x41, 0x49, 0x49, 0x36, /* 3 */
	0x18, 0x14, 0x12, 0x7F, 0x10, /* 4 */
	0x27, 0x45, 0x45, 0x45, 0x39, /* 5 */
	0x3C, 0x4A, 0x49, 0x49, 0x30, /* 6 */
	0x01, 0x71, 0x09, 0x05, 0x03, /* 7 */
	0x36, 0x49, 0x49, 0x49, 0x36, /* 8 */
	0x06, 0x49, 0x49, 0x29, 0x1E, /* 9 */

	0x00, 0x36, 0x36, 0x00, 0x00, /* : */
	0x00, 0x56, 0x36, 0x00, 0x00, /* ; */
	0x08, 0x14, 0x22, 0x41, 0x00, /* < */
	0x14, 0x14, 0x14, 0x14, 0x14, /* = */
	0x00, 0x41, 0x22, 0x14, 0x08, /* > */
	0x02, 0x01, 0x51, 0x09, 0x06, /* ? */
	0x32, 0x49, 0x79, 0x41, 0x3E, /* @ */

	0x7C, 0x12, 0x11, 0x12, 0x7C, /* A */
	0x41, 0x7F, 0x49, 0x49, 0x36, /* B */
	0x3E, 0x41, 0x41, 0x41, 0x22, /* C */
	0x41, 0x7F, 0x41, 0x41, 0x3E, /* D */
	0x7F, 0x49, 0x49, 0x49, 0x41, /* E */
	0x7F, 0x09, 0x09, 0x09, 0x01, /* F */
	0x3E, 0x41, 0x41, 0x49, 0x7A, /* G */
	0x7F, 0x08, 0x08, 0x08, 0x7F, /* H */
	0x00, 0x41, 0x7F, 0x41, 0x00, /* I */
	0x20, 0x40, 0x41, 0x3F, 0x01, /* J */
	0x7F, 0x08, 0x14, 0x22, 0x41, /* K */
	0x7F, 0x40, 0x40, 0x40, 0x40, /* L */
	0x7F, 0x02, 0x0C, 0x02, 0x7F, /* M */
	0x7F, 0x04, 0x08, 0x10, 0x7F, /* N */
	0x3E, 0x41, 0x41, 0x41, 0x3E, /* O */
	0x7F, 0x09, 0x09, 0x09, 0x06, /* P */
	0x3E, 0x41, 0x51, 0x21, 0x5E, /* Q */
	0x7F, 0x09, 0x19, 0x29, 0x46, /* R */
	0x26, 0x49, 0x49, 0x49, 0x32, /* S */
	0x01, 0x01, 0x7F, 0x01, 0x01, /* T */
	0x3F, 0x40, 0x40, 0x40, 0x3F, /* U */
	0x1F, 0x20, 0x40, 0x20, 0x1F, /* V */
	0x3F, 0x40, 0x38, 0x40, 0x3F, /* W */
	0x63, 0x14, 0x08, 0x14, 0x63, /* X */
	0x07, 0x08, 0x70, 0x08, 0x07, /* Y */
	0x61, 0x51, 0x49, 0x45, 0x43, /* Z */

	0x00, 0x7F, 0x41, 0x41, 0x00, /* [ */
	0x02, 0x04, 0x08, 0x10, 0x20, /* \ */
	0x00, 0x41, 0x41, 0x7F, 0x00, /* ] */
	0x04, 0x02, 0x01, 0x02, 0x04, /* ^ */
	0x40, 0x40, 0x40, 0x40, 0x40, /* _ */
	0x00, 0x01, 0x02, 0x04, 0x00, /* ` */

	0x20, 0x54, 0x54, 0x54, 0x78, /* a */
	0x7F, 0x48, 0x44, 0x44, 0x38, /* b */
	0x38, 0x44, 0x44, 0x44, 0x20, /* c */
	0x38, 0x44, 0x44, 0x48, 0x7F, /* d */
	0x38, 0x54, 0x54, 0x54, 0x18, /* e */
	0x08, 0x7E, 0x09, 0x01, 0x02, /* f */
	0x08, 0x54, 0x54, 0x54, 0x3C, /* g */
	0x7F, 0x08, 0x04, 0x04, 0x78, /* h */
	0x00, 0x48, 0x7D, 0x40, 0x00, /* i */
	0x20, 0x40, 0x44, 0x3D, 0x00, /* j */
	0x7F, 0x10, 0x28, 0x44, 0x00, /* k */
	0x00, 0x41, 0x7F, 0x40, 0x00, /* l */
	0x7C, 0x04, 0x78, 0x04, 0x78, /* m */
	0x7C, 0x08, 0x04, 0x04, 0x78, /* n */
	0x38, 0x44, 0x44, 0x44, 0x38, /* o */
	0x7C, 0x14, 0x14, 0x14, 0x08, /* p */
	0x08, 0x14, 0x14, 0x18, 0x7C, /* q */
	0x7C, 0x08, 0x04, 0x04, 0x08, /* r */
	0x48, 0x54, 0x54, 0x54, 0x20, /* s */
	0x04, 0x3F, 0x44, 0x40, 0x20, /* t */
	0x3C, 0x40, 0x40, 0x20, 0x7C, /* u */
	0x1C, 0x20, 0x40, 0x20, 0x1C, /* v */
	0x3C, 0x40, 0x30, 0x40, 0x3C, /* w */
	0x44, 0x28, 0x10, 0x28, 0x44, /* x */
	0x0C, 0x50, 0x50, 0x50, 0x3C, /* y */
	0x44, 0x64, 0x54, 0x4C, 0x44, /* z */

	0x00, 0x08, 0x36, 0x41, 0x00, /* { */
	0x00, 0x00, 0x7F, 0x00, 0x00, /* | */
	0x00, 0x41, 0x36, 0x08, 0x00, /* } */
	0x10, 0x08, 0x08, 0x10, 0x08  /* ~ */
};


// OLED init function
void oled_init(void) 
{
	//i2c_init();

  i2c_start();
  i2c_write(OLED_ADDR);
  i2c_write(OLED_CMD_MODE);
  i2c_write(0xAE); // Set display OFF		

  i2c_write(0xD4); // Set Display Clock Divide Ratio / OSC Frequency
  i2c_write(0x80); // Display Clock Divide Ratio / OSC Frequency 

  i2c_write(0xA8); // Set Multiplex Ratio
  i2c_write(0x3F); // Multiplex Ratio for 128x64 (64-1)

  i2c_write(0xD3); // Set Display Offset
  i2c_write(0x00); // Display Offset

  i2c_write(0x40); // Set Display Start Line

  i2c_write(0x8D); // Set Charge Pump
  i2c_write(0x14); // Charge Pump (0x10 External, 0x14 Internal DC/DC)

  i2c_write(0xA1); // Set Segment Re-Map
  i2c_write(0xC8); // Set Com Output Scan Direction

  i2c_write(0xDA); // Set COM Hardware Configuration
  i2c_write(0x12); // COM Hardware Configuration

  i2c_write(0x81); // Set Contrast
  i2c_write(0x01); // Contrast

  i2c_write(0xD9); // Set Pre-Charge Period
  i2c_write(0xF1); // Set Pre-Charge Period (0x22 External, 0xF1 Internal)

  i2c_write(0xDB); // Set VCOMH Deselect Level
  i2c_write(0x40); // VCOMH Deselect Level

  i2c_write(0x20); // Set Adressing mode
  i2c_write(0b00); // to Page addresing

  i2c_write(0xA4); // Set all pixels OFF
  i2c_write(0xA6); // Set display not inverted
  i2c_write(0xAF); // Set display On

  i2c_stop();

	oled_set_cursor(0, 0);
  oled_clear();
}

void oled_clear()
{
  i2c_start();
  i2c_write(OLED_ADDR);
  i2c_write(OLED_DAT_MODE);

  for(uint16_t i = 0; i < 1024; i++)
  {
    i2c_write(0x00);
  }

  i2c_stop();
}

void oled_write_image(const char image[])
{
  i2c_start();
  i2c_write(OLED_ADDR);
  i2c_write(OLED_DAT_MODE);

  for(uint16_t i = 0; i < 1024; i++)
  {
    i2c_write(pgm_read_word_near(image+i));
  }

  i2c_stop();
}

void oled_write_char(char c)
{
  i2c_start();
  i2c_write(OLED_ADDR);
  i2c_write(OLED_DAT_MODE);
  for(uint8_t i = 0; i < FONT_WIDTH; i++)
  {
    i2c_write(FONT5X7[((c * FONT_WIDTH) + i) - (160)]);
  }
	i2c_stop();
}

void oled_write_str(char* str)
{	
	uint8_t i = 0;

	// Ends one ealier to ignore delimiter
	while(str[i])
	{
		oled_write_char(str[i]);
		i++;
	}
}

void oled_write_int(uint16_t number)
{
	uint16_t reverse_number = 0;
	uint16_t overwrites = 3;
  uint16_t zeros = 0;

	if(!number)
	{
		oled_write_char('0');
		return;
	}

  // Reverses the numbers order of numbers, to print the right order
	while (number>0) 
	{
			reverse_number = reverse_number*10 + number%10;
      if(!(reverse_number*10 + number%10))
      {
        zeros++;
      }
			number /= 10;
	}

	while(reverse_number)
	{
		oled_write_char('0' + (reverse_number % 10));
		reverse_number /= 10;
	}

  while(zeros > 0)
  {
    oled_write_char('0');
    zeros--;
  }

  // Writes blanks after the number, to account for bigger numbers being written before
	while(overwrites)
	{
		oled_write_char(' ');
		overwrites--;
	}
}

void oled_set_cursor(uint8_t x_pos, uint8_t y_pos)
{ 
  i2c_start();
  i2c_write(OLED_ADDR);
  i2c_write(OLED_CMD_MODE);              // set command mode
  i2c_write(0xB0 | (y_pos & 0x07));        // set start page
  i2c_write(x_pos & 0x0F);                 // set low nibble of start column
  i2c_write(0x10 | (x_pos >> 4));          // set high nibble of start column
  i2c_stop(); 
}

void oled_write_byte(uint8_t byte)
{
	i2c_start();
  i2c_write(OLED_ADDR);
  i2c_write(OLED_DAT_MODE);
	i2c_write(byte);
	i2c_stop();
}