/*
 * FreqModFreqFilter.cpp
 *
 *  Created on: Oct 3, 2010
 *      Author: justin
 */

#include "FreqModFreqFilter.h"
#include "Swizzler.h"

FreqModFreqFilter::FreqModFreqFilter() {
  curBaseOffset = 0;
}

int16_t FreqModFreqFilter::calcCurOffset() {
  int16_t sinVal = Swizzler::freqModSineWave.getCurValue();
  return (sinVal*(Swizzler::modWheelLevel>>2))/255;
}

void FreqModFreqFilter::recvOffset(int16_t offset) {
  curBaseOffset = offset;
  updateOffset();
}

void FreqModFreqFilter::updateOffset() {
  sendSchlipOffset(curBaseOffset+calcCurOffset());
}

