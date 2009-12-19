#ifndef NOTE_LOOKUP_TABLE_H
#define NOTE_LOOKUP_TABLE_H

#include <WProgram.h>

extern int note_lookup[];


/**
 * Convert a Midi note to a frequency
 */
inline
int noteToFreq(int noteNum) {
	// C in octave 9 is the highest we're going to go! (C9 = 4186hz)
	if (noteNum > 107) return 4186;

	int octave = noteNum / 12;
	int note = noteNum % 12;
	
	// Divides in half for the proper number of octaves
	//return pgm_read_word_near(note_lookup + note) >> (8-octave);
	return (note_lookup[note] >> (8-octave));
}

#endif
