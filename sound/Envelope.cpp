/*
 * Envelope.cpp
 *
 *  Created on: Jul 10, 2010
 *      Author: justin
 */

#include "Envelope.h"

void Envelope::init() {
  attack = 0;
  decay = 0;
  sustain = 0xffff;
  release = 0;
  envelopeState = inactive;
  level = 0;
}

void Envelope::msTickHandler() {
  switch (envelopeState) {
    case attackPhase:
      level += changeRate;
      phaseTime++;
      if (phaseTime >= attack) setState(decayPhase);
      break;

    case decayPhase:
      level -= changeRate;
      phaseTime++;
      if (phaseTime >= decay) setState(sustainPhase);
      break;

    case sustainPhase:
      level = sustain;
      break;

    case releasePhase:
      level -= changeRate;
      phaseTime++;
      if (phaseTime >= release) setState(inactive);
      break;

    case inactive:
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

  gateState = isClosed;
}

void Envelope::setState(EnvelopeState newState) {
  switch (newState) {
    case attackPhase:
      // Calculate attack rate
      changeRate = 0xffff/attack;
      level = 0;
      break;
    case decayPhase:
      changeRate = (0xffff-sustain)/decay;
      level = 0xffff;
      break;
    case sustainPhase:
      changeRate = 0;
      level = sustain;
      break;
    case releasePhase:
      changeRate = sustain/release;
      // Level should be at sustain level already
      break;
    case inactive:
      changeRate = 0;
      level = 0;
  }

  phaseTime = 0;
  envelopeState = newState;
}
