/*
T = Touch
D = Debounce
ELE = Electrode
*/
#ifndef MPR121_H
#define MPR121_H

#include <i2c.h>
#include <stdint.h>
#include <ssd1306.h>

/* Touch Status Register*/
#define T_STATUS_L 0x00
#define T_STATUS_H 0x01

#define ELE0 (1 << 0)
#define ELE1 (1 << 1)
#define ELE2 (1 << 2)
#define ELE3 (1 << 3)
#define ELE4 (1 << 4)
#define ELE5 (1 << 5)
#define ELE6 (1 << 6)
#define ELE7 (1 << 7)
#define ELE8 (1 << 8)
#define ELE9 (1 << 9)
#define ELE10 (1 << 10)
#define ELE11 (1 << 11)

#define T_THRESHOLD_START 0x41
#define T_THRESHOLD_INCREMENT 0x02
#define T_THRESHOLD_END 0x59

#define R_THRESHOLD_START 0x42
#define R_THRESHOLD_INCREMENT 0x02
#define R_THRESHOLD_END 0x5A

#define DEBOUNCE_REGISTER 0x5B
#define DEBOUNCE_DT(N) (N & 7)
#define DEBOUNCE_DR(N) ((N & 7) << 4)

#define FILTER_CDC 0x5C
#define CDC(N) (N & 0x3F)
#define FFI(N) ((N & 3) << 6)

#define FILTER_CDT 0x5D
#define ESI(N) (N & 7)
#define SFI(N) ((N & 3) << 3)
#define CDT(N) ((N & 7) << 5)

#define ELECTRODE_CONFIG 0x5E
#define ELE_EN(N) (N & 0x0F)

#define ELECTRODE_DATA_START 0x04
#define ELECTRODE_DATA_END 0x01D
#define ELECTRODE_DATA_INCREMENT 0x02

void mpr121_setup(uint8_t i2c_address, uint8_t electrode_config, uint8_t debounce,
uint8_t filter_cdt, uint8_t filter_cdc);

void mpr121_get_pressed(uint8_t i2c_address, uint16_t* dst);

void mpr121_get_filtered_baseline(uint8_t i2c_address, uint16_t* dst);

void mpr121_get_filtered_pressed(uint8_t i2c_address, uint16_t* baseline, uint16_t* dst);

void mpr121_set_threshold(uint8_t i2c_address, uint8_t touch, uint8_t release);

int8_t mpr121_get_specific_pressed(uint16_t pressed_pads);

void mpr121_print_raw(uint8_t i2c_address);

#endif