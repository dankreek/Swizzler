/*
 * Oscillators.cpp
 *
 *  Created on: Aug 28, 2010
 *      Author: justin
 */

#include "Oscillators.h"

Oscillators::Oscillators() {
  for (uint8_t i=0; i < numVoices; i++) {
    oscillatorList[i].voiceNumber = i;
    oscillatorList[i].setNoteOffset(0);
  }
}

void Oscillators::updateFrequencies() {
  for (uint8_t i=0; i <numVoices; i++) {

  }
}

void Oscillators::noteOn(uint8_t noteNumber, uint8_t velocity) {
  for (uint8_t i=0; i < numVoices; i++) oscillatorList[i].noteOn(noteNumber, velocity);
}

void Oscillators::noteOff(uint8_t noteNumber) {
  // We really don't need to do any note off stuff here, since the gate stuff's already been done
}

void Oscillators::setNoteOffset(uint8_t oscNum, int8_t offset) {
  oscillatorList[oscNum].setNoteOffset(offset);
}
