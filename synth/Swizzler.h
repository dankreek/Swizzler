/*
 * Swizzler.h
 *
 *  Created on: Jan 31, 2010
 *      Author: justin
 *
 */

#ifndef SWIZZLER_H_
#define SWIZZLER_H_

#include "MidiInput.h"
#include "Wire.h"
#include "SetParameters.h"
#include "ExternalEeprom.h"
#include "SurfaceControlManager.h"
#include "SoundDriver.h"
#include "ArpeggiatorNoteFilter.h"
#include "Oscillators.h"
#include "SineGenerator.h"
#include "LfoController.h"
#include "FreqFilterChain.h"

class Swizzler {
public:
  static LfoController lfoController;           // Controls LFO generation

  // Calculate all the frequency modulation effects
  static FreqFilterChain freqModEffectChain;

  // Note filters
  static ArpeggiatorNoteFilter arp;

  // Current level that the mod wheel is at
  static uint8_t modWheelLevel;

  // Class which contains a freq. filter chain for each oscillator
  static Oscillators oscillators;

  static uint16_t portamentoTime;

  // The bend range is measured in schlips (like cents but 32 divisions instead of 100 between half-steps)
  static int16_t bendRange;

  static uint16_t msCounter;    // Incremented once every millisecond
  static const int ledPin = 13;
  static const uint8_t eepromAddress = 0x50;

  static const uint8_t numOscillators = 3;

  static SoundDriver soundChip;

  static void handlePitchBend();

  void init();
  void mainLoop();

  static void enableArpeggio(bool onOff);

  /**
   * Send the processor into an infinite blinking loop to indicate a run-time error
   */
  void setErrorState();

  static void setLed(bool onOff);
private:
  // How long to wait until the display unit is fully powered up (measured in milliseconds)
  static const uint8_t  poweronDisplayDelay = 100;
};

extern Swizzler swizzler;

#endif /* SWIZZLER_H_ */

