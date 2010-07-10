#ifndef WAVEGEN_INT_H
#define WAVEGEN_INT_H

#define WAVEOUT_PIN 11

#include <inttypes.h>

#define SAMPLE_RATE     8000

class Waveout {
public:
  static void start();
  static void stop();

  /**
   * Set the timer interval so that the sound it
   * output at the correct sample rate to create the input frequency
   *
   * There is a minimum and maximum frequency. I'll figure them out later.
   */
  static void setFreq(uint16_t);

  static uint16_t       rootAccumulator;
  static uint16_t       rootIncrementor;

  inline static
  void incAccumulator() {
    rootAccumulator += rootIncrementor;
  }
};

#endif
