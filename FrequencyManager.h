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
	void begin();

	/**
	 * This is called once every millisecond to handle all the business
	 */
	static
	void nextTick();

	/**
	 * Signal the a note has been hit
	 * @noteNumber	MIDI note number that has been hit
	 */
	static
	void noteOn(uint8_t noteNumber);

	/**
	 * Tell the frequency manager that a note has been let off
	 */
	static
	void noteOff(uint8_t noteNumber);

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
	static void copyNoteBufferToArpBuffer();
	static bool portamentoOn;
};

#endif
