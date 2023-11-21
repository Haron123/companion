#include "battery_indic.h"
#include "mpr121.h"
#include "ssd1306.h"

#define MPR121_ADDRESS 0x00

int main(void)
{
    setup_battery_indic();
    mpr121_setup(MPR121_ADDRESS, ELE_EN(0b1100), DEBOUNCE_DT(0b001) | DEBOUNCE_DR(0b001), ESI(0) | SFI(0));

    while(1)
    {^
        uint16_t pressed = mpr121_get_pressed(MPR121_ADDRESS)
        oled_write_int(pressed);
    }
}