#ifndef MIDIKNEE_H
#define MIDIKNEE_H

#include <inttypes.h>

/**
 * This class essentially converts an integer from 0 to 127 (MIDI controller
 * range) into an integer ranging from 0 to the range specified in init. 
 * The (kneeX, kneeY) point defines a point where the knee of the input 
 * scaler changes.
 */
class KnobKnee {
  public:
	/**
	 * @range The range knob's (from 0-range, inclusive)
	 * (@kneeX, @kneeY) Where the "knee" is, think of it as a graph where
     *      			the X axis goes from 0-127 and the Y axis goes from 0-range.
     * 				    The output Y value is determined by two lines. The first line goes from (0,0) to
     *                  (kneeX, KneeY), then next line goes from (kneeX, kneeY) to (127,range).
     *       			Different types of controls feel more natural with different knees.
	 */
	inline KnobKnee(uint16_t range, uint8_t kneeX, uint16_t kneeY) {
		this->range = range;
		this->kneeX = kneeX;
		this->kneeY = kneeY;
	}

	/**
	 * Get the output value based up a MIDI controller value
	 */
	uint16_t getValue(uint8_t midiValue);
  private:
	// The output range
	uint16_t range;

	// The knee point
	uint8_t kneeX;
	uint16_t kneeY;
};

#endif