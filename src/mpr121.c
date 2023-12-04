#include "mpr121.h"

static void inline write_register(int i2c_address, int reg_value, int data)
{
  i2c_start();
  i2c_write((i2c_address << 1) | WRITE_OPERATION);
  i2c_write(reg_value);
  i2c_write(data);
  i2c_stop();
}

static uint8_t inline read_register(int i2c_address, int reg_value)
{
  uint8_t result = 0;

  i2c_start();
  i2c_write((i2c_address << 1) | WRITE_OPERATION);
  i2c_write(reg_value);
  i2c_start();
  i2c_write((i2c_address << 1) | READ_OPERATION);
  result = i2c_read_nak();
  i2c_stop();

  return result;
}

static inline void burst_read_register(uint8_t i2c_address, uint8_t start_register, uint8_t byte_amount, uint8_t* dst)
{
  i2c_start();
  i2c_write((i2c_address << 1) | WRITE_OPERATION);
  i2c_write(start_register);
  i2c_start();
  i2c_write((i2c_address << 1) | READ_OPERATION);
  for(uint8_t i = 0; i < byte_amount-1; i++)
  {
    *(dst + i) = i2c_read_ack();
  }
  *(dst + byte_amount - 1) = i2c_read_nak();

  i2c_stop();
}

void mpr121_setup(uint8_t i2c_address, uint8_t electrode_config, uint8_t debounce,
uint8_t filter_cdt, uint8_t filter_cdc)
{
  write_register(i2c_address, DEBOUNCE_REGISTER, debounce);
  write_register(i2c_address, ELECTRODE_CONFIG, electrode_config);
  write_register(i2c_address, FILTER_CDT, filter_cdt);
  write_register(i2c_address, FILTER_CDC, filter_cdc);
}

void mpr121_get_pressed(uint8_t i2c_address, uint16_t* dst)
{
  burst_read_register(i2c_address, T_STATUS_L, 2, (uint8_t*)dst);
}

void mpr121_get_filtered_baseline(uint8_t i2c_address, uint16_t* dst)
{
  uint16_t current_data = 0;
  uint16_t current_iter = 0;

  for(uint8_t i = ELECTRODE_DATA_START; i <= ELECTRODE_DATA_END; i += ELECTRODE_DATA_INCREMENT)
  {
    current_data = read_register(i2c_address, i);
    current_data |= ((read_register(i2c_address, i+1) & 3) << 8);
    dst[current_iter++] = current_data;
  }
}

void mpr121_get_filtered_pressed(uint8_t i2c_address, uint16_t* baseline, uint16_t* dst)
{
  uint16_t current_data = 0;
  uint16_t current_iter = 0;

  *dst = 0;

  for(uint8_t i = ELECTRODE_DATA_START; i <= ELECTRODE_DATA_END; i += ELECTRODE_DATA_INCREMENT)
  {
    current_data = read_register(i2c_address, i) | ((read_register(i2c_address, i+1) & 3) << 8);
    if(current_data < (baseline[current_iter++] - 2))
    {
      *dst |= (1 << current_iter);
    }
  }
}

void mpr121_set_threshold(uint8_t i2c_address, uint8_t touch, uint8_t release)
{
  // use i as our current address, we go from the lowest to the highest
  // address (touch_thr to release_thr) and increment by one
  for(int i = T_THRESHOLD_START; i < R_THRESHOLD_END; i++)
  {
    // If the index is an odd number its a register for touch
    if(i & 0x01)
    {
      write_register(i2c_address, i, touch);
    }
    else
    {
      write_register(i2c_address, i, release);
    }
  }
}

int8_t mpr121_get_specific_pressed(uint16_t pressed_pads)
{
  for(uint8_t i = 0; i < 12; i++)
  {
    if(pressed_pads & (1 << i))
    {
      return i;
    }
  }

  // No pads pressed
  return -1;
}