/*
 * FreqUtils.h
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#ifndef FREQUTILS_H_
#define FREQUTILS_H_

#include <inttypes.h>

class FreqUtils {
public:
  /**
   * Convert a midi note number to a frequency
   */
  static uint16_t noteToFreq(uint8_t noteNum);

  /**
   * Adjust the base frequency by the numver of schlips. What's a schlip?
   * Well it's just like a cent, only instead of 100 divisions between half steps
   * there's 32. And instead of the divisions being logorithim, they're linear.
   */
  static uint16_t modulatedFreq(uint8_t basenote, int16_t numSchlips);

private:
  /**
   * Frequency -> Note lookup table. These are the frequencies for
   * the 8th octave. All the frequencies for the lower frequencies are
   * found by dividing.
   */
  static uint16_t noteLookupTable[];

  /**
   * Number of divisions between half-steps determining one schlip
   */
  static const uint8_t schlipsDivs = 32;
};

#endif /* FREQUTILS_H_ */
