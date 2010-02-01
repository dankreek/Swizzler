#ifndef MIDIKNEE_H
#define MIDIKNEE_H

#include <inttypes.h>

/**
 * This class essentially converts an integer from 0 to 127 (MIDI contrller
 * range) into an integer ranging from 0 to the range specified in init. 
 * The (kneeX, kneeY) point defines a point where the knee of the input 
 * scaler changes.
 */
class KnobKnee {
  public:
	inline
	KnobKnee(uint16_t range, uint8_t kneeX, uint16_t kneeY) {
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
