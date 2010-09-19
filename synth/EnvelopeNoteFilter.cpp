/*
 * EnvelopeNoteFilter.cpp
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#include "Swizzler.h"
#include "EnvelopeNoteFilter.h"
#include "EnvelopeUtility.h"

EnvelopeNoteFilter::EnvelopeNoteFilter()
{
  // TODO Auto-generated constructor stub

}

void EnvelopeNoteFilter::noteOn(uint8_t noteNumber, uint8_t velocity) {
  if (curNoteNum != noteNumber) {
    EnvelopeUtility::restartGate();
    //restartGate();
    curNoteNum = noteNumber;
  }

  // Pass note through to next filter in chain
  sendNoteOn(noteNumber, velocity);
}

void EnvelopeNoteFilter::noteOff(uint8_t noteNumber) {
  if (curNoteNum == noteNumber) {
    EnvelopeUtility::setGate(false);
    curNoteNum = -1;
  }

  // Pass note off through to next filter in the chain
  sendNoteOff(noteNumber);
}
