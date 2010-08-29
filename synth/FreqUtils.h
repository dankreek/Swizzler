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
  static uint16_t noteToFreq(uint8_t noteNum);

private:
  /**
   * Frequency -> Note lookup table. These are the frequencies for
   * the 8th octave. All the frequencies for the lower frequencies are
   * found by dividing.
   */
  static uint16_t noteLookupTable[];
};

#endif /* FREQUTILS_H_ */
