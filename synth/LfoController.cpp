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
      Swizzler::freqModEffectChain.setFrequencyModulation(true);
      pwModulation.enableEffect(false);
      break;
    case pulsewidthModulation:
      Swizzler::freqModEffectChain.setFrequencyModulation(false);
      pwModulation.enableEffect(true);
      break;
  }
}

void LfoController::nextTick() {
  sinGenerator.nextTick();
  pwModulation.nextModulationValue(sinGenerator.getCurValue());
}
