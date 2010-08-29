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
  Swizzler::soundChip.setEnvelopeGate(0, false);
  Swizzler::soundChip.setEnvelopeGate(0, true);
  swizzler.setLed(true);
}

void EnvelopeNoteFilter::noteOff(uint8_t noteNumber) {
  if (curNoteNum == noteNumber) {
    Swizzler::soundChip.setEnvelopeGate(0, false);
    curNoteNum = -1;
  }

  // Pass note off through to next filter in the chain
  sendNoteOff(noteNumber);
  swizzler.setLed(false);
}