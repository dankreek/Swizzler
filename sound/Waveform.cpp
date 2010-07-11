/*
 * Waveform.cpp
 *
 *  Created on: Jul 10, 2010
 *      Author: justin
 */

#include "Waveform.h"

uint8_t Waveform::pulseWidth;
int8_t Waveform::triangleBuffer[waveformLength];
int8_t Waveform::squareBuffer[waveformLength];
int8_t Waveform::sawtoothBuffer[waveformLength];

Waveform::Waveform() {
  // Make triangle the default waveform
  curWave = triangleBuffer;
}

void Waveform::init() {
  // Set pulse width to 50% (and redraw waveform)
  setPulseWidth(64);
  generateSawtoothWave();
  generateTriangleWave();
}

void Waveform::generateSawtoothWave() {
  int8_t val = -128;
  for (int i=0; i < waveformLength; i++) {
    sawtoothBuffer[i] = val;
    val += (256/waveformLength);
  }
}

void Waveform::setPulseWidth(uint8_t pw) {
  pulseWidth = pw;
  for (int i=0; i < waveformLength; i++) {
    squareBuffer[i] = (i < pulseWidth) ? -128 : 127;
  }
}

void Waveform::generateTriangleWave() {
  int8_t val=-128;
  uint8_t i;

  for (i=0; i < waveformLength/2; i++) {
    triangleBuffer[i] = val;
    val += (256*2)/waveformLength;
  }

  for (; i < waveformLength; i++) {
    triangleBuffer[i] = val;
    val -= (256*2)/waveformLength;
  }
}
