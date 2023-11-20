#include "i2c.h"

#define TW_SDA_PIN PC4
#define TW_SCL_PIN PC5

void i2c_init()
{
  // Enable pullup
  DDRC  |= (1 << TW_SDA_PIN) | (1 << TW_SCL_PIN);
  PORTC |= (1 << TW_SDA_PIN) | (1 << TW_SCL_PIN);
  
  // Setup bitrate register to desired scl frequency
  TWBR = TWBR_VALUE;

  // Set prescaler to 1
  TWSR = (0 << TWPS1) | (0 << TWPS0);

  // Enable i2c lines
  TWCR = (1 << TWEN) | (1 << TWSTO) | (0 << TWEA);
}

void i2c_close()
{
  // Clear the i2c control register
  TWCR = 0;
}

void i2c_start()
{
  // Start condition
  TWCR |= (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
  while (!(TWCR & (1<<TWINT)));
}

void i2c_stop()
{
  // Stop condition
  TWCR |= (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
}

void i2c_write(uint8_t data)
{
  // Write byte to the i2c data register
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1<<TWINT)));
}

int8_t i2c_read()
{
  TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
  while (!(TWCR & (1<<TWINT)));
  return TWDR;
}