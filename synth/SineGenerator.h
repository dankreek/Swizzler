/*
 * SineGenerator.h
 *
 *  Created on: Oct 3, 2010
 *      Author: justin
 */

#ifndef SINEGENERATOR_H_
#define SINEGENERATOR_H_

#include <inttypes.h>
#include "ITimerCall.h"
#include "SineTable.h"

class SineGenerator : public ITimerCall  {
public:
  SineGenerator();

  // Note that this is for LFO generator that can generate from 0-32hz.
  // But to maintain more grandularity this function accepts (actual freq)<<3
  // as the frequency (a seven bit number that gets shifted to a 4 bit number)
  // TODO: Figure out how the hell to implement this
  void setFrequency(uint16_t freq);

  void nextTick();

  // Get the current sine value
  int16_t getCurValue();

private:
  SineTable sineTable;
  uint16_t incAmount;
  uint16_t idxAccum;
};

#endif /* SINEGENERATOR_H_ */
