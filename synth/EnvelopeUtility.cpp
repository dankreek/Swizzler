/*
 * EnvelopeUtility.cpp
 *
 *  Created on: Sep 18, 2010
 *      Author: justin
 */

#include "EnvelopeUtility.h"
#include "Swizzler.h"

void EnvelopeUtility::restartGate() {
  for (uint8_t i=0; i < Swizzler::numOscillators; i++) {
    Swizzler::soundChip.setEnvelopeGate(i, false);
    Swizzler::soundChip.setEnvelopeGate(i, true);
  }

}

void EnvelopeUtility::setGate(bool openClosed) {
  for (uint8_t i=0; i < Swizzler::numOscillators; i++) {
    Swizzler::soundChip.setEnvelopeGate(i, openClosed);
  }
}
