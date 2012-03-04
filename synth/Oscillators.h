/** @file Oscillators.h
 *  @date Aug 28, 2010
 */

#ifndef OSCILLATORS_H_
#define OSCILLATORS_H_

#include "ANoteReceiver.h"
#include "FreqFilterChain.h"
#include "ITimerCall.h"

/**
 * This class takes the root note that's been played on the keyboard and
 * sends it to each of the 3 oscillator's frequency filters.
 *
 * @author Justin May <may.justin@gmail.com>
 */
class Oscillators : public ANoteReceiver {
public:
	/// Initialize this class
	Oscillators();

	/**
	 * Receive a note on command from the MIDI note filter chain, then output
	 * the correct frequencies to each oscillator.
	 *
	 * @param noteNum	The MIDI note number received from the keyboard
	 * @param velocity	The velocity that the note was struck at
	 */
	void noteOn(uint8_t noteNum, uint8_t velocity);


	/// No action needed on a note off command
	void noteOff(uint8_t noteNum);

	/**
	 * Set an oscillator's note offset
	 *
	 * @param oscNum	Oscillator number to set note offset for
	 * @param offset	Number of half-steps (+ or -) to offset the oscillator's frequency by
	 */
	void setNoteOffset(uint8_t oscNum, int8_t offset);

	/**
	 * Send out the current frequency to each oscillator on the sound chip.
	 */
	void update();

	/// The number of voices with frequency (voice 4 is only white noise)
	static const uint8_t VCO_COUNT = 3;

private:
	/// The note that was last sent by the MIDI note filter chain
	uint8_t _curRootNote;

//  FreqFilterChain oscillatorList[numVoices];

	/// Note offset (in half-steps) for each oscillator
	int8_t _noteOffset[VCO_COUNT];

	/// Keep track of the last frequency output so no redundant frequency update is sent to the sound chip
	uint16_t _lastFreq[VCO_COUNT];

	/**
	 * Calculate the frequency and send it out to the sound chip. The frequency
	 * is only sent if the frequency is different than the last one sent.
	 *
	 * @param voiceNum	Oscillator number to attempt to send the frequency to
	 */
	void _outputFrequency(uint8_t voiceNum);
};

#endif /* OSCILLATORS_H_ */
