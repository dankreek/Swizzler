/*
 * PulseWidthModulationEffect.h
 *
 *  Created on: Jan 5, 2011
 *      Author: justin
 */

#ifndef PULSEWIDTHMODULATIONEFFECT_H_
#define PULSEWIDTHMODULATIONEFFECT_H_

#include <inttypes.h>
#include "IModulationEffect.h"

class PulseWidthModulationEffect : public IModulationEffect {
public:
  PulseWidthModulationEffect();
  void nextModulationValue(int16_t value);
  void enableEffect(bool onOff);
private:
  bool isEffectOn;
  uint8_t lastPulseWidth;
};

#endif /* PULSEWIDTHMODULATIONEFFECT_H_ */
