#ifndef NOTE_LOOKUP_TABLE_H
#define NOTE_LOOKUP_TABLE_H

/**
 * Frequency -> Note lookup table. These are the frequencies for
 * octave 3. All the frequencies for the lower frequencies are
 * found by dividing.
 */
int note_lookup[] PROGMEM = {
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


/**
 * Convert a Midi note to a frequency
 */
int noteToFreq(int noteNum) {
	if (noteNum > 107) return 4186;

	int octave = noteNum / 12;
	int note = noteNum % 12;
	
	// Divides in half for the proper number of octaves
	return note_lookup[note] >> (8-octave);
}

#endif
