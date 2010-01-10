#ifndef MIDINOTEBUFFER_H_
#define MIDINOTEBUFFER_H_

#include <inttypes.h>

struct MidiNote {
	unsigned char	number;
	unsigned char	velocity;
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
  	static int lastNote;
  
  	class NoteNode {
  		public:
  		MidiNote note;
  		bool alloc;	// Is this node allocated?
  	};
  	
  	// Initialize the Note Buffer
  	static void begin();
  	
  	//Add a new midi note in-order
	static void putMidiNote(MidiNote);

	// Remove a midi note from the buffer
	static void removeMidiNote(MidiNote);

  	// Buffer where the notes reside
  	static NoteNode buffer[MIDI_NOTE_BUF_SIZE];
  	
  private:
  	static void makeHole(int);
  	static void closeHole(int);
};

#endif /*MIDINOTEBUFFER_H_*/
