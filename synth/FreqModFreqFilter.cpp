/*
 * FreqModFreqFilter.cpp
 *
 *  Created on: Oct 3, 2010
 *      Author: justin
 */

#include "FreqModFreqFilter.h"

FreqModFreqFilter::FreqModFreqFilter() {
  curOffset = 0;
}

void FreqModFreqFilter::recvOffset(int16_t offset) {
  curOffset = offset;

  // Pass-thru for now
  sendSchlipOffset(offset);
}

void FreqModFreqFilter::updateOffset() {
  sendSchlipOffset(curOffset);
}

