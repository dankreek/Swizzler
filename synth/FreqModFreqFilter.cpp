/*
 * FreqModFreqFilter.cpp
 *
 *  Created on: Oct 3, 2010
 *      Author: justin
 */

#include "FreqModFreqFilter.h"

FreqModFreqFilter::FreqModFreqFilter() {
  curFreq = 0;
}

void FreqModFreqFilter::recvFreq(uint16_t freq) {
  curFreq = freq;

  // Pass-thru for now
  sendFreq(freq);
}

void FreqModFreqFilter::updateFreq() {
  sendFreq(curFreq);
}

