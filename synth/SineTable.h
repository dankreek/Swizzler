/*
 * SineTable.h
 *
 *  Created on: Oct 2, 2010
 *      Author: justin
 */

#ifndef SINETABLE_H_
#define SINETABLE_H_

#include <inttypes.h>

class SineTable {
public:
  /**
   * Get the value of the sine wave at the index of div (0-sineWavetableLength)
   */
  static int16_t getSine(uint16_t div);

  static const uint8_t sineTableDivisions = 32;
  static const uint8_t sineTableLength = sineTableDivisions+1;  // Length of the 1/4 sine wave
  static const uint8_t sineWavetableLength = 128;               // Length of the entire derived sine table, (sineTableLength-1)*4

  static uint8_t sineTable[sineTableLength];
};

#endif /* SINETABLE_H_ */
