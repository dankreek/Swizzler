#include <inttypes.h>
#include <WProgram.h>
#include "FreqMan.h"
#include "PortamentoManager.h"
#include "Bresenham.h"
#include "MidiNoteBuffer.h"
#include "waveout.h"
#include "envelope.h"

ArpManager FreqMan::arpMan;
PortamentoManager FreqMan::portMan;

bool FreqMan::portamentoOn;
bool FreqMan::arpeggioOn;
bool FreqMan::arpRunning;
uint8_t FreqMan::arpMinNotes;

/**
 * Frequency -> Note lookup table. These are the frequencies for
 * octave 3. All the frequencies for the lower frequencies are
 * found by dividing.
 */
int note_lookup[] = {
	2093,	// C
	2217, 	// C#
	2349,	// D
	2489,	// D#
	2637,	// E
	2794,	// F
	2960,	// F#
	3136,	// G
	3322,	// G#
	3520,	// A
	3729,	// A#
	3951,	// B
};

void FreqMan::begin() {
	portamentoOn = false;
	portMan.begin();

	arpMinNotes = 2;
	arpMan.arpTime = 50;
	enableArp(true);	
		
	MidiNoteBuffer::begin();
}

void FreqMan::enableArp(bool onOff) {
	if (onOff) {
		arpeggioOn = true;
		arpRunning = false;
	}
	else {
		arpeggioOn = false;
	}
}

void FreqMan::enablePortamento(bool onOff) {
	if (onOff && !portamentoOn) {
		portamentoOn = true;
		portMan.begin();
	}
	else if (!onOff && portamentoOn) {
		portamentoOn = false;
		if (portMan.destFreq > -1) Waveout::setFreq(portMan.destFreq);
	}
}

// TODO: This will be done via different algo's later, ie up, down, up&down, random, etc
void FreqMan::copyNoteBufferToArpBuffer() {
	for (int i=0; i < MidiNoteBuffer::size; i++) {
		arpMan.noteList[i] = MidiNoteBuffer::buffer[i].number;
	}
	arpMan.noteListSize = MidiNoteBuffer::size;
}	

void FreqMan::noteOn(int noteNumber) {
	MidiNote note;

	note.number = noteNumber;

	MidiNoteBuffer::putMidiNote(note);
	
	if (portamentoOn) {
		// If no previous note in the buffer then just play the note
		if (MidiNoteBuffer::size == 1) {
			portMan.nextDirectFreq(noteToFreq(noteNumber));
		}
		else {
			// If there is a previous note setup the glide
			portMan.nextGlideFreq(noteToFreq(noteNumber));		
		}

		// Restart the gate
		envelopeOut.openGate();	
		envelopeOut.closeGate();
	}
	else if (arpeggioOn) {
		// Open the gate if the min number of keys are down for an arp
		if (MidiNoteBuffer::size >= arpMinNotes) {
			// Copy the midi key buffer into the arp bufferin order from lowest to highest note
			stopArp();
			copyNoteBufferToArpBuffer();
			startArp();

			if (envelopeOut.gate == false) envelopeOut.closeGate();
		}
		else if (arpRunning) {
			stopArp();
		}
	}
	// No arpeggiating or portamento
	else {
		// Set the new frequency immediatly
		Waveout::setFreq(noteToFreq(noteNumber));

		// Restart the gate if this is a new note
		if (MidiNoteBuffer::size == 1) envelopeOut.closeGate();
	}

	// For debugging
	if (MidiNoteBuffer::size > 0) {
		digitalWrite(8, true);
	}
	else {
		digitalWrite(8, false);
	}
}

void FreqMan::startArp() {
	arpRunning = true;
	arpMan.restartArpeggio();

}

void FreqMan::stopArp() {
	envelopeOut.openGate();
	arpRunning = false;
}

void FreqMan::noteOff(int noteNumber) {
	MidiNote note;
	note.number = noteNumber;

	// If this note is the current note that's playing then open the gate
	if (MidiNoteBuffer::size > 0) { 
		if (!arpeggioOn) {
			if ((MidiNoteBuffer::lastNote > -1) && (MidiNoteBuffer::getLastNote().number == note.number)) {
				envelopeOut.openGate();	
			}
		}
		
		MidiNoteBuffer::removeMidiNote(note);

		if (arpeggioOn) {
			// Open the gate if there's not enough notes to make an arpeggio
			if (MidiNoteBuffer::size <  arpMinNotes) {
				stopArp();
			}
			// Modify the arpeggio if there is now one less note in it
			else {
				stopArp();
				copyNoteBufferToArpBuffer();
				startArp();
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

int FreqMan::noteToFreq(int noteNum) {
	//if (noteNum > 83) return 1047;

	int octave = noteNum / 12;
	int note = noteNum % 12;
	
	// Divides in half for the proper number of octaves
	return (note_lookup[note] >> (8-octave));
}

void FreqMan::nextTick() {
	if (arpeggioOn && arpRunning) {
		// If the next note in the arpeggio needs to be updated 
		if (arpMan.nextTick()) {
			if (portamentoOn) {
				// If portamento on, update portamento info
				portMan.nextGlideFreq(noteToFreq(arpMan.curNote()));
			}
			else {
				// Otherwise go directly to the next frequency
				Waveout::setFreq(noteToFreq(arpMan.curNote()));
			}	
		}
	}

	// If portamento's on and running then output the new frequency
	if (portamentoOn && !portMan.done) {
		if (portMan.nextTick()) Waveout::setFreq(portMan.curFreq);
	}
}
