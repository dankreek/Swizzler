#ifndef MIDIINPUT_H_
#define MIDIINPUT_H_

#include "Swizzler.h"

class MidiInput {
public:
	// Current MIDI command data
	static int midiCmd;
	static int midiData1;
	static int midiData2;
	
	static const unsigned char noteOff = 0x80;
	static const unsigned char noteOn = 0x90;
	static const unsigned char polyAfterTouch = 0xa0;
	static const unsigned char ctrlChange = 0xb0;
	static const unsigned char prgmChange = 0xc0;
	static const unsigned char afterTouch = 0xd0;
	static const unsigned char pitchbend = 0xe0;
	static const unsigned char sysExMsg = 0xf0;
		
	/**
	 * Initialize it
	 */
	static inline
	void init() {
		midiCmd=-1;
		midiData1=-1;
		midiData2=-1;
	}
		
	/**
	 * Push a byte onto the Midi stack. This will be called by an interrupt routine or some shits.
	 */
	inline static
	void pushByte(uint8_t byte) {
		// Throw out system real-time messages
		if ((byte > 0xf0) && (byte <= 0xff)) return;

		// This is a status byte, so start a new MIDI command
		if (byte & 0x80) {
			// If this command is not on our channel, then skip it
			// (hard coded to 1 for now, will make an option later)
			if ((byte & 0x0f) == 0) {
				midiCmd = byte;
				resetCommand();
			}
			else {
				// Set to no-message pending state
				init();
			}
		}
		else if ((midiCmd > -1) && (midiData1 == -1)) {
			midiData1 = byte;
		}
		else if ((midiCmd > -1) && (midiData2 == -1)) {
			midiData2 = byte;
		}
		
		// If a status byte is set, see if it's a complete command
		if (midiCmd >= 0x80)
			handleMidiCommand();
	}

	/**
	 * If a status byte of some kind has been sent make sure there are enough data bytes for it.
	 * If there are indeed enough data bytes, call the handler function
	 */
	inline static
	void handleMidiCommand() {
		// Two byte commands
		if (midiData2 >= 0) {
			if (isCommandByte(noteOn))
				handleNoteOn();
			else if (isCommandByte(pitchbend))
				handlePitchBend();
			else if (isCommandByte(ctrlChange))
				handleControlChange();
			else if (isCommandByte(noteOff))
				handleNoteOff();
				
			// Ignoring aftertouch commands for now 
			resetCommand();
		}
		// One byte commands
		else if (midiData1 >= 0) {
			if (isCommandByte(prgmChange)) {
				handleProgramChange();
				resetCommand();
			}
			// Ignore aftertouch
			else if (isCommandByte(afterTouch))
				resetCommand(); 
		}
		// No data commands
		else {
			// Ignore Sysex and real-time messages
			if (midiCmd >= 0xf0)
				resetCommand();
		}
	}	
	
	
	/**
	 * If the passed-in byte the command type of
	 */
	inline static
	bool isCommandByte(int command) {
		return ((midiCmd & 0xf0) == command);
	}
	
	/**
	 * Clear the current midi command
	 */
	static inline
	void resetCommand() {
		midiData1 = -1;
		midiData2 = -1;
	}
	
	// Handle MIDI events
	static void handleNoteOff();
	static void handleNoteOn();
	static void handlePitchBend();
	static void handleControlChange();
	static void handleProgramChange();
};



#endif /*MIDIINPUT_H_*/
