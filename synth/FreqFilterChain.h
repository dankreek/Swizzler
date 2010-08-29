/*
 * FreqFilterChain.h
 *
 *  Created on: Aug 28, 2010
 *      Author: justin
 */

#ifndef FREQFILTERCHAIN_H_
#define FREQFILTERCHAIN_H_

#include "DirectNoteFreqFilter.h"
#include "ANoteReceiver.h"
#include "OscillatorOutput.h"
#include "DirectNoteFreqFilter.h"
#include "PitchbendFreqFilter.h"

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

  // Keeps track of the current and previous note numbers that have entered the filter chain
  int8_t prevNoteNum;
  int8_t curNoteNum;

private:
  int8_t noteOffset;

  // Pointer to the first frequency filter in the chain
  AFreqTransmitter *chainHead;

  // These are all the filters in the chain
  OscillatorOutput oscOut;
  PitchbendFreqFilter pitchbendFilter;          // Calculated pitch bends
  DirectNoteFreqFilter directNoteFilter;        // Directly converts a note to a frequency
};

#endif /* FREQFILTERCHAIN_H_ */
