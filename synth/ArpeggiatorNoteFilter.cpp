/*
 * ArpeggiatorNoteFilter.cpp
 *
 *  Created on: Aug 23, 2010
 *      Author: justin
 */

#include "ArpeggiatorNoteFilter.h"
#include "EnvelopeUtility.h"

ArpeggiatorNoteFilter::ArpeggiatorNoteFilter() {
  setArpTime(100);
  setMinNotes(3);
  curTime = 0;
}

void ArpeggiatorNoteFilter::setArpTime(uint16_t time) {
  arpTime = time;
}

void ArpeggiatorNoteFilter::noteOn(uint8_t noteNumber, uint8_t velocity) {
  // Add note to the buffer
  noteBuffer.putMidiNote(noteNumber);

  // If this note sets the minimum number of notes close the envelope gate
  if (noteBuffer.size == minNotes) {
    EnvelopeUtility::setGate(true);
  }
}

void ArpeggiatorNoteFilter::noteOff(uint8_t noteNumber) {
  noteBuffer.removeMidiNote(noteNumber);

  // If removing this note puts the number of notes held down below the minimum, open the envelope gate
  if (noteBuffer.size == (minNotes-1)) {
    EnvelopeUtility::setGate(false);
  }
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
      curNoteI = (curNoteI + 1) % noteBuffer.size;
      curTime = 0;
      sendNoteOn(noteBuffer.buffer[curNoteI], 127);
    }

  }
}
