/*
 * FreqUtils.cpp
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#include "FreqUtils.h"

uint16_t FreqUtils::noteLookupTable[] = {
  4186,   // C
  4435,   // C#
  4699,   // D
  4978,   // D#
  5274,   // E
  5588,   // F
  5920,   // F#
  6272,   // G
  6645,   // G#
  7040,   // A
  7459,   // A#
  7902,   // B
};

uint16_t FreqUtils::noteToFreq(uint8_t noteNum) {
  /**
   * The MIDI standard defines note #0 as a 'C', so
   * divide the note number by 12 to get the octave the note is in
   * and take the remainder the find the note name.
   */
  int octave = noteNum / 12;
  int note = noteNum % 12;

  // Divides in half for the proper number of octaves
  // (every right shift is one less octave)
  return (noteLookupTable[note] >> (9-octave));
}