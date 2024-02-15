#include "battery_indic.h"

void setup_battery_indic()
{
	INDIC_DDR &= ~((INDIC_25_PIN) | (INDIC_75_PIN) | (INDIC_100_PIN));
  INDIC_PORT |= ((INDIC_25_PIN) | (INDIC_75_PIN) | (INDIC_100_PIN));
}

uint8_t get_battery_level()
{
	uint8_t indic_input = !!(INDIC_PIN & INDIC_25_PIN) << 2 | !!(INDIC_PIN & INDIC_75_PIN) << 1 | !!(INDIC_PIN & INDIC_100_PIN);
	
	return indic_input;
}