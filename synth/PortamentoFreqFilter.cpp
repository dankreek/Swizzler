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
  if (timerCount <= (Swizzler::portamentoTime/4)) {
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
  int16_t beginSchlip = (int16_t)(srcPortNote-destPortNote)*(int16_t)FreqUtils::schlipsDivs;

  offsetIncAmount = -(beginSchlip << linearResolution)/(Swizzler::portamentoTime/4);
  curSchlipsOffset = (beginSchlip << linearResolution);

  /*
  freqAccum.start(
      FreqUtils::noteToFreq(srcPortNote),
      FreqUtils::noteToFreq(destPortNote),
      Swizzler::portamentoTime,
      freqAccumResolution);
*/
//  lineCalc.init(
//      FreqUtils::noteToFreq(srcPortNote),
//      FreqUtils::noteToFreq(destPortNote),
//      Swizzler::portamentoTime);

  /*
    lineCalc.init(
        (int16_t)(srcPortNote-destPortNote)*(int16_t)FreqUtils::schlipsDivs,
        0, Swizzler::portamentoTime/4);
*/
  // TODO : Explore this method. It's not correct but sounds cool at faster glide speeds
//  lineCalc.init(
//      (destPortNote-srcPortNote)*FreqUtils::schlipsDivs,
//      0, Swizzler::portamentoTime/4);

  //nextTick();
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
