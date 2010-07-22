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
  int8_t getNextSample();

  // Initialize this voice
  void init();

  // This voice's envelope generator
  Envelope envelope;

  // This voice's waveform generator
  Waveform waveform;

  // Calculate the phaseChangeRate by frequency (in Hz)
  void setFrequency(uint16_t freq);

  // If this voice being sent through the filter
  bool isFiltered;

  // Voice output volume is 5bits
  static const uint8_t outputVolumeResolution = 5;

  // This voice's output volume (0-32)
  uint8_t outputVolume;

  // Is another voice synced to this one
  // -1 signifies no sync
  int8_t slaveSyncVoice;

  uint16_t phaseAccumulator;

  // Apply power-on defaults
  void resetVoice();

private:
  // The rate at which the phase accumulator increments
  uint16_t phaseChangeRate;
};

inline int8_t Voice::getNextSample() {
  // Increment accumulator
  phaseAccumulator += phaseChangeRate;

  // Calculate outsample scaled by envelope (which is scaled to 8 bits from 16)
  int16_t outSample = waveform.getSample(phaseAccumulator)*(envelope.level>>8);

  return (outSample >> 8);
}


#endif /* VOICE_H_ */
