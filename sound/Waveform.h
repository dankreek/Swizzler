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

  /**
   * This waveform type
   */
  WaveformType curWaveType;

  /**
   * Get the sample which lies at the provided index for the currently selected waveform
   */
  inline int8_t getSample(uint16_t i) {
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
        return noiseOut;
        break;
    }

    return 0;
  }

  uint16_t pulseWidth;

  // Fill the noise table with a bunch random noise
  static void initNoiseGenerator();

  static inline
  void pollNoiseGenerator() {
    int16_t temp;

    temp=noise;
    noise <<= 1;

    temp ^= noise;
    if ((temp & 0x4000) == 0x4000) noise |= 1;
    noiseOut = noise >> 6;
  }

private:
  static int8_t noiseOut;
  static uint16_t noise;
};

#endif /* WAVEFORM_H_ */
