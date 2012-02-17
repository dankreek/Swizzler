/** @file FreqFilterChain.cpp
 *  @date Aug 28, 2010
 */

#include "FreqFilterChain.h"
#include "Swizzler.h"

FreqFilterChain::FreqFilterChain() {
  prevNoteNum = -1;
  curNoteNum = -1;

  // Tell all the filters who their daddy is
  pitchbendFilter.setParentContainer(this);
  portamentoFilter.setParentContainer(this);
  freqModFilter.setParentContainer(this);

  // Link frequency filters together
  portamentoFilter.linkTo(&pitchbendFilter);
  pitchbendFilter.linkTo(&freqModFilter);
  freqModFilter.linkTo(&outputFilter);

  setPortamento(false);
}

void FreqFilterChain::setPortamento(bool onOff) {
  if (onOff) {
    chainHead = &portamentoFilter;
  } else {
    chainHead = &pitchbendFilter;
  }
}

void FreqFilterChain::update() {
	chainHead->updateOffset();

	// Tell the next guy (oscillators) to update
	receiver->update();
}

void FreqFilterChain::noteOn(uint8_t noteNumber, uint8_t velocity) {
	prevNoteNum = curNoteNum;
	// TODO - I don't think noteOffset is needed anymore.
	curNoteNum = noteNumber + noteOffset;
	update();
	sendNoteOn( noteNumber, velocity );
}

void FreqFilterChain::nextTick() {
	portamentoFilter.nextTick();
	update();
}

void FreqFilterChain::setFrequencyModulation(bool onOff) {
	if (onOff) {
		pitchbendFilter.linkTo(&freqModFilter);
	} else {
		pitchbendFilter.linkTo(&outputFilter);
	}
}

void FreqFilterChain::noteOff(uint8_t noteNumber) {}
