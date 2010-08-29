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
#include "DirectNoteFreqFilter.h"

class FreqFilterChain : public ANoteReceiver {
public:
  FreqFilterChain();
  void noteOn(uint8_t noteNum, uint8_t velocity);
  void noteOff(uint8_t noteNum);

  void setNoteOffset(int8_t ofs);

  // Recalculate resulting frequency
  void updateFrequency();

  // This filter chain's voice number
  uint8_t voiceNumber;
private:
  int8_t noteOffset;
  int8_t prevNoteNum;
  int8_t curNoteNum;

  // Pointer to the first note receiver in the chain
  ANoteReceiver *chainNoteReciver;

  // These are all the filters in the chain
  OscillatorOutput oscOut;
  DirectNoteFreqFilter directNoteFilter;        // Directly converts a note to a frequency
};

#endif /* FREQFILTERCHAIN_H_ */
