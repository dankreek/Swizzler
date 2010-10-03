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
  static EnvelopeNoteFilter envelopeController;
  static ArpeggiatorNoteFilter arp;
  static Oscillators oscillators;

  static uint16_t portamentoTime;
  static const uint8_t bendRange = 2;

  static uint16_t msCounter;    // Incremented once every millisecond
  static const int ledPin = 13;
  static const uint8_t eepromAddress = 0x50;

  static const uint8_t numOscillators = 4;

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

