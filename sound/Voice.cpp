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
  phaseAccumulator = 0;
  isFiltered=false;
  outputVolume=0xff;
}

void Voice::setFrequency(uint16_t freq) {
  phaseChangeRate = (freq*0x10000)/PwmOut::sampleRate;
}

