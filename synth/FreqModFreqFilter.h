/*
 * FreqModFreqFilter.h
 *
 *  Created on: Oct 3, 2010
 *      Author: justin
 */

#ifndef FREQMODFREQFILTER_H_
#define FREQMODFREQFILTER_H_

#include "AFreqOffsetReceiver.h"
#include "AFreqOffsetTransmitter.h"
#include "AFreqFilterChainMember.h"
#include "ITimerCall.h"

class FreqModFreqFilter : public AFreqOffsetReceiver, public AFreqOffsetTransmitter, public AFreqFilterChainMember {
public:
  FreqModFreqFilter();

  void recvOffset(int16_t offset);
  void updateOffset();

private:
  // Most recently received frequency
  int16_t curOffset;
};

#endif /* FREQMODFREQFILTER_H_ */
