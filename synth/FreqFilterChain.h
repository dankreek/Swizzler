/*
 * FreqFilterChain.h
 *
 *  Created on: Aug 28, 2010
 *      Author: justin
 */

#ifndef FREQFILTERCHAIN_H_
#define FREQFILTERCHAIN_H_

#include "ANoteReceiver.h"
#include "OscillatorOutput.h"

class FreqFilterChain : public ANoteReceiver {
public:
  FreqFilterChain();
  void noteOn(uint8_t noteNum, uint8_t velocity);
  void noteOff(uint8_t noteNum);

  void setNoteOffset(int8_t ofs);
private:
  int8_t noteOffset;
  int8_t prevNoteNum;
  int8_t curNoteNum;

  // These are all the filters in the chain
  OscillatorOutput oscOut;
};

#endif /* FREQFILTERCHAIN_H_ */
