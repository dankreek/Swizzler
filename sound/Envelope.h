/*
 * Envelope.h
 *
 *  Created on: Jul 10, 2010
 *      Author: justin
 */

#ifndef ENVELOPE_H_
#define ENVELOPE_H_

#include <inttypes.h>

class Envelope {
public:
  // Initialize this envelope generator
  void init();

  // Adjust envelope level every millisecond (called by main loop)
  void msTickHandler();

  // Highest sustain level the envelope generator uses
  static const int16_t maxLevel = 0x7fff;

  // Current envelope level (0=quietest, maxLevel=loudest)
  uint16_t level;

  // Attack, decay and release times
  int16_t attack, decay, release;

  // Sustain level (0- maxLevel)
  int16_t sustain;

  // Operate the gate. true=closed, false=open
  void setGate(bool isClosed);

  // Get the sample after being scaled by the envelope generator
  int8_t scaleSample(int8_t sample);

private:
  enum EnvelopeState {
      inactive,
      attackPhase,
      decayPhase,
      sustainPhase,
      releasePhase};

  // The current envelope phase
  EnvelopeState envelopeState;

  // The state of the gate. true=closed, false=opened
  bool gateState;

  // The current rate (per millisecond) at which the envelope level is changing
  // Change is incremental during attack, and decremental during decay and release
  int16_t changeRate;

  // How long (in milliseconds) that current envelope phase has been running
  int16_t phaseTime;

  // Put envelope generator in new state
  void setState(EnvelopeState newState);
};

inline
int8_t Envelope::scaleSample(int8_t sample) {
  // Calculate outsample scaled by envelope (which is scaled down to the correct resolution)
    int16_t outSample =
      (int16_t)sample * (int16_t)(level >> 8);

    return (outSample >> 8);
}

#endif /* ENVELOPE_H_ */
