/*
 * Oscillators.cpp
 *
 *  Created on: Aug 28, 2010
 *      Author: justin
 */

#include "Oscillators.h"

Oscillators::Oscillators() {

}

void Oscillators::noteOn(uint8_t noteNumber, uint8_t velocity) {
  for (uint8_t i=0; i < numVoices; i++) oscillatorList[i].noteOn(noteNumber, velocity);
}

void Oscillators::noteOff(uint8_t noteNumber) {
  // We really don't need to do any note off stuff here, since the gate stuff's already been done
  //for (uint8_t i=0; i <numVoices; i++) oscillatorList[i].noteOff(noteNumber);
}

void Oscillators::setNoteOffset(uint8_t oscNum, int8_t offset) {
  oscillatorList[oscNum].setNoteOffset(offset);
}
