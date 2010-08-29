/*
 * OscillatorOutput.cpp
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#include "Swizzler.h"
#include "OscillatorOutput.h"

OscillatorOutput::OscillatorOutput()
{
  // TODO Auto-generated constructor stub

}

void OscillatorOutput::recvFreq(uint16_t freq) {
  Swizzler::soundChip.setFrequency(0, freq);
}
