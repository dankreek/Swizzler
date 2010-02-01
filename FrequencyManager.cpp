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
	portMan.begin();
	
	MidiNoteBuffer::begin();
}

void FrequencyManager::newNote(uint8_t noteNumber) {
	// If portamento's on, start the glide
	if (portamentoOn) {
		// If no previous note in the buffer then just play the note
		if (MidiNoteBuffer::lastNote == -1) {
			portMan.nextDirectFreq(noteToFreq(noteNumber));
		}
		else {
			// If there is a previous note setup the glide
			portMan.nextGlideFreq(noteToFreq(noteNumber));
		}
	}
	// Set the frequency directly
	else {
		Waveout::setFreq(noteToFreq(noteNumber));
	}
}

void FrequencyManager::enablePortamento(bool onOff) {
	if (onOff && !portamentoOn) {
		portamentoOn = true;
		portMan.begin();
	}
	else if (!onOff && portamentoOn) {
		portamentoOn = false;
		if (portMan.destFreq > -1) Waveout::setFreq(portMan.destFreq);
	}
}


int FrequencyManager::noteToFreq(uint8_t noteNum) {
	//if (noteNum > 83) return 1047;

	int octave = noteNum / 12;
	int note = noteNum % 12;
	
	// Divides in half for the proper number of octaves
	return (note_lookup[note] >> (8-octave));
}

void FrequencyManager::nextTick() {
	// If portamento's on and running then output the new frequency
	if (portamentoOn && !portMan.done) {
		if (portMan.nextTick()) Waveout::setFreq(portMan.curFreq);
	}
}
