/*
 * Voice.h
 *
 *  Created on: Jul 10, 2010
 *      Author: justin
 */

#ifndef VOICE_H_
#define VOICE_H_

#include <inttypes.h>
#include "Envelope.h"
#include "Waveform.h"

class Voice {
public:
  // Calculate the next sample and apply the envelope
  inline int8_t getNextSample() {
    // Increment accumulator
    phaseAccumulator += phaseChangeRate;

    // Phase accumulator needs to be scaled from 16 to 7 bits (the length of the wavetable)
    return waveform.getSample(phaseAccumulator>>9);
  }

  // Initialize this voice
  void init();

  Envelope envelope;
  Waveform waveform;

  // Calculate the phaseChangeRate by frequency (in Hz)
  void setFrequency(uint16_t freq);

private:
  uint16_t phaseAccumulator;

  // The rate at which the phase accumulator increments
  uint16_t phaseChangeRate;
};

#endif /* VOICE_H_ */
