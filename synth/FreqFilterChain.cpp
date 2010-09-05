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

  directNoteFilter.linkTo(&pitchbendFilter);
  pitchbendFilter.linkTo(&oscOut);

  // The start of the chain is the note->freq conversion
  //chainHead = &directNoteFilter;
  chainHead = &portamentoFilter;
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

void FreqFilterChain::noteOff(uint8_t noteNumber) {}
