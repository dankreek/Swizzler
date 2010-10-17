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
  static const uint8_t modWheel = 1;

  static const uint8_t lfoFreq = 85;
  static const uint8_t lfoType = 86;

  static const uint8_t portamentoOnOff = 65;
  static const uint8_t portamentoTime = 5;

  static const uint8_t oscLevel1 = 20;
  static const uint8_t oscWaveform1 = 21;

  static const uint8_t oscLevel2 = 22;
  static const uint8_t oscWaveform2 = 23;
  static const uint8_t oscOffset2 = 24;

  static const uint8_t oscLevel3 = 25;
  static const uint8_t oscWaveform3 = 26;
  static const uint8_t oscOffset3 = 27;

//  static const uint8_t noiseLevel = 28;

  static const uint8_t pitchBendRange = 29;

  static const uint8_t pulseWidth = 30;

  static const uint8_t attackTime = 73;
  static const uint8_t decayTime = 74;
  static const uint8_t sustainLevel = 75;
  static const uint8_t releaseTime = 76;

  static const uint8_t arpOnOff = 77;
  static const uint8_t arpTime = 78;
  static const uint8_t arpMinNotes = 79;
  static const uint8_t arpDirection = 80;

  // Store the current settings in the slot of the currently selected preset
  static const uint8_t storePreset = 102;
};

#endif
