#include "MidiInput.h"
#include "MidiNoteBuffer.h"
#include "wavetable.h"
#include "envelope.h"
#include "waveout.h"
#include "NoteLookupTable.h"

int MidiInput::midiCmd;
int MidiInput::midiData1;
int MidiInput::midiData2;

// Midi controller numbers
#define SET_TRIANGLE 	67
#define SET_SAWTOOTH 	26
#define SET_SQUARE 	83
#define SET_NOISE 	86 
#define SET_RANDOM	87

void MidiInput::handleNoteOn() {
	MidiNote note;
	
	// Most MIDI input devices send a NOTE ON message with a velocity of 0
	// to signal the note ending.
	if (midiData2 == 0) {
		handleNoteOff();
		return;
	}
	
	// Record MIDI data
	note.number = midiData1;
	note.velocity = midiData2;
	
	// Put MIDI note onto the ordered list
	MidiNoteBuffer::putMidiNote(note);

	// Set the new frequency
	//Waveout::setFreq(noteToFreq(note.number));
	Waveout::setFreq(noteToFreq(midiData1));

	// Restart the gate
	envelopeOut.openGate();	
	envelopeOut.closeGate();
}

void MidiInput::handleNoteOff() {	
	MidiNote note;
	note.number = midiData1;

	// If this note is the current note that's playing then open the gate
	if (MidiNoteBuffer::size > 0) { 
		if (MidiNoteBuffer::buffer[MidiNoteBuffer::lastNote].note.number == note.number) {
			envelopeOut.openGate();	
		}
	}
	
	MidiNoteBuffer::removeMidiNote(note);
}

void MidiInput::handlePitchBend() {
}

// Lots of fun with controllers!
void MidiInput::handleControlChange() {
	switch (midiData1) {
		case SET_TRIANGLE:
			Wavetable::curWaveTable = Wavetable::triTable;
			break;
		case SET_SAWTOOTH:
			Wavetable::curWaveTable = Wavetable::sawTable;
			break;
		case SET_SQUARE:
			Wavetable::curWaveTable = Wavetable::sqTable;
			break;
		case SET_NOISE:
			Wavetable::curWaveTable = Wavetable::noiseTable;
			break;
		case SET_RANDOM:
			Wavetable::curWaveTable = Wavetable::randTable;
			break;
	}
}

void MidiInput::handleProgramChange() {
}
