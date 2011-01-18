/*
 * Oscillators.cpp
 *
 *  Created on: Aug 28, 2010
 *      Author: justin
 */

#include "Oscillators.h"
#include "Swizzler.h"
#include "FreqUtils.h"

Oscillators::Oscillators() {
  curRootNote = 0;
  for (uint8_t i=0; i < numVoices; i++) {
    noteOffset[i] = 0;
    lastFreq[i] = 0;
  }
}

void Oscillators::noteOn(uint8_t noteNumber, uint8_t velocity) {
  curRootNote = noteNumber;
  update();
}

void Oscillators::update() {
  for (uint8_t i=0; i < numVoices; i++) { outputFrequency(i); }
}

void Oscillators::outputFrequency(uint8_t voiceNum) {
  int16_t freqModOffset = Swizzler::freqModEffectChain.getFreqOffset();
  uint16_t outFreq = FreqUtils::modulatedFreq(curRootNote + noteOffset[voiceNum], freqModOffset);

  if (outFreq != lastFreq[voiceNum]) {
    Swizzler::soundChip.setFrequency(voiceNum, outFreq);
    lastFreq[voiceNum] = outFreq;
  }
}

void Oscillators::noteOff(uint8_t noteNumber) {
  // We really don't need to do any note off stuff here, since the gate stuff's already been done
}

void Oscillators::setNoteOffset(uint8_t oscNum, int8_t offset) {
  noteOffset[oscNum] = offset;
  outputFrequency(oscNum);
}

