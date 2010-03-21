/*
 * ExternalEeprom.h
 *
 *  Created on: Mar 20, 2010
 *      Author: justin
 */

#ifndef EXTERNALEEPROM_H_
#define EXTERNALEEPROM_H_

#include "Swizzler.h"
#include <inttypes.h>

class ExternalEeprom {
public:
	ExternalEeprom(uint8_t i2cAddress);
	void writeBlock(uint16_t address, byte* buffer, uint8_t size);
	void readBlock(uint16_t address, byte* buffer, uint8_t size);
private:
	uint8_t	i2cAddress;
};

extern ExternalEeprom PresetEeprom;

#endif /* EXTERNALEEPROM_H_ */
