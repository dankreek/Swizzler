/*
 * Waveform.cpp
 *
 *  Created on: Jul 10, 2010
 *      Author: justin
 */

#include "Waveform.h"
#include <stdlib.h>

int8_t Waveform::noiseOut;
uint16_t Waveform::noise;

void Waveform::init() {
  curWaveType = squareWave;
  pulseWidth = 0x8000;
}

void Waveform::initNoiseGenerator() {
  noise = 0xaa;
}
