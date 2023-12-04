#ifndef EEPROM_H
#define EEPROM_H

/**
 * @brief sets up the eeprom at the given i2c address
*/
void eeprom_setup(uint8_t i2c_address);

/**
 * @brief erases the whole eeprom at the given i2c address
*/
void eeprom_erase(uint8_t i2c_address);

/**
 * @brief writes a single byte to the given i2c address
 * @param eeprom_address the internal memory address of the eeprom that you wanna write to
 * @param byte the byte you wanna write to the eeprom
*/
void eeprom_write(uint8_t i2c_address, uint8_t eeprom_address, uint8_t byte);

/**
 * @brief writes a sixteen bytes to the given i2c address
 * @param eeprom_address the internal memory address of the eeprom start the write at
 * @param byte_sequence an array of 16 bytes that you wanna write to
*/
void eeprom_write_16(uint8_t i2c_address, uint8_t eeprom_address, uint8_t* byte_sequence);

/**
 * @brief reads the eeprom contents and returns it
 * @param eeprom_address the internal memory address of the eeprom that you wanna read from
*/
uint8_t eeprom_read(uint8_t i2c_address, uint8_t eeprom_address);



#endif