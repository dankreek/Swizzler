/*
 * PulseWidthModulationEffect.cpp
 *
 *  Created on: Jan 5, 2011
 *      Author: justin
 */

#include "PulseWidthModulationEffect.h"
#include "Swizzler.h"
#include "PresetManager.h"

PulseWidthModulationEffect::PulseWidthModulationEffect() {
  lastPulseWidth = 128;
  isEffectOn = false;
}

void PulseWidthModulationEffect::nextModulationValue(int16_t modVal) {
  int16_t modAmount = (modVal * (int16_t)Swizzler::modWheelLevel) / 127;
  uint8_t pwValue = ((modAmount/2) + 128);

  if (pwValue != lastPulseWidth) {
    if (isEffectOn) { Swizzler::soundChip.setGlobalPulseWidth(pwValue); }
    lastPulseWidth = pwValue;
  }
}

void PulseWidthModulationEffect::enableEffect(bool onOff) {
  isEffectOn = onOff;

  if (!isEffectOn) {
    Swizzler::soundChip.setGlobalPulseWidth(PresetManager::curSettings.pulseWidth << 1);
  }
}
