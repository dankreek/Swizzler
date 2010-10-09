/*
 * AFreqTransmitter.h
 *
 *  Created on: Aug 28, 2010
 *      Author: justin
 */

#ifndef AFREQTRANSMITTER_H_
#define AFREQTRANSMITTER_H_

#include <inttypes.h>
#include "AFreqOffsetReceiver.h"

class AFreqOffsetTransmitter {
public:
  void linkTo(AFreqOffsetReceiver *recv);
  void sendSchlipOffset(int16_t schlipOffset);

  // Force a send recalculation and send of the cur frequency to the next in the chain
  // TODO : I really don't think this is needed... think up a better strategy
  virtual void updateOffset() = 0;
private:
  AFreqOffsetReceiver *receiver;
};

inline
void AFreqOffsetTransmitter::linkTo(AFreqOffsetReceiver *output) {
  receiver = output;
}

inline
void AFreqOffsetTransmitter::sendSchlipOffset(int16_t offset) {
  receiver->recvOffset(offset);
}

#endif /* AFREQTRANSMITTER_H_ */
