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
  lastOffset = offset;
  updateOffset();
}

int16_t genOffset() {
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

  return numSchlips;
}

void PitchbendFreqFilter::updateOffset() {
  sendSchlipOffset(lastOffset+genOffset());
}
