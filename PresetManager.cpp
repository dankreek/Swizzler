/*
 * PresetHandler.cpp
 *
 *  Created on: Mar 13, 2010
 *      Author: justin
 */

#include "PresetManager.h"
#include "Swizzler.h"
#include <avr/eeprom.h>
#include "Wire.h"

Preset PresetManager::curSettings;
uint8_t	PresetManager::curPreset;

void PresetManager::setInitialSettings() {
}

void PresetManager::storePreset() {
	const byte* p = (const byte*)(const void*)&curSettings;
	uint8_t presetOfs = curPreset*sizeof(Preset);

	// Store preset to external EEPROM
	for (int i=0; i < sizeof(Preset); i++) {
		int rdata = p[i];
		Wire.beginTransmission(Swizzler::eepromAddress);
		Wire.send((int)(presetOfs >> 8)); // MSB
		Wire.send((int)(presetOfs & 0xFF)); // LSB
		Wire.send(rdata);
		Wire.endTransmission();
	}

	/*
	// Store preset to internal EEPROM
	for (int i=0; i < sizeof(curSettings); i++) {
		eeprom_write_byte(presetOfs+(unsigned char *)i, *p++);
	}
	*/
}

void PresetManager::loadPreset(uint8_t patchNum) {
	if (patchNum > 18) return;

	Preset savedSettings;
	byte* p = (byte*)(void*)&savedSettings;

	uint8_t presetOfs = patchNum * sizeof(Preset);

	// Read a block from external EEPROM
	Wire.beginTransmission(Swizzler::eepromAddress);
	Wire.send(((int)presetOfs >> 8)); // MSB
	Wire.send(((int)presetOfs & 0xFF)); // LSB
	Wire.endTransmission();
	Wire.requestFrom(Swizzler::eepromAddress, sizeof(Preset));
	for (int c = 0; c < sizeof(Preset); c++ ) {
		if (Wire.available()) {
			p[c] = Wire.receive();
		}
	}
	/*
	// Read preset from internal EEPROM
	for (int i=0; i < sizeof(savedSettings); i++) {
		*p++ = eeprom_read_byte(presetOfs+(unsigned char *)i);
	}
	*/

	SetParameters::setAttackTime(savedSettings.attackTime);
	SetParameters::setDecayTime(savedSettings.decayTime);
	SetParameters::setSustainLevel(savedSettings.sustainLevel);
	SetParameters::setReleaseTime(savedSettings.releaseTime);

	SetParameters::setTriLevel(savedSettings.triLevel);
	SetParameters::setSawtoothLevel(savedSettings.sawLevel);
	SetParameters::setSquareLevel(savedSettings.sqLevel);
	SetParameters::setRandomLevel(savedSettings.randLevel);
	SetParameters::setNoiseLevel(savedSettings.noiseLevel);
	SetParameters::setPulseWidth(savedSettings.pulseWidth);

	SetParameters::setPortamentoTime(savedSettings.portamentoTime);
	SetParameters::enablePortamento(savedSettings.portamentoOn);

	SetParameters::setArpeggioTime(savedSettings.arpeggioTime);
	SetParameters::setArpeggioMinNotes(savedSettings.arpeggioMinNotes);
	SetParameters::enableArpeggio(savedSettings.arpeggioOn);

	SetParameters::setBendRange(savedSettings.bendRange);

	curPreset = patchNum;
}
