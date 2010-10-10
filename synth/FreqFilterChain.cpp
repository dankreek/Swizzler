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
  oscOut.setParentContainer(this);
  pitchbendFilter.setParentContainer(this);
  portamentoFilter.setParentContainer(this);
  freqModFilter.setParentContainer(this);

  // Link frequency filters together
  portamentoFilter.linkTo(&pitchbendFilter);

  pitchbendFilter.linkTo(&freqModFilter);
  freqModFilter.linkTo(&oscOut);

  setPortamento(false);

  // The start of the chain is the note->freq conversion
  // if portamento is turned on then the chainHead points to portamentoFilter
  //chainHead = &directNoteFilter;
  //chainHead = &portamentoFilter;
}

void FreqFilterChain::setPortamento(bool onOff) {
  if (onOff) {
    chainHead = &portamentoFilter;
  }
  else {
    chainHead = &pitchbendFilter;
  }
}

void FreqFilterChain::setNoteOffset(int8_t ofs) {
  int8_t delta = ofs-noteOffset;

  noteOffset = ofs;
  prevNoteNum = curNoteNum;
  curNoteNum += delta;
  updateFrequency();
}

void FreqFilterChain::updateFrequency() {
  chainHead->updateOffset();
}

void FreqFilterChain::noteOn(uint8_t noteNumber, uint8_t velocity) {
  prevNoteNum = curNoteNum;
  curNoteNum = (noteNumber+noteOffset);
  updateFrequency();
}

void FreqFilterChain::nextTick() {
  if ((Swizzler::msCounter % 4) == 0) {
    portamentoFilter.nextTick();
    updateFrequency();
  }
}

void FreqFilterChain::noteOff(uint8_t noteNumber) {}
