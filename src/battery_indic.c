#include "battery_indic.h"

void setup_battery_indic()
{
	INDIC_DDR &= ~(0x0F);
}

uint8_t get_battery_level()
{
	uint8_t indic_input = INDIC_PIN & 0x0F;
	
	return indic_input;
}