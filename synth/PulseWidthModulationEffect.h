/** @file PulseWidthModulationEffect.h
 *  @date Jan 5, 2011
 */

#ifndef PULSEWIDTHMODULATIONEFFECT_H_
#define PULSEWIDTHMODULATIONEFFECT_H_

#include <inttypes.h>
#include "IModulationEffect.h"

/**
 *
 * @author Justin May <may.justin@gmail.com>
 */
class PulseWidthModulationEffect : public IModulationEffect {
public:
  PulseWidthModulationEffect();
  void nextModulationValue(int16_t value);
  void enableEffect(bool onOff);
private:
  /// True if pulse width modulation is current enabled
  bool _isEffectOn;

  /// The last pulse width that was generated by nextModulationValue(). 
  uint8_t _lastPulseWidth;
};

#endif /* PULSEWIDTHMODULATIONEFFECT_H_ */
