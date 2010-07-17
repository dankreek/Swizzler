/*
 * Waveform.h
 *
 *  Created on: Jul 10, 2010
 *      Author: justin
 */

#ifndef WAVEFORM_H_
#define WAVEFORM_H_

#include <inttypes.h>

enum WaveformType {
  triangleWave,
  squareWave,
  sawtoothWave,
  noiseWave
};

class Waveform {
public:
  Waveform();

  // Length of a wavetable
  static const uint8_t waveformLength = 128;

  // Buffers which contain wavetables
  static int8_t triangleBuffer[waveformLength];
  static int8_t squareBuffer[waveformLength];
  static int8_t sawtoothBuffer[waveformLength];

  /**
   * Set the pulse width of the pulse wave
   */
  void setPulseWidth(uint16_t pw);

  /**
   * This waveform type
   */
  WaveformType curWaveType;

  /**
   * Get the sample which lies at the provided index for the currently selected waveform
   */
  inline int8_t getSample(uint16_t i) {
    // All triangle all the time
    switch (curWaveType) {
    case sawtoothWave:
      return (i >> 8)-128;
      break;
    case triangleWave:
      i >>= 7;
      return ((i <= 255) ? i : 511-i)-128;
      break;
    case squareWave:
      return (i < pulseWidth) ? -64 : 64;
      break;
    case noiseWave:
      return noiseWaveTable[i>>8];
      break;
    }

    return 0;
  }

  uint16_t pulseWidth;

  static int8_t noiseWaveTable[waveformLength];
};

#endif /* WAVEFORM_H_ */
