/*
 * FreqFilterChain.cpp
 *
 *  Created on: Aug 28, 2010
 *      Author: justin
 */

#include "FreqFilterChain.h"
#include "OscillatorMux.h"

FreqFilterChain::FreqFilterChain() {
  prevNoteNum = -1;
  curNoteNum = -1;
}

void FreqFilterChain::setNoteOffset(int8_t ofs) {
  noteOffset = ofs;
}

void FreqFilterChain::noteOn(uint8_t noteNumber, uint8_t velocity) {
  prevNoteNum = curNoteNum;
  curNoteNum = (noteNumber+noteOffset);

  // For now just convert to frequency and send
  oscOut.recvFreq(OscillatorMux::noteToFreq(noteNumber));
}


void FreqFilterChain::noteOff(uint8_t noteNumber) {}
