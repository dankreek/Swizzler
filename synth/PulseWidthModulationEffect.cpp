/** @file PulseWidthModulationEffect.cpp
 *  @date Jan 5, 2011
 */

#include "PulseWidthModulationEffect.h"
#include "Swizzler.h"
#include "PresetManager.h"

PulseWidthModulationEffect::PulseWidthModulationEffect() {
  _lastPulseWidth = 128;
  _isEffectOn = false;
}

void PulseWidthModulationEffect::nextModulationValue(int16_t modVal) {
  int16_t modAmount = ( modVal * (int16_t) Swizzler::modWheelLevel ) / 127;
  uint8_t pwValue = ( ( modAmount / 2 ) + 128 );

  if ( pwValue != _lastPulseWidth ) {
    if ( _isEffectOn ) { Swizzler::soundChip.setGlobalPulseWidth(pwValue); }
    _lastPulseWidth = pwValue;
  }
}

void PulseWidthModulationEffect::enableEffect(bool onOff) {
  _isEffectOn = onOff;

  if ( !_isEffectOn ) {
    Swizzler::soundChip.setGlobalPulseWidth( PresetManager::curSettings.pulseWidth << 1 );
  }
}
