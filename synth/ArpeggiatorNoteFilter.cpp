/*
 * ArpeggiatorNoteFilter.cpp
 *
 *  Created on: Aug 23, 2010
 *      Author: justin
 */

#include "ArpeggiatorNoteFilter.h"
#include "EnvelopeUtility.h"
#include <stdlib.h>

ArpeggiatorNoteFilter::ArpeggiatorNoteFilter() {
  setArpDirection(forward);
  setArpTime(100);
  setMinNotes(3);
  curTime = 0;
}

void ArpeggiatorNoteFilter::setArpDirection(ArpeggioDirection dir) {
  curDir = dir;
}

void ArpeggiatorNoteFilter::setArpTime(uint16_t time) {
  arpTime = time;
}

void ArpeggiatorNoteFilter::noteOn(uint8_t noteNumber, uint8_t velocity) {
  // Add note to the buffer
  noteBuffer.putMidiNote(noteNumber);

  // If this note sets the minimum number of notes close the envelope gate
  if (noteBuffer.size == minNotes) {
    restartArpeggio();
    EnvelopeUtility::setGate(true);
  }
}

void ArpeggiatorNoteFilter::noteOff(uint8_t noteNumber) {
  noteBuffer.removeMidiNote(noteNumber);

  // If removing this note puts the number of notes held down below the minimum, open the envelope gate
  // TODO: This needs to be more intelligent. When the user lets off on all the notes, let the arp run for envelope decay
  if (noteBuffer.size == (minNotes-1)) {
    EnvelopeUtility::setGate(false);
  }
}

void ArpeggiatorNoteFilter::restartArpeggio() {
  if (curDir != backward) { nextNoteI = 0; }
  else { nextNoteI = (noteBuffer.size-1); }

  curTime = arpTime;
}

uint8_t ArpeggiatorNoteFilter::getMinNotes() const {
  return minNotes;
}

void ArpeggiatorNoteFilter::setMinNotes(uint8_t minNotes) {
  this->minNotes = minNotes;
}

void ArpeggiatorNoteFilter::nextTick() {
  if (noteBuffer.size >= minNotes) {
    curTime++;

    // Switch to the next note
    // TODO Implement other directions of arpeggiation
    if (curTime >= arpTime) {
      curTime = 0;
      sendNoteOn(noteBuffer.buffer[nextNoteI], 127);
      incNextI();
    }

  }
}

void ArpeggiatorNoteFilter::incNextI() {
  switch (curDir) {
  case forward:
    nextNoteI = (nextNoteI + 1) % noteBuffer.size;
    break;

  case backward:
    nextNoteI--;
    if (nextNoteI == -1)
      nextNoteI = (noteBuffer.size-1);
    break;

  case random:
  default:
    uint8_t nextCandidateI;

    do {
      nextCandidateI = (rand() % noteBuffer.size);
    } while (nextCandidateI == nextNoteI);

    nextNoteI  = nextCandidateI;
    break;
  }


}
