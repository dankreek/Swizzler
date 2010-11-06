/*
 * Swizzler.h
 *
 *  Created on: Jan 31, 2010
 *      Author: justin
 *
 */

#ifndef SWIZZLER_H_
#define SWIZZLER_H_

#include "EnvelopeNoteFilter.h"

#include "MidiInput.h"
#include "Wire.h"
#include "SetParameters.h"
#include "ExternalEeprom.h"
#include "SurfaceControlManager.h"
#include "SoundDriver.h"
#include "ArpeggiatorNoteFilter.h"
#include "Oscillators.h"
#include "SineGenerator.h"

class Swizzler {
public:
  static SineGenerator freqModSineWave;         // Frequency modulation sinewave generator

  // Note filters
  static EnvelopeNoteFilter envelopeController;
  static ArpeggiatorNoteFilter arp;

  // Current level that the mod wheel is at
  static uint8_t modWheelLevel;

  // Class which contains a freq. filter chain for each oscillator
  static Oscillators oscillators;

  static uint16_t portamentoTime;

  // The bend range is measured in schlips (like cents but 32 divisions instead of 100 between half-steps)
  static const int16_t bendRange = 64;

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
};

extern Swizzler swizzler;

#endif /* SWIZZLER_H_ */

