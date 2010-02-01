#include "NoteManager.h"
#include "MidiNoteBuffer.h"
#include "Swizzler.h"

void NoteManager::noteOn(uint8_t noteNumber) {
	MidiNoteBuffer::putMidiNote(noteNumber);

	// Restart the gate
	swizzler.envelope.openGate();
	swizzler.envelope.closeGate();

	// For debugging
	if (MidiNoteBuffer::size > 0) {
		digitalWrite(8, true);
	}
	else {
		digitalWrite(8, false);
	}
}

void NoteManager::noteOff(uint8_t noteNumber) {
	if (MidiNoteBuffer::size > 0) {
		// If this note is the current note that's playing then open the gate
		if (MidiNoteBuffer::getLastNote() == noteNumber)
			swizzler.envelope.openGate();

		MidiNoteBuffer::removeMidiNote(noteNumber);
	}

	// For debugging
	if (MidiNoteBuffer::size > 0) {
		digitalWrite(8, true);
	}
	else {
		digitalWrite(8, false);
	}
}
