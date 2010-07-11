/*
 * Voice.cpp
 *
 *  Created on: Jul 10, 2010
 *      Author: justin
 */

#include "Voice.h"
#include "PwmOut.h"

void Voice::init() {
  envelope.init();
  waveform.setWaveform(triangleWave);
  phaseAccumulator = 0;
}

void Voice::setFrequency(uint16_t freq) {
  phaseChangeRate = (freq*0x10000)/PwmOut::sampleRate;
}

