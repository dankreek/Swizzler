/** @file ExternalEeprom.h
 *  @date Mar 20, 2010
 */

#ifndef EXTERNALEEPROM_H_
#define EXTERNALEEPROM_H_

#include <inttypes.h>

/**
 * Driver to write data to an external i2c EEPROM chip
 *
 * @author Justin May <may.justin@gmail.com>
 */
class ExternalEeprom {
  public:
    /**
     * The EEPROM chip I'm using has a 64 byte page size. Sequential reads can not
     * be read over a 64-byte page boundry which is why the PresetManager simply stores
     * each preset starting at an offset of (presetNumber * pageSize).
     */
    static const uint8_t PAGE_SIZE = 64;

    /**
     * Create a new External Eeprom object with the given i2c address.
     * This class should work with a number of ic2 eeprom devices, though its only
     * been tested on the Atmel AT24C256B
	 *
     * Records the i2c bus address for the eeprom being used. Note that Wire.begin()
     * must be called before anything in this class actually works
     *
     * @param i2cAddress	The i2c address of the eeprom chip
     */
    ExternalEeprom(uint8_t i2cAddress);

    /**
     * Write a block of memory to the EEPROM chip
     *
     * @param address The address to begin writing to on the EEPROM
     * @param buffer  A pointer to the data buffer that is to be written to the chip
     * @param size    The size (in bytes) of the data buffer
     */
    void writeBlock(uint16_t address, uint8_t* buffer, uint8_t size);

    /**
     * Read a block of memory from the EEPROM into the Atmega's ram
     *
     * @param address The address to begin reading from on the EEPROM
     * @param buffer  A pointer to the data buffer that will be written to
     * @param size    The number of bytes to be written into the buffer
     */
    void readBlock(uint16_t address, uint8_t* buffer, uint8_t size);

  private:
    /// i2c address of the EEPROM chip
    uint8_t i2cAddress;
};

#endif /* EXTERNALEEPROM_H_ */
