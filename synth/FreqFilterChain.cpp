/*
 * FreqFilterChain.cpp
 *
 *  Created on: Aug 28, 2010
 *      Author: justin
 */

#include "FreqFilterChain.h"
#include "Swizzler.h"

FreqFilterChain::FreqFilterChain() {
  prevNoteNum = -1;
  curNoteNum = -1;

  // Tell all the filters who their daddy is
  pitchbendFilter.setParentContainer(this);
  portamentoFilter.setParentContainer(this);
  freqModFilter.setParentContainer(this);

  // Link frequency filters together
  portamentoFilter.linkTo(&pitchbendFilter);
  pitchbendFilter.linkTo(&freqModFilter);
  freqModFilter.linkTo(&outputFilter);

  setPortamento(false);
}

void FreqFilterChain::setPortamento(bool onOff) {
  if (onOff) {
    chainHead = &portamentoFilter;
  } else {
    chainHead = &pitchbendFilter;
  }
}

void FreqFilterChain::updateFrequency() {
  chainHead->updateOffset();
}

void FreqFilterChain::noteOn(uint8_t noteNumber, uint8_t velocity) {
  prevNoteNum = curNoteNum;
  curNoteNum = (noteNumber+noteOffset);
  updateFrequency();

  // Pass note information on to next node in chain
  sendNoteOn(noteNumber, velocity);
}

void FreqFilterChain::nextTick() {
  portamentoFilter.nextTick();
  updateFrequency();
}

void FreqFilterChain::setFrequencyModulation(bool onOff) {
  if (onOff) {
    pitchbendFilter.linkTo(&freqModFilter);
  } else {
    pitchbendFilter.linkTo(&outputFilter);
  }
}

void FreqFilterChain::noteOff(uint8_t noteNumber) {}
