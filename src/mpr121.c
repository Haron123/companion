#include "mpr121.h"

static void write_register(int i2c_address, int reg_value, int data)
{
  i2c_start();
  i2c_write((i2c_address << 1) | WRITE_OPERATION);
  i2c_write(reg_value);
  i2c_write(data);
  i2c_stop();
}

static uint8_t read_register(int i2c_address, int reg_value)
{
  uint8_t result = 0;

  i2c_start();
  i2c_write((i2c_address << 1) | WRITE_OPERATION);
  i2c_write(reg_value);
  i2c_start();
  i2c_write((i2c_address << 1) | READ_OPERATION);
  result = i2c_read();
  i2c_stop();

  return result;
}

static void burst_read_register(uint8_t i2c_address, uint8_t start_register, uint8_t byte_amount, uint8_t* dst)
{
  i2c_start();
  i2c_write((i2c_address << 1) | WRITE_OPERATION);
  i2c_write(start_register);
  i2c_start();
  i2c_write((i2c_address << 1) | READ_OPERATION);
  while(uint8_t i = 0; i < byte_amount; i++)
  {
    dst[i] = i2c_read();
  }
  i2c_stop();
}

void mpr121_setup(uint8_t i2c_address, uint8_t electrode_config, uint8_t debounce,
uint8_t filter_cdt);
{
  write_register(i2c_address, DEBOUNCE_REGISTER, debounce);
  write_register(i2c_address, ELECTRODE_CONFIG, electrode_config);
  write_register(i2c_address, FILTER_CDT, filter_cdt);
}

T_status mpr121_get_pressed(int i2c_address)
{
  T_status result = 0;

  burst_read_register(i2c_address, T_STATUS_L, 2, (uint8_t*)&result);

  return result;
}