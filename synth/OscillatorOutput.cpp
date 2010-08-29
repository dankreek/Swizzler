/*
 * OscillatorOutput.cpp
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#include "Swizzler.h"
#include "OscillatorOutput.h"

OscillatorOutput::OscillatorOutput() {
}

void OscillatorOutput::recvFreq(uint16_t freq) {
  Swizzler::soundChip.setFrequency(freqChainContainer->voiceNumber, freq);
}
