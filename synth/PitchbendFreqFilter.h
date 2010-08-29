/*
 * PitchbendFreqFilter.h
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#ifndef PITCHBENDFREQFILTER_H_
#define PITCHBENDFREQFILTER_H_

#include "AFreqReceiver.h"
#include "AFreqTransmitter.h"
#include "AFreqFilterChainMember.h"

class PitchbendFreqFilter : public AFreqReceiver, public AFreqTransmitter, public AFreqFilterChainMember {
public:
  PitchbendFreqFilter();

  void recvFreq(uint16_t);
  void updateFreq();

private:
  int16_t getBendOffset();
};

#endif /* PITCHBENDFREQFILTER_H_ */
