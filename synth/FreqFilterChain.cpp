/*
 * FreqFilterChain.cpp
 *
 *  Created on: Aug 28, 2010
 *      Author: justin
 */

#include "FreqFilterChain.h"

FreqFilterChain::FreqFilterChain() {
  prevNoteNum = -1;
  curNoteNum = -1;

  // Tell all the filters who their parent is
  oscOut.setParentContainer(this);
  directNoteFilter.setParentContainer(this);
  pitchbendFilter.setParentContainer(this);
  portamentoFilter.setParentContainer(this);

  // Link frequency filters together
  directNoteFilter.linkTo(&pitchbendFilter);
  portamentoFilter.linkTo(&pitchbendFilter);

  pitchbendFilter.linkTo(&oscOut);

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
    chainHead = &directNoteFilter;
  }
}

void FreqFilterChain::setNoteOffset(int8_t ofs) {
  noteOffset = ofs;
}

void FreqFilterChain::updateFrequency() {
  chainHead->updateFreq();
}

void FreqFilterChain::noteOn(uint8_t noteNumber, uint8_t velocity) {
  prevNoteNum = curNoteNum;
  curNoteNum = (noteNumber+noteOffset);
  updateFrequency();
}

void FreqFilterChain::nextTick() {
  portamentoFilter.nextTick();
}

void FreqFilterChain::noteOff(uint8_t noteNumber) {}
