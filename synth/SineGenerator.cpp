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

void SineGenerator::setFrequency(uint8_t freq) {

}

int16_t SineGenerator::getCurValue() {
  return sineTable.getSine(idxAccum>>9);
}
