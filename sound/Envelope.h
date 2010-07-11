/*
 * Envelope.h
 *
 *  Created on: Jul 10, 2010
 *      Author: justin
 */

#ifndef ENVELOPE_H_
#define ENVELOPE_H_

#include <inttypes.h>

enum EnvelopeState {
  inactive,
  attackPhase,
  decayPhase,
  sustainPhase,
  releasePhase
};

class Envelope {
public:
  // Adjust all envelope levels every millisecond (called by main loop)
  void msTickHandler();

  // Current envelope level (0=quietest, 255=loudest)
  uint8_t envelopeLevel;

  // Attack, decay and release times
  uint16_t attack, decay, release;

  // Sustain level (0-255)
  uint8_t sustain;

  // Operate the gate. true=closed, false=open
  void setGate(bool isClosed);

private:
   EnvelopeState state;

   // The state of the gate. true=closed, false=opened
   bool gateState;
};

#endif /* ENVELOPE_H_ */
