/*
 * SineGenerator.cpp
 *
 *  Created on: Oct 3, 2010
 *      Author: justin
 */

#include "SineGenerator.h"

SineGenerator::SineGenerator() {
  incAmount = 0;
  idxAccum = 0;
}

void SineGenerator::nextTick() {
  idxAccum += incAmount;
}

void SineGenerator::setFrequency(uint16_t freq) {
  incAmount = (freq*0x10000)/1000;
}

int16_t SineGenerator::getCurValue() {
  // Convert idxAccum (16 bit) to an index between 0-127 (7 bit)
  return sineTable.getSine(idxAccum>>9);
}
