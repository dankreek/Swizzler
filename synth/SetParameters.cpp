/*
 * SetParameters.cpp
 *
 *  Created on: Mar 9, 2010
 *      Author: justin
 */

#include "SetParameters.h"
#include "KnobKnee.h"
#include "PresetManager.h"

// Knees to define how midi controls work, and the range for the control
KnobKnee portTimeKnee = KnobKnee(2000, 95, 500);
KnobKnee attackTimeKnee = KnobKnee(8000, 95, 1000);
KnobKnee decRelTimeKnee = KnobKnee(24000, 95, 2400);	// Decay/release time knee
KnobKnee arpTimeKnee = KnobKnee(1000, 95, 250);			// Arpeggio time (ms per note)

void SetParameters::setTriLevel(uint8_t p) {
	Wavetable::triLevel = (p >> 3);
	PresetManager::curSettings.triLevel = p;
}

void SetParameters::setSawtoothLevel(uint8_t p) {
	Wavetable::sawLevel = (p >> 3);
	PresetManager::curSettings.sawLevel = p;
}

void SetParameters::setSquareLevel(uint8_t p) {
	Wavetable::sqLevel = (p >> 3);
	PresetManager::curSettings.sqLevel = p;
}

void SetParameters::setRandomLevel(uint8_t p) {
	Wavetable::randLevel = (p >> 3);
	PresetManager::curSettings.randLevel = p;
}

void SetParameters::setNoiseLevel(uint8_t p) {
	Wavetable::noiseLevel = (p >> 3);
	PresetManager::curSettings.noiseLevel = p;
}

void SetParameters::enablePortamento(uint8_t p) {
	FrequencyManager::enablePortamento((p > 0) ? true : false);
	PresetManager::curSettings.portamentoOn = p;
}

void SetParameters::setPortamentoTime(uint8_t p) {
	FrequencyManager::portMan.time = portTimeKnee.getValue(p);
	PresetManager::curSettings.portamentoTime = p;
}

void SetParameters::setPulseWidth(uint8_t p) {
	//Pulse width is a 4 bit value because the wavetables are 4bits long
	Wavetable::pulseWidth = (p >> 3);
	Wavetable::genSquare();
	PresetManager::curSettings.pulseWidth = p;
}

void SetParameters::setAttackTime(uint8_t p) {
	//swizzler.envelope.attackTime = attackTimeKnee.getValue(p);
	PresetManager::curSettings.attackTime = p;
}

void SetParameters::setDecayTime(uint8_t p) {
	//swizzler.envelope.decayTime = decRelTimeKnee.getValue(p);
	PresetManager::curSettings.decayTime = p;
}

void SetParameters::setSustainLevel(uint8_t p) {
	//swizzler.envelope.sustainLevel = p;
	PresetManager::curSettings.sustainLevel = p;
}

void SetParameters::setReleaseTime(uint8_t p) {
	//swizzler.envelope.releaseTime = decRelTimeKnee.getValue(p);
	PresetManager::curSettings.releaseTime = p;
}

void SetParameters::enableArpeggio(uint8_t p) {
	NoteManager::enableArpeggio((p > 0) ? true : false);
	PresetManager::curSettings.arpeggioOn = p;
}

void SetParameters::setArpeggioTime(uint8_t p) {
	// Tweaked to make 10 the minimum value.
	// XXX: Is this the best way to go about it?
	NoteManager::arpManager.arpTime = arpTimeKnee.getValue(p)+10;
	PresetManager::curSettings.arpeggioTime = p;
}

void SetParameters::setArpeggioMinNotes(uint8_t p) {
	// Ranges from 1-16
	NoteManager::arpManager.minNotes = (p >> 3)+1;
	PresetManager::curSettings.arpeggioMinNotes = p;
}

void SetParameters::setBendRange(uint8_t p) {
	// Bend range (in +/- half-steps) ranges from 0-15
	FrequencyManager::bendRange = (p >> 3);
	PresetManager::curSettings.bendRange = p;
}
