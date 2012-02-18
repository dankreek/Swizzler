/** @file KnobKnee.h
 */

#ifndef KNOBKNEE_H
#define KNOBKNEE_H

#include <inttypes.h>

/**
 * This class converts an integer from 0 to 127 (MIDI controller
 * range) into an integer ranging from 0 to the maxValue specified in init, but is scaled
 * by a linear curve defined by 4 points. This is used to turn a linear MIDI controller
 * into a psuedo-logarithmic tapered control, as well as provie easy scaling from the standard MIDI
 * controller's 0-127 range into a range more suitable for a control.
 *
 * This uses a simple piecewise linear function made up of lines connecting the points
 * (0,0) -> (x1, y1) -> (x2, y2) -> (127, maxRange)
 *
 * @author Justin May <may.justin@gmail.com>
 */
class KnobKnee {
public:
  /**
   * Create a psuedo-logarithmic MIDI control scaler.
   *
   * @param x1 X coordinate of first knee point
   * @param y1 Y coordinate of first knee point
   * @param x2 X coordinate of second knee point
   * @param y2 Y coordinate of second knee point
   * @param maxValue The max value of the knob when turned all the way up 
   */
  KnobKnee(uint8_t x1, uint16_t y1, uint8_t x2, uint16_t y2, uint16_t maxValue);

  /**
   * Get the output value based up a MIDI controller value
   *
   * @param midiValue
   * @return The scaled value of the MIDI controller input
   */
  uint16_t getValue(uint8_t midiValue);

private:
  /// The output range
  uint16_t maxValue;

  // The knee points
  uint8_t x1,x2;
  uint16_t y1,y2;
};


#endif
