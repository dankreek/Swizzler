/*
 * EnvelopeUtility.cpp
 *
 *  Created on: Sep 18, 2010
 *      Author: justin
 */

#include "EnvelopeUtility.h"
#include "Swizzler.h"

void EnvelopeUtility::restartGate() {
  Swizzler::soundChip.setEnvelopeGate(false);
  Swizzler::soundChip.setEnvelopeGate(true);
}

void EnvelopeUtility::setGate(bool openClosed) {
  Swizzler::soundChip.setEnvelopeGate(openClosed);
}
