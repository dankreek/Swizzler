#ifndef MIDINOTEBUFFER_H_
#define MIDINOTEBUFFER_H_

#include <inttypes.h>

struct MidiNote {
	uint8_t	number;
	uint8_t	velocity;
};

#define MIDI_NOTE_BUF_SIZE 10 

/**
 * This is essentially an ordered doubly-linked list that keeps track of every MIDI note that is being pressed,
 * plus an indicator as to which note was the last note to be played. This class is used to either play arpeggios or
 * tell what the last note hit was for monophonic synthesis.
 */ 
class MidiNoteBuffer {
  public:  
  	// The current size of the list (how many keys are being held down)
  	static uint8_t size;
  
  	// The index of the latest note that was struck in the buffer
  	static int8_t lastNote;
  
  	// Initialize the Note Buffer
  	static void begin();
  	
  	//Add a new midi note in-order
	static void putMidiNote(MidiNote);

	// Remove a midi note from the buffer
	static void removeMidiNote(MidiNote);

	// Get the last note that was struck
	inline static
	MidiNote getLastNote() {
		return buffer[lastNote];
	}

  	// Buffer where the notes reside
  	static MidiNote buffer[MIDI_NOTE_BUF_SIZE];
  	
  private:
  	static void makeHole(uint8_t);
  	static void closeHole(uint8_t);
};

#endif /*MIDINOTEBUFFER_H_*/
