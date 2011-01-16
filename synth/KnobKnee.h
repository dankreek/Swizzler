#ifndef KNOBKNEE_H
#define KNOBKNEE_H

#include <inttypes.h>

/**
 * This class essentially converts an integer from 0 to 127 (MIDI controller
 * range) into an integer ranging from 0 to the maxValue specified in init.
 *
 * This uses a simple piecewise linear function made up of lines connecting the points
 * (0,0) -> (x1, y1) -> (x2, y2) ->(127, maxRange)
 *

 */
class KnobKnee {
public:
  /**
   * @maxValue The range knob's (from 0-range, inclusive)*
   */
  KnobKnee(uint8_t x1, uint16_t y1, uint8_t x2, uint16_t y2, uint16_t maxValue);

  /**
   * Get the output value based up a MIDI controller value
   */
  uint16_t getValue(uint8_t midiValue);

private:
  // The output range
  uint16_t maxValue;

  // The knee points
  uint8_t x1,x2;
  uint16_t y1,y2;
};


#endif
