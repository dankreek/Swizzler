/*
 * DirectNoteFreqFilter.cpp
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#include "DirectNoteFreqFilter.h"
#include "OscillatorMux.h"

DirectNoteFreqFilter::DirectNoteFreqFilter()
{
  // TODO Auto-generated constructor stub

}

void DirectNoteFreqFilter::updateFreq() {
  sendFreq(OscillatorMux::noteToFreq(freqChainContainer->curNoteNum));
}
