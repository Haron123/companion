/*
T = Touch
D = Debounce
ELE = Electrode
*/


#ifndef MPR121_H
#define MPR121_H

#include <i2c.h>
#include <stdint.h>

/* Touch Status Register*/
#define T_STATUS_L 0x00
#define T_STATUS_H 0x01

typedef struct __attribute__((__packed__)) T_status
{
  uint16_t ele0 : 1;
  uint16_t ele1 : 1;
  uint16_t ele2 : 1;
  uint16_t ele3 : 1;
  uint16_t ele4 : 1;
  uint16_t ele5 : 1;
  uint16_t ele6 : 1;
  uint16_t ele7 : 1;
  uint16_t ele8 : 1;
  uint16_t ele9 : 1;
  uint16_t ele10 : 1;
  uint16_t ele11 : 1;
  uint16_t eleprox : 1;
  uint16_t reserved1 : 1;
  uint16_t reserved2 : 1;
  uint16_t ovcf : 1;
} T_status;

#define T_THRESHOLD_WRITE_START 0x41
#define T_THRESHOLD_INCREMENT 0x02
#define T_THRESHOLD_WRITE_END 0x59

#define R_THRESHOLD_START 0x42
#define R_THRESHOLD_INCREMENT 0x02
#define R_THRESHOLD_START 0x5A

#define DEBOUNCE_REGISTER 0x5B
#define DEBOUNCE_DT(N) (N & 7)
#define DEBOUNCE_DR(N) ((N & 7) << 4)

#define FILTER_CDT 0x5D
#define ESI(N) (N & 7)
#define SFI(N) ((N & 7) << 3)

#define ELECTRODE_CONFIG 0x5E
#define ELE_EN(N) (N & 0x0F)

typedef struct Mpr121
{
  uint8_t i2c_address;
} Mpr121;

void mpr121_setup(uint8_t i2c_address, uint8_t electrode_config, uint8_t debounce,
uint8_t filter_cdt);

uint16_t mpr121_get_pressed(int i2c_address);

#endif