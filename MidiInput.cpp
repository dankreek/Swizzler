#include "MidiInput.h"
#include "MidiNoteBuffer.h"
#include "envelope.h"
#include "waveout.h"
#include "NoteLookupTable.h"

int MidiInput::midiCmd;
int MidiInput::midiData1;
int MidiInput::midiData2;



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
	if (MidiNoteBuffer::size > 0) 
		if (MidiNoteBuffer::buffer[MidiNoteBuffer::lastNote].note.number == note.number) {
			envelopeOut.openGate();	
		}

	
	MidiNoteBuffer::removeMidiNote(note);
}

void MidiInput::handlePitchBend() {
}

void MidiInput::handleControlChange() {
}

void MidiInput::handleProgramChange() {
}
