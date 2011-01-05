/*
 * LfoController.cpp
 *
 *  Created on: Jan 4, 2011
 *      Author: justin
 */
#include "LfoController.h"
#include "Swizzler.h"

void LfoController::setLfoMode(LfoMode mode) {
  curMode = mode;

  switch (mode) {
    case frequencyModulation:
      Swizzler::oscillators.setFrequencyModulation(true);
      break;
    case amplitudeModulation:
      Swizzler::oscillators.setFrequencyModulation(false);
      break;
    case freqAndPwModulation:
      Swizzler::oscillators.setFrequencyModulation(true);
      break;
    case pulsewidthModulation:
      Swizzler::oscillators.setFrequencyModulation(false);
      break;
  }
}

void LfoController::nextTick() {
  sinGenerator.nextTick();
}
