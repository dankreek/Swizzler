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

  // Generate the wavetables
  static void init();

  // Length of a wavetable
  static const uint8_t waveformLength = 128;

  // Buffers which contain wavetables
  static int8_t triangleBuffer[waveformLength];
  static int8_t squareBuffer[waveformLength];
  static int8_t sawtoothBuffer[waveformLength];

  /**
   * Set (and redraw) the pulse width of the pulse wave (7 bits are significant)
   */
  static void setPulseWidth(uint8_t pw);

private:
  // Pointer to this instance's current wavetable
  int8_t *curWave;

  // Generate the wave forms in memory
  static void generateTriangleWave();
  static void generateSawtoothWave();

  static uint8_t pulseWidth;
};

#endif /* WAVEFORM_H_ */
