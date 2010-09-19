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
#include "ITimerCall.h"
#include "Bresenham.h"

class PortamentoFreqFilter : public AFreqTransmitter, public AFreqFilterChainMember, public ITimerCall {
public:
  PortamentoFreqFilter();
  void updateFreq();

  // Reset the Portamento generator to its initial state
  void reset();

  // This should be called every  millisecond to update the current portamento state
  void nextTick();

private:
  // Has a new note been struck since the last frequency update
  bool isNewNoteStruck();

  // Has a note previously been struck yet
  bool hasPrevNoteBeenStruck();

  void startNewGlide();

  uint16_t      curFrequency;

  // Source and destination portamento note numbers. These are used to tell when a new note has been struck
  // and how fast to change frequencies
  int8_t        destPortNote;
  int8_t        srcPortNote;

  //LinearIncrementor     freqAccum;      // Frequency accumulator
  Bresenham             lineCalc;       // Linear function calculator
  static const uint8_t  freqAccumResolution = 13;
};


#endif /* PORTAMENTOFREQFILTER_H_ */
