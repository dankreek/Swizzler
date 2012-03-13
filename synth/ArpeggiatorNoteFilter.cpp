/** @file   ArpeggiatorNoteFilter.cpp
 *  @date   Aug 23, 2010
 *  @author Justin May <may.justin@gmail.com>
 */

#include "ArpeggiatorNoteFilter.h"
#include "Swizzler.h"
#include <stdlib.h>

ArpeggiatorNoteFilter::ArpeggiatorNoteFilter() {
  setArpDirection(up);
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

  // Simply turn the gate on if arpeggiating if off
  if (isBypassOn) {
//    if (noteNumber != noteBuffer.getLastNote()) {
      Swizzler::soundChip.restartGate();
//    }

    // Pass note through to next note reciever
    sendNoteOn(noteNumber, velocity);
  // Do the arpeggiating
  } else {
    // If this note sets the minimum number of notes close the envelope gate
    if (noteBuffer.size == minNotes) {
      restartArpeggio();
      Swizzler::soundChip.setEnvelopeGate(true);
    }
  }
}

void ArpeggiatorNoteFilter::noteOff(uint8_t noteNumber) {
  uint8_t lastNote = noteBuffer.getLastNote();
  noteBuffer.removeMidiNote(noteNumber);

  if (isBypassOn) {
    if (noteNumber == lastNote) {
      Swizzler::soundChip.setEnvelopeGate(false);
    }

    // Pass note off through to next filter in the chain
    sendNoteOff(noteNumber);
  } else {
    // If removing this note puts the number of notes held down below the minimum, open the envelope gate
    // TODO: This needs to be more intelligent. When the user lets off on all the notes, let the arp run for envelope decay
    if (noteBuffer.size == (minNotes-1)) {
      Swizzler::soundChip.setEnvelopeGate(false);
    }
  }
}

void ArpeggiatorNoteFilter::restartArpeggio() {
  if (curDir != down) { nextNoteI = 0; }
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
	if ( !isBypassOn ) {
		if ( noteBuffer.size >= minNotes ) {
			// TODO - Verify this is true and put this in a constant somewhere
			// 4 ticks per millisecond
			curTime += 4;

			// Switch to the next note
			if ( curTime >= arpTime ) {
				curTime = 0;
				sendNoteOn(noteBuffer.buffer[nextNoteI], 127);
				incNextI();
			}

		}
	}
}

void ArpeggiatorNoteFilter::setBypass(bool onOff) {
  isBypassOn = onOff;
}

void ArpeggiatorNoteFilter::incNextI() {
  switch (curDir) {
  case up:
    nextNoteI = (nextNoteI + 1) % noteBuffer.size;
    break;

  case down:
    nextNoteI--;
    if (nextNoteI == -1) nextNoteI = (noteBuffer.size-1);
    break;

  case random:
  default:
    uint8_t nextCandidateI;

    // Make sure a different index is randomly selected
    do {
      nextCandidateI = (rand() % noteBuffer.size);
    } while (nextCandidateI == nextNoteI);

    nextNoteI  = nextCandidateI;
    break;
  }

}

void ArpeggiatorNoteFilter::update() {}
