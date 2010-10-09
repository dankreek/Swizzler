/*
 * PitchbendFreqFilter.h
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#ifndef PITCHBENDFREQFILTER_H_
#define PITCHBENDFREQFILTER_H_

#include "AFreqOffsetReceiver.h"
#include "AFreqOffsetTransmitter.h"
#include "AFreqFilterChainMember.h"

class PitchbendFreqFilter : public AFreqOffsetReceiver, public AFreqOffsetTransmitter, public AFreqFilterChainMember {
public:
  void recvOffset(int16_t);
  void updateOffset();
private:
  int16_t lastOffset;
};

#endif /* PITCHBENDFREQFILTER_H_ */
