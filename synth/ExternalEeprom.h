/*
 * ExternalEeprom.h
 *
 *  Created on: Mar 20, 2010
 *      Author: justin
 */

#ifndef EXTERNALEEPROM_H_
#define EXTERNALEEPROM_H_

#include <inttypes.h>

class ExternalEeprom {
  public:
    /**
     * The EEPROM chip I'm using has a 64 byte page size. Sequential reads can not
     * be read over a 64-byte page boundry which is why the PresetManager simply stores
     * each preset starting at an offset of (presetNumber * pageSize).
     */
    static const uint8_t pageSize = 64;

    /**
     * Create a new External Eeprom object with the given i2c address.
     * This class should work with a number of ic2 eeprom devices, though its only
     * been tested on the Atmel AT24C256B
     */
    ExternalEeprom(uint8_t i2cAddress);

    /**
     * Write a block of memory to the EEPROM chip
     * @address	The address to begin writing to on the EEPROM
     * @buffer A pointer to the data buffer that is to be written to the chip
     * @size the size (in bytes) of the data buffer
     */
    void writeBlock(uint16_t address, uint8_t* buffer, uint8_t size);

    /**
     * Read a block of memory from the EEPROM into the Atmega's ram
     * @address	The address to begin reading from on the EEPROM
     * @buffer A pointer to the data buffer that will be written to
     * @size the number of bytes to be written into the buffer
     */
    void readBlock(uint16_t address, uint8_t* buffer, uint8_t size);

  private:
    uint8_t i2cAddress;
};

#endif /* EXTERNALEEPROM_H_ */
