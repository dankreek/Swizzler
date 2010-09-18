/*
 * EnvelopeNoteFilter.cpp
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#include "Swizzler.h"
#include "EnvelopeNoteFilter.h"

EnvelopeNoteFilter::EnvelopeNoteFilter()
{
  // TODO Auto-generated constructor stub

}

void EnvelopeNoteFilter::noteOn(uint8_t noteNumber, uint8_t velocity) {
  if (curNoteNum != noteNumber) {
    restartGate();
    curNoteNum = noteNumber;
  }

  // Pass note through to next filter in chain
  sendNoteOn(noteNumber, velocity);
}

void EnvelopeNoteFilter::restartGate() {
  for (uint8_t i=0; i < Swizzler::numOscillators; i++) {
    Swizzler::soundChip.setEnvelopeGate(i, false);
    Swizzler::soundChip.setEnvelopeGate(i, true);
  }
}

void EnvelopeNoteFilter::noteOff(uint8_t noteNumber) {
  if (curNoteNum == noteNumber) {
    for (uint8_t i=0; i < Swizzler::numOscillators; i++) {
      Swizzler::soundChip.setEnvelopeGate(i, false);
    }

    curNoteNum = -1;
  }

  // Pass note off through to next filter in the chain
  sendNoteOff(noteNumber);
}
