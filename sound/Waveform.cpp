/*
 * Waveform.cpp
 *
 *  Created on: Jul 10, 2010
 *      Author: justin
 */

#include "Waveform.h"
#include <stdlib.h>

uint16_t Waveform::noiseOut;
uint16_t Waveform::noise;

Waveform::Waveform() {
  curWaveType = triangleWave;
  pulseWidth = 0x8000;
}

void Waveform::initNoiseGenerator() {
  noise = 0xaa;
}

void Waveform::pollNoiseGenerator() {
  int16_t temp;

  temp=noise;
  noise <<= 1;

  temp ^= noise;
  if ((temp & 0x4000) == 0x4000) noise |= 1;
  noiseOut = noise >> 6;
}
