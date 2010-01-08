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
	arpMan.arpTime = 20;
	enableArp(false);	
		
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

void FreqMan::noteOn(int noteNumber) {
	MidiNote note;

	note.number = noteNumber;
	note.velocity = 127;

	MidiNoteBuffer::putMidiNote(note);
	
	if (portamentoOn) {
		portMan.nextFreq(noteToFreq(noteNumber));		

		// Restart the gate
		envelopeOut.openGate();	
		envelopeOut.closeGate();
	}
	else if (arpeggioOn) {
		// Open the gate if the min number of keys are down for an arp
		if ((MidiNoteBuffer::size >= arpMinNotes) && !arpRunning) startArp();
		else if (arpRunning) stopArp();
	}
	else {
		// Set the new frequency immediatly
		Waveout::setFreq(noteToFreq(noteNumber));

		// Restart the gate
		envelopeOut.closeGate();
	}
}

void FreqMan::startArp() {
	arpRunning = false;
	envelopeOut.closeGate();
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
		if (MidiNoteBuffer::buffer[MidiNoteBuffer::lastNote].note.number == note.number) {
			envelopeOut.openGate();	
		}
	}

	MidiNoteBuffer::removeMidiNote(note);
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
				portMan.nextFreq(noteToFreq(arpMan.curNote()));
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
