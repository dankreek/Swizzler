#ifndef FREQMAN_H
#define FREQMAN_H

#include "PortamentoManager.h"

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
	static
	void init();

	/**
	 * The note manager is sending a new note
	 */
	static
	void newNote(uint8_t noteNumber);

	/**
	 * This is called once every millisecond to handle all the business
	 */
	static
	void nextTick();

	/**
	 * Turn on/off portamento
	 * @onOff true to turn on portamento, false to turn off portamento
	 */
	static
	void enablePortamento(bool onOff);

	/**
	 * Convert a Midi note to a frequency
	 */
	static
	int noteToFreq(uint8_t noteNum);

  private:
	static bool portamentoOn;
};

#endif
