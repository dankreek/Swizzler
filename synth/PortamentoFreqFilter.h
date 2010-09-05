/*
 * PortamentoFreqFilter.h
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#ifndef PORTAMENTOFREQFILTER_H_
#define PORTAMENTOFREQFILTER_H_

#include "AFreqTransmitter.h"
#include "AFreqFilterChainMember.h"
#include "LinearIncrementor.h"

class PortamentoFreqFilter : public AFreqTransmitter, public AFreqFilterChainMember {
public:
  PortamentoFreqFilter();
  void updateFreq();

  // Reset the Portamento generator to its initial state
  void reset();

  // This should be called every  millisecond to update the current portamento state
  void nextTick();

private:
  void startNewGlide();

  uint16_t      curFrequency;

  // Source and destination portamento note numbers. These are used to tell when a new note has been struck
  // and how fast to change frequencies
  int8_t        destPortNote;
  int8_t        srcPortNote;

  LinearIncrementor     freqAccum;      // Frequency accumulator
  static const uint8_t  freqAccumResolution = 14;
};

#endif /* PORTAMENTOFREQFILTER_H_ */
