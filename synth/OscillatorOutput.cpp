/*
 * OscillatorOutput.cpp
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#include "Swizzler.h"
#include "OscillatorOutput.h"
#include "FreqUtils.h"

OscillatorOutput::OscillatorOutput() {
  lastFreq = 0;
}

void OscillatorOutput::recvOffset(int16_t offset) {
  uint16_t freq = FreqUtils::modulatedFreq(freqChainContainer->curNoteNum, offset);

  if (freq != lastFreq) {
//    Swizzler::soundChip.setFrequency(freqChainContainer->voiceNumber, freq);

    lastFreq = freq;
  }
}
