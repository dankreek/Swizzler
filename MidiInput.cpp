#include <inttypes.h>
#include "MidiInput.h"
#include "MidiNoteBuffer.h"
#include "wavetable.h"
#include "FreqMan.h"
#include "envelope.h"

int MidiInput::midiCmd;
int MidiInput::midiData1;
int MidiInput::midiData2;

// The 16 values used to control the envelope timings. 
// Directly lifted from the SID chip
uint16_t attackTimes[] = {2, 8, 16, 24, 38, 56, 68, 80, 100, 250, 600, 800, 1000, 3000, 5000, 8000 };
uint16_t decRelTimes[] = {6, 24, 48, 72, 114, 168, 204, 240, 300, 750, 1500, 2400, 3000, 9000, 15000, 24000};

// Midi controller numbers
#define PORT_ON_OFF 	67
#define PORT_TIME	5

#define PULSE_WIDTH	12

#define TRI_LEVEL	74
#define SAW_LEVEL	71
#define SQUARE_LEVEL	70
#define RAND_LEVEL	20
#define NOISE_LEVEL	21

#define ATTACK_TIME	75
#define DECAY_TIME	76
#define SUSTAIN_LEVEL	77
#define RELEASE_TIME	14

void MidiInput::handleNoteOn() {
	// Most MIDI input devices send a NOTE ON message with a velocity of 0
	// to signal the note ending.
	if (midiData2 == 0) FreqMan::noteOff(midiData1);
	else FreqMan::noteOn(midiData1);
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
		case PULSE_WIDTH:
			Wavetable::pulseWidth = (midiData2 >> 3);
			Wavetable::genSquare();
			break;
		case ATTACK_TIME:
			envelopeOut.attackTime = attackTimes[midiData2 >> 3];
			break;
		case DECAY_TIME:
			envelopeOut.decayTime = decRelTimes[midiData2 >> 3];
			break;
		case SUSTAIN_LEVEL:
			envelopeOut.sustainLevel = (midiData2 >> 2);
			break;
		case RELEASE_TIME:
			envelopeOut.releaseTime = decRelTimes[midiData2 >> 3];
			break;
	}
}

void MidiInput::handleProgramChange() {
}
