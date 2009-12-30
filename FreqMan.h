#ifndef FREQMAN_H
#define FREQMAN_H

/**
 * The frequency manager takes in control messages (via MIDI) like note on, note off
 * portamento on/off, and arpeggio on/off, and tells the oscillator what frequency to
 * put out at.
 */
class FreqMan {
  public:

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
	void noteOn(int noteNumber);

	/**
	 * Tell the frequency manager that a note has been let off
	 */
	static
	void noteOff(int noteNumber);

	/**
	 * Turn on/off portamento
	 * @onOff true to turn on portamento, false to turn off portamento
	 */
	static
	void enablePortamento(bool onOff);

	/**
	 * Turn on/off the arp'er
	 * @onOff true to turn on arpeggiator, false to turn it off
	 */
	static
	void enableArp(bool onOff);

	/**
	 * Convert a Midi note to a frequency
	 */
	static
	int noteToFreq(int noteNum);

  private:

	static
	bool portamentOn;

	static
	bool arpeggioOn; 

};

#endif
