/*
 * Envelope.cpp
 *
 *  Created on: Jul 10, 2010
 *      Author: justin
 */

#include "Envelope.h"

void Envelope::msTickHandler() {
  switch (state) {
    case attackPhase:
      envelopeLevel += changeRate;
      phaseTime++;
      if (phaseTime >= attack) setState(decayPhase);
      break;

    case decayPhase:
      envelopeLevel -= changeRate;
      phaseTime++;
      if (phaseTime >= decay) setState(sustainPhase);
      break;

    case sustainPhase:
      envelopeLevel = sustain;
      break;

    case releasePhase:
      envelopeLevel -= changeRate;
      phaseTime++;
      if (phaseTime >= release) setState(inactive);
      break;
  }
}

void Envelope::setGate(bool isClosed) {
  if (gateState != isClosed) {
    // Gate is newly closed, start attack phase
    if (isClosed) {
      setState(attackPhase);
    }
    // Gate is newly opened, start decay phase
    else {
      setState(releasePhase);
    }
  }
}

void Envelope::setState(EnvelopeState newState) {
  switch (newState) {
    case attackPhase:
      // Calculate attack rate
      changeRate = 0xffff/attack;
      envelopeLevel = 0;
      break;
    case decayPhase:
      changeRate = (0xffff-sustain)/decay;
      envelopeLevel = 0xffff;
      break;
    case sustainPhase:
      changeRate = 0;
      envelopeLevel = sustain;
      break;
    case releasePhase:
      changeRate = sustain/release;
      // Level should be at sustain level already
      break;
    case inactive:
      changeRate = 0;
      envelopeLevel = 0;
  }

  phaseTime = 0;
  state = newState;
}
