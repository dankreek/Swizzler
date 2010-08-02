/*
 * Swizzler.h
 *
 *  Created on: Jan 31, 2010
 *      Author: justin
 */

#ifndef SWIZZLER_H_
#define SWIZZLER_H_

#include "MidiInput.h"
#include "FrequencyManager.h"
#include "NoteManager.h"
#include "Wire.h"
#include "SetParameters.h"
#include "ExternalEeprom.h"
#include "SurfaceControlManager.h"
#include "SoundDriver.h"

class Swizzler {
public:
  static uint16_t msCounter;    // Incremented once every millisecond
  static const int ledPin = 13;
  static const uint8_t eepromAddress = 0x50;

  static const uint8_t numOscillators = 4;

  static SoundDriver soundChip;

  void init();
  void mainLoop();

  /**
   * Send the processor into an infinite blinking loop to indicate a run-time error
   */
  void setErrorState();

  void setLed(bool onOff);
};

extern Swizzler swizzler;

#endif /* SWIZZLER_H_ */

