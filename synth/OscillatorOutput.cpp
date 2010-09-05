/*
 * OscillatorOutput.cpp
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#include "Swizzler.h"
#include "OscillatorOutput.h"

OscillatorOutput::OscillatorOutput() {
  lastFreq = 0;
}

void OscillatorOutput::recvFreq(uint16_t freq) {
  if (freq != lastFreq) {
    Swizzler::soundChip.setFrequency(freqChainContainer->voiceNumber, freq);
    lastFreq = freq;
  }


}
