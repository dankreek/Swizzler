#include "NoteManager.h"
#include "MidiNoteBuffer.h"
#include "Swizzler.h"

bool NoteManager::arpOn;
ArpManager NoteManager::arpManager;

void NoteManager::init()  {
	// Initialize the arpeggio manager
	arpManager.init();

	// Arpeggios are turned off by default
	enableArpeggio(false);
}

// TODO: There really doesn't need to be a setter here, just make arpOn public
void NoteManager::enableArpeggio(bool onOff) {
	arpOn = onOff;
}

void NoteManager::noteOn(uint8_t noteNumber) {
	// Put the note into the notes-on Arpbuffer
	MidiNoteBuffer::putMidiNote(noteNumber);

	// If the arpeggiator is running
	if (arpOn) {
		// If there's enough notes being held down start a new arpeggio
		if (MidiNoteBuffer::size  >= arpManager.minNotes) {
			reloadArpeggiator();
			restartGate();
		}
	}
	// If arpeggiator is off simply restart the gate
	else {
		FrequencyManager::newNote(noteNumber);
		restartGate();
	}

	// LED fun for debugging
	if (MidiNoteBuffer::size > 0) {
		digitalWrite(8, true);
	}
	else {
		digitalWrite(8, false);
	}
}

void NoteManager::restartGate() {
	swizzler.envelope.openGate();
	swizzler.envelope.closeGate();
}

void NoteManager::reloadArpeggiator() {
	// Make sure the nextTick() routine doesn't do anything until the next arp is setup
	arpManager.arpRunning = false;
	
	// Copy currently held notes into arpeggio buffer
	// (This might be factored out later to allow for different arpeggio directions,
	// currently only bottom-to-top is supported)
	for (int i=0; i < MidiNoteBuffer::buffer[i]; i++) {
		arpManager.noteList[i] = MidiNoteBuffer::buffer[i];
	}
	arpManager.noteListSize=MidiNoteBuffer::size;
				
	// Start a new arpeggio from the beginning
	arpManager.restartArpeggio();
}	

void NoteManager::noteOff(uint8_t noteNumber) {
	// Make sure the buffer's not already empty (could happen if a player mashes
	// down on a shitload of keys and lets them all off randomly)
	if (MidiNoteBuffer::size > 0) {
		if (!arpOn) {
			// If this note is the current note that's playing then open the gate
			if (MidiNoteBuffer::getLastNote() == noteNumber)
				swizzler.envelope.openGate();
		}

		MidiNoteBuffer::removeMidiNote(noteNumber);
		
		if (arpOn) {
			// If there are less notes being held down than the min. needed for an arp, close the gate
			if (MidiNoteBuffer::size < arpManager.minNotes) {
				swizzler.envelope.openGate();
			}
			// If there is still enough notes, restart the arpeggio
			else {
				reloadArpeggiator();
			}	
		}
	}

	// For debugging
	if (MidiNoteBuffer::size > 0) {
		digitalWrite(8, true);
	}
	else {
		digitalWrite(8, false);
	}
}
