#include <inttypes.h>
#include "FrequencyManager.h"
#include "PortamentoManager.h"
#include "Bresenham.h"
#include "MidiNoteBuffer.h"
#include "Swizzler.h"

PortamentoManager FrequencyManager::portMan;
bool FrequencyManager::portamentoOn;
uint8_t FrequencyManager::bendRange;
uint8_t FrequencyManager::curMidiNote;
int16_t FrequencyManager::bendOffset;
uint16_t FrequencyManager::curFreq;
int8_t FrequencyManager::bendAmount;

/**
 * Frequency -> Note lookup table. These are the frequencies for
 * the 8th octave. All the frequencies for the lower frequencies are
 * found by dividing.
 */
int note_lookup[] = {
	4186,	// C
	4435, 	// C#
	4699,	// D
	4978,	// D#
	5274,	// E
	5588,	// F
	5920,	// F#
	6272,	// G
	6645,	// G#
	7040,	// A
	7459,	// A#
	7902,	// B
};

void FrequencyManager::init() {
	portamentoOn = false;
	portMan.init();

	bendOffset = 0;
	bendRange = 2;
}

void FrequencyManager::newNote(uint8_t noteNumber) {
	curMidiNote = noteNumber;

	if (bendAmount != 0) recalculateBendOffset();

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
		setBaseFrequency(noteToFreq(noteNumber));
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
		if (portMan.destFreq > -1) setBaseFrequency(portMan.destFreq);
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

	// Divides in half for the proper number of octaves
	// (every right shift is one less octave)
	return (note_lookup[note] >> (9-octave));
}

void FrequencyManager::setBendAmount(int8_t ba) {
	bendAmount = ba;
	recalculateBendOffset();
	sendFrequency();
}

void FrequencyManager::recalculateBendOffset() {
	// Bend up
	if (bendAmount > 0) {
		bendOffset = (bendAmount * (int16_t)(noteToFreq(curMidiNote+bendRange)-noteToFreq(curMidiNote)))/63;
	}
	// Bend down
	else if (bendAmount < 0) {
		//digitalWrite(8, true);
		bendOffset = (bendAmount * (int16_t)(noteToFreq(curMidiNote)-noteToFreq(curMidiNote-bendRange)))/64;
	}
	// No bend
	else {
		bendOffset = 0;
	}
}

void FrequencyManager::setBaseFrequency(uint16_t freq) {
  curFreq = freq;
  sendFrequency();
}

void FrequencyManager::sendFrequency() {
  for (int i=0;i<4;i++) Swizzler::soundChip.setFrequency(i, curFreq+bendOffset);
}
