/*
 * AFreqTransmitter.h
 *
 *  Created on: Aug 28, 2010
 *      Author: justin
 */

#ifndef AFREQTRANSMITTER_H_
#define AFREQTRANSMITTER_H_

#include <inttypes.h>
#include "AFreqReceiver.h"

class AFreqTransmitter {
public:
  void linkTo(AFreqReceiver *recv);
  void sendFreq(uint16_t freq);

  // Force a send recalculation and send of the cur frequency to the next in the chain
  virtual void updateFreq() = 0;
private:
  AFreqReceiver *receiver;
};

inline
void AFreqTransmitter::linkTo(AFreqReceiver *output) {
  receiver = output;
}

inline
void AFreqTransmitter::sendFreq(uint16_t freq) {
  receiver->recvFreq(freq);
}

#endif /* AFREQTRANSMITTER_H_ */
