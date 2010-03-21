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
#include "ExternalEeprom.h"

Preset PresetManager::curSettings;
uint8_t	PresetManager::curPreset;

// This is used to read in a preset from EEPROM before its settings are applied
Preset readStorage;

void PresetManager::setInitialSettings() {
}

void PresetManager::storePreset() {
	const byte* p = (const byte*)(const void*)&curSettings;
	uint16_t presetOfs = curPreset*sizeof(Preset);

	// Store preset to external EEPROM
	PresetEeprom.writeBlock(presetOfs, (byte*)(void*)&curSettings, sizeof(Preset));

	/*
	// Store preset to internal EEPROM
	for (int i=0; i < sizeof(curSettings); i++) {
		eeprom_write_byte(presetOfs+(unsigned char *)i, *p++);
	}
	*/
}

void PresetManager::loadPreset(uint8_t patchNum) {
	if (patchNum > 127) return;
	uint8_t* p = (uint8_t*)&readStorage;

	uint16_t presetOfs = patchNum * sizeof(Preset);

	// Read block from external EEPROM
	PresetEeprom.readBlock(presetOfs, p, sizeof(Preset));

	SetParameters::setAttackTime(readStorage.attackTime);
	SetParameters::setDecayTime(readStorage.decayTime);
	SetParameters::setSustainLevel(readStorage.sustainLevel);
	SetParameters::setReleaseTime(readStorage.releaseTime);

	SetParameters::setTriLevel(readStorage.triLevel);
	SetParameters::setSawtoothLevel(readStorage.sawLevel);
	SetParameters::setSquareLevel(readStorage.sqLevel);
	SetParameters::setRandomLevel(readStorage.randLevel);
	SetParameters::setNoiseLevel(readStorage.noiseLevel);
	SetParameters::setPulseWidth(readStorage.pulseWidth);

	SetParameters::setPortamentoTime(readStorage.portamentoTime);
	SetParameters::enablePortamento(readStorage.portamentoOn);

	SetParameters::setArpeggioTime(readStorage.arpeggioTime);
	SetParameters::setArpeggioMinNotes(readStorage.arpeggioMinNotes);
	SetParameters::enableArpeggio(readStorage.arpeggioOn);

	SetParameters::setBendRange(readStorage.bendRange);

	curPreset = patchNum;
}
