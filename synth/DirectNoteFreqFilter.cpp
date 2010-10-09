/*
 * DirectNoteFreqFilter.cpp
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#include "DirectNoteFreqFilter.h"
#include "FreqUtils.h"
#include "FreqFilterChain.h"

void DirectNoteFreqFilter::updateOffset() {
  // Todo : this class is no longer needed!
  //sendSchlipOffset(FreqUtils::noteToFreq(freqChainContainer->curNoteNum));
  sendSchlipOffset(0);
}
