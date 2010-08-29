/*
 * OscillatorOutput.h
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#ifndef OSCILLATOROUTPUT_H_
#define OSCILLATOROUTPUT_H_

#include "FreqFilterChain.h"
#include "AFreqReceiver.h"
#include "AFreqFilterChainMember.h"

class OscillatorOutput : public AFreqReceiver, public AFreqFilterChainMember {
public:
  OscillatorOutput();
  void recvFreq(uint16_t freq);

};

#endif /* OSCILLATOROUTPUT_H_ */
