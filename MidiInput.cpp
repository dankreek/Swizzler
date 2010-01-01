#include <inttypes.h>
#include "MidiInput.h"
#include "MidiNoteBuffer.h"
#include "wavetable.h"
#include "FreqMan.h"

int MidiInput::midiCmd;
int MidiInput::midiData1;
int MidiInput::midiData2;

// Midi controller numbers
#define PORT_ON_OFF 	67
#define PORT_TIME	5

//#define SET_SAWTOOTH 	26
//#define SET_SQUARE 	83
//#define SET_NOISE 	86 
//#define SET_RANDOM	87

#define TRI_LEVEL	74
#define SAW_LEVEL	71
#define SQUARE_LEVEL	70
#define RAND_LEVEL	20
#define NOISE_LEVEL	21

void MidiInput::handleNoteOn() {
	// Most MIDI input devices send a NOTE ON message with a velocity of 0
	// to signal the note ending.
	if (midiData2 == 0) {
		handleNoteOff();
		return;
	}
	
	FreqMan::noteOn(midiData1);
}

void MidiInput::handleNoteOff() {	
	FreqMan::noteOff(midiData1);
}

void MidiInput::handlePitchBend() {
}

// Lots of fun with controllers!
void MidiInput::handleControlChange() {
	switch (midiData1) {
		case TRI_LEVEL:
			Wavetable::triLevel = (midiData2 >> 3);
			break;
		case SAW_LEVEL:
			Wavetable::sawLevel = (midiData2 >> 3);
			break;
		case SQUARE_LEVEL:
			Wavetable::sqLevel = (midiData2 >> 3);
			break;
		case RAND_LEVEL:
			Wavetable::randLevel = (midiData2 >> 3);
			break;
		case NOISE_LEVEL:
			Wavetable::noiseLevel = (midiData2 >> 3);
			break;
		case PORT_ON_OFF:
			FreqMan::enablePortamento( (midiData2 > 0) ? true : false);
			break;
		case PORT_TIME:
			FreqMan::portamentoTime = ((uint32_t)(midiData2+1) * (uint32_t)1000)/128;
			break;
	}
}

void MidiInput::handleProgramChange() {
}
