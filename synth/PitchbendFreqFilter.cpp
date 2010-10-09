/*
 * PitchbendFreqFilter.cpp
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#include "PitchbendFreqFilter.h"
#include "FreqUtils.h"
#include "MidiInput.h"

void PitchbendFreqFilter::recvOffset(int16_t offset) {
  int16_t numSchlips;
  if (MidiInput::pitchbendAmount == 0) {
    numSchlips=0;
  }
  else if (MidiInput::pitchbendAmount > 0) {
    numSchlips = MidiInput::pitchbendAmount*Swizzler::bendRange/MidiInput::bendMax;
  }
  else {
    numSchlips = MidiInput::pitchbendAmount*Swizzler::bendRange/(-MidiInput::bendMin);
  }

  sendSchlipOffset(numSchlips+offset);
}

void PitchbendFreqFilter::updateOffset() {
  // This shouldn't be the head of the chain, so it's not needed
}
