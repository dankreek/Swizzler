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
  sawtoothWave,
  reverseSawtoothWave,
  squareWave,
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
   * (Index ranges from 0-0xfff)
   */
  int8_t getSample(uint16_t i);

  // The pulse width of this voice's square wave (0-0xffff)
  uint16_t pulseWidth;

  static void initNoiseGenerator();

  /**
   * The static generator needs to be called consistently during
   * execution to keep things random
   */
  static void pollNoiseGenerator();

private:
  static int8_t noiseOut;
  static uint16_t noise;
};

inline int8_t Waveform::getSample(uint16_t i) {
  switch (curWaveType) {
    case sawtoothWave:
      return (i >> 8)-128;
    case reverseSawtoothWave:
      return 255-(i >> 8)-128;
    case triangleWave:
      i >>= 7;
      return (i <= 255) ? (i-128) : (511-i-128);
    case squareWave:
      return (i < pulseWidth) ? -64 : 64;
    case noiseWave:
      return noiseOut;

  }

  return 0;
}

inline void Waveform::pollNoiseGenerator() {
  int16_t oldNoise;

  oldNoise=noise;
  noise <<= 1;

  oldNoise ^= noise;
  if ((oldNoise & 0x4000) == 0x4000) noise |= 1;
  noiseOut = noise >> 6;
}

#endif /* WAVEFORM_H_ */
