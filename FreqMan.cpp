#include <inttypes.h>
#include "FreqMan.h"
#include "Bresenham.h"
#include "MidiNoteBuffer.h"
#include "waveout.h"
#include "envelope.h"

bool FreqMan::portamentoOn;
int FreqMan::prevPortFreq;
bool FreqMan::portamentoDone;
int FreqMan::destPortFreq;
int FreqMan::portamentoTime;
Bresenham FreqMan::portamentoLine;

bool FreqMan::arpeggioOn;
uint8_t FreqMan::arpIndex;
uint16_t FreqMan::arpTimeCounter;
uint16_t FreqMan::arpTime;
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
	prevPortFreq = -1;
	destPortFreq = -1;
	portamentoTime = 100;

	arpeggioOn = true;
	arpMinNotes = 2;
	arpTime = 20;
		
	MidiNoteBuffer::begin();
}

void FreqMan::enableArp(bool onOff) {
	if (onOff) {
		arpIndex = 0;
		arpTimeCounter = 0;
		arpeggioOn = true;
		arpRunning = false;
	}
	else {
		arpeggioOn = false;
	}
}

void FreqMan::enablePortamento(bool onOff) {
	if (onOff) {
		portamentoOn = true;
		prevPortFreq = -1;
		destPortFreq = -1;
		portamentoDone = true;
	}
	else {
		portamentoOn = false;
		if (destPortFreq > -1) Waveout::setFreq(destPortFreq);
	}
}

void FreqMan::noteOn(int noteNumber) {
	MidiNote note;

	note.number = noteNumber;
	note.velocity = 127;

	MidiNoteBuffer::putMidiNote(note);
	
	if (portamentoOn) {
		// If no previous note has been struck
		if (prevPortFreq == -1) {
			prevPortFreq = noteToFreq(noteNumber);
			destPortFreq = prevPortFreq;
			portamentoDone = true;

			// Set the freq immediatly
			Waveout::setFreq(destPortFreq);
		}
		else {
			prevPortFreq = destPortFreq;
			destPortFreq = noteToFreq(noteNumber);
			portamentoDone = false;

			// Setup the portamento linear function
			portamentoLine.init(prevPortFreq, destPortFreq, portamentoTime);
		}

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
		envelopeOut.openGate();	
		envelopeOut.closeGate();
	}
}

void FreqMan::startArp() {
	arpTimeCounter = 0;
	arpRunning = true;
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
	if (portamentoOn && (!portamentoDone)) {
		int16_t nextFreq;
		portamentoDone = !portamentoLine.next(&nextFreq);

		if (portamentoDone) {
			nextFreq = destPortFreq;
		}

		Waveout::setFreq(nextFreq);
	}
	
	if (arpeggioOn && arpRunning) {
		// If this is the start of a new arpeggio note, play it!
		if ((arpTimeCounter == 0) && (MidiNoteBuffer::size >= arpMinNotes))   {
			arpIndex = (arpIndex + 1) % MidiNoteBuffer::size;
			Waveout::setFreq(noteToFreq(MidiNoteBuffer::buffer[arpIndex].note.number));
		}	

		
		// Increment arpeggio step timer
		arpTimeCounter = (arpTimeCounter + 1) % arpTime;
	}
}
