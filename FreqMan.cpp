#include "FreqMan.h"
#include "MidiNoteBuffer.h"
#include "waveout.h"
#include "envelope.h"

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

void FreqMan::noteOn(int noteNumber) {
	MidiNote note;

	note.number = noteNumber;
	note.velocity = 127;

	MidiNoteBuffer::putMidiNote(note);

	// Set the new frequency
	Waveout::setFreq(noteToFreq(noteNumber));

	// Restart the gate
	envelopeOut.openGate();	
	envelopeOut.closeGate();
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
	//return pgm_read_word_near(note_lookup + note) >> (8-octave);
	return (note_lookup[note] >> (8-octave));
}
