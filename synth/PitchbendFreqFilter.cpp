/*
 * PitchbendFreqFilter.cpp
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#include "PitchbendFreqFilter.h"
#include "FreqUtils.h"
#include "MidiInput.h"

PitchbendFreqFilter::PitchbendFreqFilter()
{
  // TODO Auto-generated constructor stub

}

int16_t PitchbendFreqFilter::getBendOffset() {
  uint8_t curMidiNote = freqChainContainer->curNoteNum;

  // Bend up
  if (MidiInput::pitchbendAmount == 0) {
    return 0;
  }
  else if (MidiInput::pitchbendAmount > 0) {
    return (MidiInput::pitchbendAmount * (int16_t)(FreqUtils::noteToFreq(curMidiNote+Swizzler::bendRange)-FreqUtils::noteToFreq(curMidiNote)))/63;
  }
  // Bend down
  else if (MidiInput::pitchbendAmount < 0) {
    //digitalWrite(8, true);
    return (MidiInput::pitchbendAmount * (int16_t)(FreqUtils::noteToFreq(curMidiNote)-FreqUtils::noteToFreq(curMidiNote-Swizzler::bendRange)))/64;
  }
}

void PitchbendFreqFilter::recvFreq(uint16_t freq) {
  sendFreq(freq + getBendOffset());
}

void PitchbendFreqFilter::updateFreq() {
  // This shouldn't be the head of the chain, so it's not needed
}
