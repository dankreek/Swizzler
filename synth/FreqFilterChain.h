/*
 * FreqFilterChain.h
 *
 *  Created on: Aug 28, 2010
 *      Author: justin
 *
 */

#ifndef FREQFILTERCHAIN_H_
#define FREQFILTERCHAIN_H_

#include "ANoteReceiver.h"
#include "ANoteTransmitter.h"
#include "OscillatorOutput.h"
#include "PitchbendFreqFilter.h"
#include "PortamentoFreqFilter.h"
#include "ITimerCall.h"
#include "FreqModFreqFilter.h"
#include "OutputFreqFilter.h"

class FreqFilterChain : public ANoteReceiver, public ANoteTransmitter, public ITimerCall {
public:
  FreqFilterChain();

  void noteOn(uint8_t, uint8_t);
  void noteOff(uint8_t);

  // Recalculate resulting frequency
  void updateFrequency();

  // Keeps track of the current and previous note numbers that have entered the filter chain
  int8_t prevNoteNum;
  int8_t curNoteNum;

  // Service all timer functions of each filter
  void nextTick();

  // Turn portamento on/off
  void setPortamento(bool onOff);

  // Turn frequency modulation on/off
  void setFrequencyModulation(bool onOff);

  // Get the current frequency offset (in schlips)
  int16_t getFreqOffset();
private:
  int8_t noteOffset;

  // Pointer to the first frequency filter in the chain
  AFreqOffsetTransmitter *chainHead;

  // These are all the filters in the chain
  PitchbendFreqFilter pitchbendFilter;          // Calculated pitch bends
  PortamentoFreqFilter portamentoFilter;
  FreqModFreqFilter freqModFilter;              // Frequency modulation filter
  OutputFreqFilter outputFilter;
};

inline
int16_t FreqFilterChain::getFreqOffset() {
  return outputFilter.curOffset;
}

#endif /* FREQFILTERCHAIN_H_ */
