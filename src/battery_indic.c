#include "battery_indic.h"

static uint8_t get_highest_bit_set(uint8_t data)
{
	uint8_t result = 0;
	for(int8_t i = 7; i >= 0; i--)
	{
		if(data & (1 << i))
		{
			return i;
		}
	}
}

uint8_t get_battery_level()
{
	uint8_t indic_input = INDIC_PIN & 0x0F;
	
	return get_highest_bit_set(indic_input);
}