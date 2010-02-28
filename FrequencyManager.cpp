#include <inttypes.h>
#include <WProgram.h>
#include "FrequencyManager.h"
#include "PortamentoManager.h"
#include "Bresenham.h"
#include "MidiNoteBuffer.h"
#include "Waveout.h"
#include "Swizzler.h"

PortamentoManager FrequencyManager::portMan;
bool FrequencyManager::portamentoOn;
int8_t FrequencyManager::bendAmount;
uint8_t FrequencyManager::bendRange;
uint8_t FrequencyManager::curMidiNote;

/**
 * Frequency -> Note lookup table. These are the frequencies for
 * the 8th octave. All the frequencies for the lower frequencies are
 * found by dividing.
 */
int note_lookup[] = {
	2093,	// C
	2217, 	// C#
	2349,	// D
	2489,	// D#
	2637,	// E
	2794,	// F
	2960,	// F#
	3136,	// G
	3322,	// G#
	3520,	// A
	3729,	// A#
	3951,	// B
};

void FrequencyManager::init() {
	portamentoOn = false;
	portMan.init();
	
	MidiNoteBuffer::begin();
}

void FrequencyManager::newNote(uint8_t noteNumber) {
	// If portamento's on, start the glide
	if (portamentoOn) {
		// If no previous note in the buffer then just play the note at its frequency
		if (MidiNoteBuffer::isEmpty()) {
			portMan.nextDirectFreq(noteToFreq(noteNumber));
		}
		// If there is a previous note setup the glide
		else {
			portMan.nextGlideFreq(noteToFreq(noteNumber));
		}
	}
	// If no portamento then set the frequency directly
	else {
		Waveout::setFreq(noteToFreq(noteNumber));
	}
}

void FrequencyManager::enablePortamento(bool onOff) {
	// Turn portamento on
	if (onOff && !portamentoOn) {
		portamentoOn = true;
		portMan.init();
	}
	// Turn portamento off
	else if (!onOff && portamentoOn) {
		portamentoOn = false;
		// If a destination frequency has been defined from a previous glide, jump directly to it
		if (portMan.destFreq > -1) Waveout::setFreq(portMan.destFreq);
	}
}


uint16_t FrequencyManager::noteToFreq(uint8_t noteNum) {
	// TODO: Find the max frequency this thing will safely run at
	//if (noteNum > 83) return 1047;

	/**
	 * The MIDI standard defines note #0 as a 'C', so
	 * divide the note number by 12 to get the octave the note is in
	 * and take the remainder the find the note name.
	 */
	int octave = noteNum / 12;
	int note = noteNum % 12;
	
	curMidiNote = noteNum;

	// Divides in half for the proper number of octaves
	// (every right shift is one less octave)
	return (note_lookup[note] >> (8-octave));
}

void FrequencyManager::setBendAmount(int8_t ba) {
	bendAmount = ba;
	recalculateBendOffset();
}

void FrequencyManager::recalculateBendOffset() {
	// TODO: bendAmount needs to be unsigned, so going to have to store the direction in a different variable
	// No bend
	if (bendAmount == 0) bendOffset = 0;
	// Bend up
	else if (bendAmount > 0) {
		bendOffset = ((int16_t)bendAmount * noteToFreq(curMidiNote+bendAmount))/63;
	}
	// Bend down
	else {
		bendOffset = ((int16_t)bendAmount * noteToFreq(curMidiNote+bendAmount))/(-64);
	}
}

