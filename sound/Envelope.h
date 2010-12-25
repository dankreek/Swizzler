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

  static const uint16_t maxLevel = 0xffff;

  // Current envelope level (0=quietest, maxLevel=loudest)
  uint16_t level;

  // Attack, decay and release times
  uint16_t attack, decay, release;

  // Sustain level (0- maxLevel)
  uint16_t sustain;

  // Operate the gate. true=closed, false=open
  void setGate(bool isClosed);

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
  uint16_t changeRate;

  // How long (in milliseconds) that current envelope phase has been running
  uint16_t phaseTime;

  // Put envelope generator in new state
  void setState(EnvelopeState newState);
};

#endif /* ENVELOPE_H_ */
