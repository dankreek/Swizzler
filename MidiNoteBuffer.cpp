#include "MidiNoteBuffer.h"

MidiNoteBuffer::NoteNode MidiNoteBuffer::buffer[MIDI_NOTE_BUF_SIZE];
int MidiNoteBuffer::size;
int MidiNoteBuffer::lastNote;

void MidiNoteBuffer::begin() {	
	size=0;
	lastNote=-1;
	for (int i=0; i < MIDI_NOTE_BUF_SIZE; i++) {
		buffer[i].alloc = false;
	}
}

void MidiNoteBuffer::removeMidiNote(MidiNote note) {
	for (int i=0; i < MIDI_NOTE_BUF_SIZE; i++) {
		if (buffer[i].note.number == note.number) {
			// The last note struck is unstruck, remove it
			if (lastNote == i) i = -1;
			
			closeHole(i);
			size--;

			// Update the last note pointer if it past the hole
			if (lastNote > i) lastNote--;

			break;
		}
	}
}

void MidiNoteBuffer::putMidiNote(MidiNote note) {
	int i;	// The index to put the data in
	
	// If this list is full, reject the insertion (huh huh)
	if (MidiNoteBuffer::size == (MIDI_NOTE_BUF_SIZE))
		return;
	
	// Find this note's place in the list
	for (i=0; i < size; i++) {
		if (buffer[i].note.number > note.number) {
			// Make a hole here for the note
			makeHole(i);
			
			// Insert the note
			buffer[i].note = note;
			buffer[i].alloc = true;

			break;
		}
		else if (buffer[i].note.number == note.number) {
			break;
		}
	}

	// Put note into the end of the list if it's higher than all other notes
	if (i >= size) {
		buffer[i].note = note;
		buffer[i].alloc = true;
	}
	
	lastNote = i;	
	size++;
}

void MidiNoteBuffer::makeHole(int insert) {	
	for (int i = size; i >= insert; i--) {
		buffer[i] = buffer[i-1];
	}
}

void MidiNoteBuffer::closeHole(int fill) {
	int i;
	
	for (i=fill; i < (MIDI_NOTE_BUF_SIZE-1); i++) {
		buffer[i] = buffer[i+1];
	}
	
	buffer[i].alloc = false;
}
