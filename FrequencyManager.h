#ifndef FREQMAN_H
#define FREQMAN_H

#include "PortamentoManager.h"
#include "Swizzler.h"

/**
 * The frequency manager takes in control messages (via MIDI) like note on, note off
 * portamento on/off, and arpeggio on/off and tells the oscillator what frequency to
 * put out at.
 */
class FrequencyManager {
  public:
	static PortamentoManager portMan;

	/**
	 * Initialize the frequency manager
	 */
	static void init();

	/**
	 * The note manager is sending a new note
	 */
	static void newNote(uint8_t noteNumber);

	/**
	 * This is called once every millisecond to handle all the business.
	 * Currently only the portamento manager needs a timer hook.
	 */
	static inline void nextTick() {
		// If portamento's on and running then output a new frequency
		if (portamentoOn && !portMan.done) {
			// only change frequency if it's necessary
			if (portMan.nextTick()) Waveout::setFreq(portMan.curFreq);
		}
	}

	/**
	 * Set a new bend value 0 is max bend low, 64 is no bend, 127 is max high bend
	 */
	static void setBendAmount(uint8_t ba);

	/**
	 * Turn on/off portamento
	 * @onOff true to turn on portamento, false to turn off portamento
	 */
	static void enablePortamento(bool onOff);

	/**
	 * Convert a Midi note to a frequency
	 */
	static uint16_t noteToFreq(uint8_t noteNum);

	// The range that the pitch bend swings between (in +/- half-steps)
	static uint8_t bendRange;

  private:
	// Is portamento currently on?
	static bool portamentoOn;

	// Current bend amount, this is an unsigned 7bit number (-64,63)
	static uint8_t bendAmount;

	// Use the bendAmount and the current note number to recalculate the bendOffset
	static void recalculateBendOffset();

	// How much to increment (or decrement) the output frequency (in hz) as set by recalculateBendOffset()
	static int16_t bendOffset;

	// The last note that was sent
	static uint8_t curMidiNote;
};

#endif
