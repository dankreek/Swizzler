/*
 * ExternalEeprom.cpp
 *
 *  Created on: Mar 20, 2010
 *      Author: justin
 */

#include "ExternalEeprom.h"
#include "Wire.h"

//ExternalEeprom PresetEeprom = ExternalEeprom(Swizzler::eepromAddress);

/**
 * Records the i2c bus address for the eeprom being used. Note that Wire.begin()
 * must be called before anything in this class actually works
 */
ExternalEeprom::ExternalEeprom(uint8_t address) {
	// Record the eeprom's i2c address
	this->i2cAddress = address;
}

/**
 * Write a block of data to the EEPROM
 */
void ExternalEeprom::writeBlock(uint16_t address, uint8_t* buffer, uint8_t size) {
	Wire.beginTransmission(this->i2cAddress);
	Wire.send((int)(address >> 8)); // MSB
	Wire.send((int)(address & 0xFF)); // LSB

	for (uint8_t c = 0; c < size; c++) {
		Wire.send(buffer[c]);
	}

	Wire.endTransmission();
}

void ExternalEeprom::readBlock(uint16_t address, uint8_t* buffer, uint8_t size) {
	Wire.beginTransmission(this->i2cAddress);
	Wire.send((int)(address >> 8)); // MSB
	Wire.send((int)(address & 0xFF)); // LSB
	Wire.endTransmission();

	Wire.requestFrom(this->i2cAddress, size);

	for (uint8_t c = 0; c < size; c++ )	{
		if (Wire.available()) buffer[c] = Wire.receive();
	}
}

