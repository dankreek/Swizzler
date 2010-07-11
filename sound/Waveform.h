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

  /**
   * Set this instance's waveform type
   */
  inline void setWaveform(WaveformType wt) {
    switch (wt) {
      case triangleWave:
        curWave = triangleBuffer;
        break;
      case squareWave:
        curWave = squareBuffer;
        break;
      case sawtoothWave:
        curWave = sawtoothBuffer;
        break;
      case noiseWave:
        curWave = NULL;
        break;
    }

    curWaveType = wt;
  }

  /**
   * Get the sample which lies at the provided index for the currently selected waveform
   */
  inline void getSample(uint8_t i) {
    if (curWaveType == noiseWave) {
      // TODO : Need to generate noise!
    }
    else
      return curWave[i];
  }

private:
  // Pointer to this instance's current wavetable
  int8_t *curWave;

  // Current waveform type
  WaveformType curWaveType;

  // Generate the wave forms in memory
  static void generateTriangleWave();
  static void generateSawtoothWave();

  static uint8_t pulseWidth;
};

#endif /* WAVEFORM_H_ */
