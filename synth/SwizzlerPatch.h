/** @file SwizzlerPatch.h */

#ifndef PRESET_H
#define PRESET_H

#include <inttypes.h>

// TODO - Maybe move this into PresetManager?

/**
 * @brief The SwizzlerPatch struct represents one synth patch stored in RAM.
 *
 * Note that all stored values are in raw MIDI controller values (0-127)
 * and will be translated to real values through SetParameters.
 *
 * @author Justin May <may.justin@gmail.com>
 */
struct SwizzlerPatch {
  /// Preset name
  char name[16];

  /// LFO Frequency
  uint8_t lfoFreq;

  /// LFO Type
  uint8_t lfoType;

  /// Attack time
  uint8_t attackTime;
  /// Decay time
  uint8_t decayTime;
  /// Sustain level
  uint8_t sustainLevel;
  /// Release time
  uint8_t releaseTime;

  /// VCO1 Waveform
  uint8_t waveform1;
  /// VCO1 Level
  uint8_t voiceLevel1;

  /// VCO2 Waveform
  uint8_t waveform2;
  /// VCO2 Level
  uint8_t voiceLevel2;
  /// VCO3 frequency offset
  uint8_t freqOffset2;

  /// VCO3 Waveform
  uint8_t waveform3;
  /// VCO3 Level
  uint8_t voiceLevel3;
  /// VCO3 frequency offset
  uint8_t freqOffset3;


  /// Pulsewidth for each VCO's pulse waveform
  uint8_t pulseWidth;

  /// Portamento glide time
  uint8_t portamentoTime;
  /// Enable portamento
  uint8_t portamentoOn;

  /// Arpeggio time
  uint8_t arpeggioTime;
  /// Minimum number of notes to start an arpeggio
  uint8_t arpeggioMinNotes;
  /// Enable arpeggios
  uint8_t arpeggioOn;
  /// Arpeggio direction
  uint8_t arpeggioDirection;

  /// Pitch bend range
  uint8_t bendRange;
};

#endif
