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
  destPortNote = 0;
  srcPortNote = 0;
  curSchlipsOffset = 0;
}

void PortamentoFreqFilter::nextTick() {
  if (timerCount <= getEffectivePortTime()) {
    curSchlipsOffset = curSchlipsOffset + offsetIncAmount;
    timerCount++;
  }
  else {
    curSchlipsOffset = 0;
  }
}

void PortamentoFreqFilter::sendEffectiveOffset() {
  sendSchlipOffset(getEffectiveOffset());
}

void PortamentoFreqFilter::startNewGlide() {
  timerCount=0;
  int16_t beginSchlip = (srcPortNote-destPortNote)*FreqUtils::schlipsDivs;


  offsetIncAmount = -(beginSchlip << linearResolution)/((int16_t)getEffectivePortTime());
  curSchlipsOffset = (beginSchlip << linearResolution);
}

bool PortamentoFreqFilter::isNewNoteStruck() {
  return (
      (destPortNote != freqChainContainer->curNoteNum) ||
      (srcPortNote != freqChainContainer->prevNoteNum));
}

bool PortamentoFreqFilter::hasPrevNoteBeenStruck() {
  return (freqChainContainer->prevNoteNum != -1);
}


void PortamentoFreqFilter::updateOffset() {
  // If no notes have changed, then simply output the current frequency
  if (!isNewNoteStruck()) {


  }
  // If a note has been played start a new glide
  else {
    // If there was no previous frequency, go directly to the destination frequency
    if (!hasPrevNoteBeenStruck()) {
      freqChainContainer->prevNoteNum = freqChainContainer->curNoteNum;
      srcPortNote = freqChainContainer->curNoteNum;
    }
    else {
      srcPortNote = freqChainContainer->prevNoteNum;
    }

    destPortNote = freqChainContainer->curNoteNum;

    startNewGlide();
  }

  sendEffectiveOffset();
}

uint16_t PortamentoFreqFilter::getEffectivePortTime() {
  // Note the +1 is because the timer routine gets called every 2ms (divide by 2)
  return (Swizzler::portamentoTime >> (linearResolution+1));
}

