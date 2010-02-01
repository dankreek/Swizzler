#include <inttypes.h>
#include "MidiKnee.h"
#include "MidiInput.h"
#include "MidiNoteBuffer.h"
#include "wavetable.h"
#include "FreqMan.h"
#include "Swizzler.h"

// Knees to define how midi controls work, and the range for the control
MidiKnee portTimeKnee = MidiKnee(2000, 95, 500);
MidiKnee attackTimeKnee = MidiKnee(8000, 95, 1000);
MidiKnee decRelTimeKnee = MidiKnee(24000, 95, 2400);	// Decay/release time knee

int MidiInput::midiCmd;
int MidiInput::midiData1;
int MidiInput::midiData2;

// Midi controller numbers
#define PORT_ON_OFF 	67
#define PORT_TIME	5

#define ARP_ON_OFF	26

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
	if (midiData2 == 0) FrequencyManager::noteOff(midiData1);
	else FrequencyManager::noteOn(midiData1);
}

void MidiInput::handleNoteOff() {	
	FrequencyManager::noteOff(midiData1);
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
			FrequencyManager::enablePortamento((midiData2 > 0) ? true : false);
			break;
		case PORT_TIME:
			FrequencyManager::portMan.time = portTimeKnee.getValue(midiData2);
			break;
		case PULSE_WIDTH:
			Wavetable::pulseWidth = (midiData2 >> 3);
			Wavetable::genSquare();
			break;
		case ATTACK_TIME:
			swizzler.envelope.attackTime = attackTimeKnee.getValue(midiData2);
			break;
		case DECAY_TIME:
			swizzler.envelope.decayTime = decRelTimeKnee.getValue(midiData2);
			break;
		case SUSTAIN_LEVEL:
			swizzler.envelope.sustainLevel = (midiData2 >> 2);
			break;
		case RELEASE_TIME:
			swizzler.envelope.releaseTime = decRelTimeKnee.getValue(midiData2);
			break;
		case ARP_ON_OFF:
			break;
	}
}

void MidiInput::handleProgramChange() {
}
