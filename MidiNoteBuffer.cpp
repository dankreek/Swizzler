#include "MidiNoteBuffer.h"

MidiNote MidiNoteBuffer::buffer[MIDI_NOTE_BUF_SIZE];
uint8_t MidiNoteBuffer::size;
int8_t MidiNoteBuffer::lastNote;

void MidiNoteBuffer::begin() {	
	size=0;
	lastNote=-1;
}

void MidiNoteBuffer::removeMidiNote(MidiNote note) {
	for (int i=0; i < size; i++) {
		// If this index contains the note to be removed
		if (buffer[i].number == note.number) {
			// The last note struck is unstruck, remove it
			if (lastNote == i) lastNote = -1;
			
			closeHole(i);
			size--;

			// Update the last note pointer if it past the hole
			if (lastNote > i) lastNote--;

			return;
		}
	}
}

void MidiNoteBuffer::putMidiNote(MidiNote note) {
	int i;	// The index to put the data in
	
	// If this list is full, reject the insertion (huh huh)
	if (size == MIDI_NOTE_BUF_SIZE) return;
	
	// Find this note's place in the list
	for (i=0; i < size; i++) {
		if (buffer[i].number > note.number) {
			// Make a hole here for the note
			makeHole(i);
			
			// Insert the note
			buffer[i].number = note.number;

			break;
		}
		// Do not add the same note twice (shouldn't happen, but safety measure)
		else if (buffer[i].number == note.number) {
			return;	
		}
	}

	// Put note into the end of the list if it's higher than all other notes
	if (i == size) {
		buffer[i].number = note.number;
	}
	
	lastNote = i;	
	size++;
}

void MidiNoteBuffer::makeHole(uint8_t insert) {	
	for (uint8_t i = (size+1); i > insert; i--) {
		buffer[i].number = buffer[i-1].number;
	}
}

void MidiNoteBuffer::closeHole(uint8_t fill) {
	uint8_t i;
	
	for (i=fill; (i < size) && (i < (MIDI_NOTE_BUF_SIZE-1)); i++) {
		buffer[i].number = buffer[i+1].number;
	}
}
