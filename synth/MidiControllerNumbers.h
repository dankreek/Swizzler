/*
 * MidiControllerNumbers.h
 *
 *  Created on: Aug 10, 2010
 *      Author: justin
 *
 */
#ifndef MIDICONTROLLERNUMBERS_H_
#define MIDICONTROLLERNUMBERS_H_

#include <inttypes.h>

class MidiControllerNumbers {
public:
  static const uint8_t portamentoOnOff = 20;
  static const uint8_t portamentoTime = 10;

  static const uint8_t pitchBendRange = 15;

  static const uint8_t pulseWidth = 2;

  static const uint8_t attackTime = 75;
  static const uint8_t decayTime = 76;
  static const uint8_t sustainLevel = 92;
  static const uint8_t releaseTime = 95;

  static const uint8_t arpOnOff = 26;
  static const uint8_t arpTime = 12;
  static const uint8_t arpMinNotes = 13;

  // Store the current settings in the slot of the currently selected preset
  static const uint8_t storePreset = 84;
};

#endif