/*
 * LfoController.h
 *
 *  Created on: Jan 1, 2011
 *      Author: justin
 */

#ifndef LFOCONTROLLER_H_
#define LFOCONTROLLER_H_

#include "ITimerCall.h"
#include "SineGenerator.h"
#include "PulseWidthModulationEffect.h"

/**
 * This class contains all the code that controls which LFO effects are currently
 * enabled.
 */
class LfoController : public ITimerCall {
public:
  enum LfoMode {
    frequencyModulation  = 0x00,
    pulsewidthModulation = 0x01,
  };

  // The sine generator is public so that the freq. modulation filters can read it
  SineGenerator sinGenerator;

  void setLfoMode(LfoMode mode);


  void nextTick();

private:
  LfoMode curMode;
  PulseWidthModulationEffect pwModulation;
};

#endif /* LFOCONTROLLER_H_ */
