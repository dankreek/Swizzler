/*
 * DirectNoteFreqFilter.cpp
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#include "DirectNoteFreqFilter.h"
#include "FreqUtils.h"
#include "FreqFilterChain.h"

DirectNoteFreqFilter::DirectNoteFreqFilter()
{
  // TODO Auto-generated constructor stub

}

void DirectNoteFreqFilter::updateFreq() {
  sendFreq(FreqUtils::noteToFreq(freqChainContainer->curNoteNum));
}
