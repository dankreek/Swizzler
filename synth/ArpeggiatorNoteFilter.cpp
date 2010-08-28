/*
 * ArpeggiatorNoteFilter.cpp
 *
 *  Created on: Aug 23, 2010
 *      Author: justin
 */

#include "ArpeggiatorNoteFilter.h"


void ArpeggiatorNoteFilter::noteOn(uint8_t noteNumber, uint8_t velocity) {
  sendNoteOn(noteNumber, velocity);
}

void ArpeggiatorNoteFilter::noteOff(uint8_t noteNumber) {
  sendNoteOff(noteNumber);
}
