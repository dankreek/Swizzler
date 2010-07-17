/*
 * Waveform.cpp
 *
 *  Created on: Jul 10, 2010
 *      Author: justin
 */

#include "Waveform.h"

int8_t Waveform::noiseWaveTable[waveformLength];

Waveform::Waveform() {
  // Make triangle the default waveform
  pulseWidth = 0x8000;
}

