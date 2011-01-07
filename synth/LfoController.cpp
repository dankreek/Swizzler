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
      pwModulation.enableEffect(false);
      break;
    case amplitudeModulation:
      Swizzler::oscillators.setFrequencyModulation(false);
      pwModulation.enableEffect(false);
      break;
    case freqAndPwModulation:
      Swizzler::oscillators.setFrequencyModulation(true);
      pwModulation.enableEffect(true);
      break;
    case pulsewidthModulation:
      Swizzler::oscillators.setFrequencyModulation(false);
      pwModulation.enableEffect(true);
      break;
  }
}

void LfoController::nextTick() {
  sinGenerator.nextTick();
  pwModulation.nextModulationValue(sinGenerator.getCurValue());
}
