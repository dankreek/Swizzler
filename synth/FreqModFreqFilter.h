/*
 * FreqModFreqFilter.h
 *
 *  Created on: Oct 3, 2010
 *      Author: justin
 */

#ifndef FREQMODFREQFILTER_H_
#define FREQMODFREQFILTER_H_

#include "AFreqReceiver.h"
#include "AFreqTransmitter.h"
#include "AFreqFilterChainMember.h"
#include "ITimerCall.h"

class FreqModFreqFilter : public AFreqReceiver, public AFreqTransmitter, public AFreqFilterChainMember {
public:
  FreqModFreqFilter();

  void recvFreq(uint16_t freq);
  void updateFreq();

private:
  // Most recently received frequency
  uint16_t curFreq;
};

#endif /* FREQMODFREQFILTER_H_ */
