#include "battery_indic.h"
#include "mpr121.h"
#include "ssd1306.h"

#define MPR121_ADDRESS 0x5A

int main(void)
{
    i2c_init();

    setup_battery_indic();
    mpr121_setup(MPR121_ADDRESS, ELE_EN(0b1100), DEBOUNCE_DT(0b001) | DEBOUNCE_DR(0b001), ESI(1) | SFI(1));
    oled_init();
    oled_clear();

    T_status pressed;

    while(1)
    {
        oled_set_cursor(0,0);
        mpr121_get_pressed(MPR121_ADDRESS, &pressed);
        oled_write_int(pressed.ele0);
    }
}