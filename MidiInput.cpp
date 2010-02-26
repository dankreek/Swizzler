#include <inttypes.h>
#include "KnobKnee.h"
#include "MidiInput.h"
#include "Swizzler.h"

// Knees to define how midi controls work, and the range for the control
KnobKnee portTimeKnee = KnobKnee(2000, 95, 500);
KnobKnee attackTimeKnee = KnobKnee(8000, 95, 1000);
KnobKnee decRelTimeKnee = KnobKnee(24000, 95, 2400);	// Decay/release time knee
KnobKnee arpTimeKnee = KnobKnee(1000, 95, 250);			// Arpeggio time (ms per note)

int16_t MidiInput::midiCmd;
int16_t MidiInput::midiData1;
int16_t MidiInput::midiData2;

// Midi controller numbers
#define PORT_ON_OFF 67
#define PORT_TIME	5

#define ARP_ON_OFF	26
#define ARP_TIME    13

#define PULSE_WIDTH	12

#define TRI_LEVEL    74
#define SAW_LEVEL	 71
#define SQUARE_LEVEL 70
#define RAND_LEVEL   20
#define NOISE_LEVEL  21

#define ATTACK_TIME     75
#define DECAY_TIME      76
#define SUSTAIN_LEVEL   77
#define RELEASE_TIME    14

void MidiInput::handleNoteOn() {
	/**
	 * Most MIDI input devices send a NOTE ON message with a velocity of 0
	 * to signal the note ending.
	 */
	if (midiData2 == 0) NoteManager::noteOff(midiData1);
	else NoteManager::noteOn(midiData1);
}

void MidiInput::handleNoteOff() {	
	NoteManager::noteOff(midiData1);
}

void MidiInput::handlePitchBend() {
	// I'm going to ignore the least significant byte of this message for now
	// (my controller only sends 0 for the LSB anyway, so who cares)

}

// Lots of fun with controllers!
void MidiInput::handleControlChange() {
	/**
	 * In the MIDI protocol the 1st byte (midiData1) is the controller number and
	 * the 2nd byte (midiData2) is the value of the controller (7bits)
	 */
	switch (midiData1) {
		/**
		 * All the oscillator level settings are 4bit values
		 */
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

		/**
		 * Portamento Controls
		 */
		case PORT_ON_OFF:
			FrequencyManager::enablePortamento((midiData2 > 0) ? true : false);
			break;
		case PORT_TIME:
			FrequencyManager::portMan.time = portTimeKnee.getValue(midiData2);
			break;
		//Pulse width is a 4 bit value because the wavetables are 4bits long
		case PULSE_WIDTH:
			Wavetable::pulseWidth = (midiData2 >> 3);
			Wavetable::genSquare();
			break;

		/**
		 * Envelope value ares calculated using a knee
		 */
		case ATTACK_TIME:
			swizzler.envelope.attackTime = attackTimeKnee.getValue(midiData2);
			break;
		case DECAY_TIME:
			swizzler.envelope.decayTime = decRelTimeKnee.getValue(midiData2);
			break;
		case RELEASE_TIME:
			swizzler.envelope.releaseTime = decRelTimeKnee.getValue(midiData2);
			break;
		// Except sustain level, it's a 5bit value for right now
		case SUSTAIN_LEVEL:
			swizzler.envelope.sustainLevel = (midiData2 >> 2);
			break;


		// Arpeggio controls
		case ARP_ON_OFF:
			NoteManager::enableArpeggio((midiData2 > 0) ? true : false);
			break;
		// Arp time is measured in milliseconds per note
		case ARP_TIME:
			// Tweaked to make 10 the minimum value.
			// XXX: Is this the best way to go about it?
			NoteManager::arpManager.arpTime = arpTimeKnee.getValue(midiData2)+10;
			break;
	}
}

void MidiInput::handleProgramChange() {
}
