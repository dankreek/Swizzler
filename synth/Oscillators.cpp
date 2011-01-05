/*
 * Oscillators.cpp
 *
 *  Created on: Aug 28, 2010
 *      Author: justin
 */

#include "Oscillators.h"
#include "Swizzler.h"

Oscillators::Oscillators() {
  for (uint8_t i=0; i < numVoices; i++) {
    oscillatorList[i].voiceNumber = i;
    oscillatorList[i].setNoteOffset(0);
    oscillatorList[i].setPortamento(false);
  }
}

void Oscillators::nextTick() {
  for (uint8_t i=0; i < Oscillators::numVoices; i++)
    oscillatorList[i].nextTick();
}

void Oscillators::updateFrequencies() {
  for (uint8_t i=0; i <numVoices; i++) {
    oscillatorList[i].updateFrequency();
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

void Oscillators::setPortamento(bool onOff) {
  Swizzler::setLed(onOff);

  for (uint8_t i=0; i < numVoices; i++) {
    oscillatorList[i].setPortamento(onOff);
  }
}

void Oscillators::setFrequencyModulation(bool onOff) {
  for (uint8_t i=0; i < numVoices; i++) {
    oscillatorList[i].setFrequencyModulation(onOff);
  }
}
