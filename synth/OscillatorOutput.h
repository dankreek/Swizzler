/*
 * OscillatorOutput.h
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#ifndef OSCILLATOROUTPUT_H_
#define OSCILLATOROUTPUT_H_

#include "AFreqFilterChainMember.h"
#include "AFreqOffsetReceiver.h"

class OscillatorOutput : public AFreqFilterChainMember, public AFreqOffsetReceiver {
public:
  OscillatorOutput();
  void recvOffset(int16_t offset);

private:
  // The last frequency that was output, this is used to make sure no unnecessary
  // messages are sent over the wire to the sound chip
  uint16_t      lastFreq;
};

#endif /* OSCILLATOROUTPUT_H_ */
