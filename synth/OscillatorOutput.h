/*
 * OscillatorOutput.h
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#ifndef OSCILLATOROUTPUT_H_
#define OSCILLATOROUTPUT_H_

#include "AFreqReceiver.h"

class OscillatorOutput : public AFreqReceiver {
public:
  OscillatorOutput();
  void recvFreq(uint16_t freq);
};

#endif /* OSCILLATOROUTPUT_H_ */