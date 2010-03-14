/*
 * PresetHandler.cpp
 *
 *  Created on: Mar 13, 2010
 *      Author: justin
 */

#include "PresetManager.h"
#include "Swizzler.h"
#include <avr/eeprom.h>

Preset PresetManager::curSettings;

void PresetManager::setInitialSettings() {
}

void PresetManager::savePoweronSettings() {
	const byte* p = (const byte*)(const void*)&curSettings;

	for (int i=0; i < sizeof(curSettings); i++) {
		eeprom_write_byte((unsigned char *)i, *p++);
	}
}

void PresetManager::loadPoweronSettings() {
	Preset savedSettings;
	byte* p = (byte*)(void*)&savedSettings;

	for (int i=0; i < sizeof(savedSettings); i++) {
		*p++ = eeprom_read_byte((unsigned char *)i);
	}

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
}
