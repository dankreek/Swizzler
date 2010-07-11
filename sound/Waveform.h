/*
 * Waveform.h
 *
 *  Created on: Jul 10, 2010
 *      Author: justin
 */

#ifndef WAVEFORM_H_
#define WAVEFORM_H_

enum WaveformType {
  triangleWave,
  squareWave,
  sawtoothWave,
  noiseWave
};

class Waveform {
public:
  // Generate the specified wave form
  static void generateWaveforms();

  // Length of a wavetable
  // TODO : Make this smaller! Need to fit more waves in memory at one time
  static const uint8_t waveformLength = 256;

  // Buffers which contain wavetables
  static int8_t triangleBuffer[waveformLength];
  static int8_t squareBuffer[waveformLength];
  static int8_t pulseBuffer[waveformLength];
  static int8_t sawtoothBuffer[waveformLength];

  // Pointer to the current wavetable
  int8_t *curWavetable;
};

#endif /* WAVEFORM_H_ */
