/*
 * PortamentoFreqFilter.cpp
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#include "PortamentoFreqFilter.h"
#include "FreqFilterChain.h"
#include "FreqUtils.h"
#include "Swizzler.h"

PortamentoFreqFilter::PortamentoFreqFilter() {
  reset();
}

void PortamentoFreqFilter::reset() {
  destPortNote = -1;
  srcPortNote = -1;
  curFrequency = 0;
}

void PortamentoFreqFilter::nextTick() {
  if (!freqAccum.stillGoing()) {
    curFrequency = freqAccum.next();

    // Force the recalculation of the frequency chain
    sendFreq(curFrequency);
  }
}

void PortamentoFreqFilter::startNewGlide() {
  freqAccum.start(
      FreqUtils::noteToFreq(srcPortNote),
      FreqUtils::noteToFreq(destPortNote),
      Swizzler::portamentoTime,
      freqAccumResolution);
}

void PortamentoFreqFilter::updateFreq() {
  // If no notes have changed, then simply output the current frequency
  if ((srcPortNote == freqChainContainer->prevNoteNum) && (destPortNote == freqChainContainer->curNoteNum)) {
    sendFreq(curFrequency);
  }
  // If a note has been played start a new glide
  else {
    // If there was no previous frequency, go directly to the destination frequency
    if (freqChainContainer->prevNoteNum == -1) {
      srcPortNote = freqChainContainer->curNoteNum;
    }
    else {
      srcPortNote = freqChainContainer->prevNoteNum;
    }

    destPortNote = freqChainContainer->curNoteNum;

    startNewGlide();
  }
}
