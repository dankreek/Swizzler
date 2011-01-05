/*
 * LfoController.h
 *
 *  Created on: Jan 1, 2011
 *      Author: justin
 */

#ifndef LFOCONTROLLER_H_
#define LFOCONTROLLER_H_

#include "ITimerCall.h"

/**
 * This class contains all the code that controls which LFO effects are currently
 * enabled.
 */
class LfoController : public ITimerCall {
public:
  enum LfoMode {
    frequencyModulation,
    pulsewidthModulation,
    freqAndPwModulation,
    amplitudeModulation
  };

  void setLfoMode(LfoMode mode);

  void nextTick();
};

#endif /* LFOCONTROLLER_H_ */
