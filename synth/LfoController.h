/** @file LfoController.h
 *  @date Jan 1, 2011
 */

#ifndef LFOCONTROLLER_H_
#define LFOCONTROLLER_H_

#include "ITimerCall.h"
#include "SineGenerator.h"
#include "PulseWidthModulationEffect.h"

/**
 * This class contains all the code that controls which LFO effects are currently
 * enabled.
 *
 * @author Justin May <may.justin@gmail.com>
 */
class LfoController : public ITimerCall {
public:
  /// The various Swizzler parameters that the LFO can modulate
  enum LfoMode {
    frequencyModulation  = 0x00, /*!< LFO will modulate the output frequency */
    pulsewidthModulation = 0x01, /*!< LFO modulates the pulsewidth of each oscillator */
  };

  /**
   * Sine wave generate. 
   *
   * This is public so that the freq. modulation filters can read it
   */
  SineGenerator sinGenerator;

  /**
   * Set which synth parameter is going to be modulated by the LFO
   *
   * @param mode    Parameter to be modulated
   */
  void setLfoMode(LfoMode mode);

  void nextTick();

private:
  /// The current LFO mode
  LfoMode curMode;

  /**
   * This is placed here to directly manipulate the pulse width of each oscillator
   * after each timer tick. The frequency modulation effect is a memebr of the frequency
   * filter chain, so it operatefd there.  
   */
  PulseWidthModulationEffect pwModulation;
};

#endif /* LFOCONTROLLER_H_ */
