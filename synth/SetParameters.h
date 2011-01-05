/*
 * SetParameters.h
 *
 *  Created on: Mar 9, 2010
 *      Author: justin
 */

#ifndef SETPARAMETERS_H_
#define SETPARAMETERS_H_

#include "Swizzler.h"

/**
 * All methods in this class take a 7bit unsigned int as an input which is the
 * size that a MIDI controller provides. This reduces  memory size and makes preset
 * storing and loading much easier.
 *
 * All scaling of controller values to real values are done in these methods
 */
class SetParameters {
public:
  static void enablePortamento(uint8_t);
  static void setPortamentoTime(uint8_t);

  static void setLfoFreq(uint8_t);
  static void setLfoType(uint8_t);

  static void setPulseWidth(uint8_t);

  static void setAttackTime(uint8_t);
  static void setDecayTime(uint8_t);
  static void setSustainLevel(uint8_t);
  static void setReleaseTime(uint8_t);

  static void setOscLevel1(uint8_t);
  static void setOscWaveform1(uint8_t);

  static void setOscLevel2(uint8_t);
  static void setOscWaveform2(uint8_t);
  static void setOscOffset2(uint8_t);

  static void setOscLevel3(uint8_t);
  static void setOscWaveform3(uint8_t);
  static void setOscOffset3(uint8_t);

  static void setNoiseLevel(uint8_t);

  static void enableArpeggio(uint8_t);
  static void setArpeggioTime(uint8_t);
  static void setArpeggioMinNotes(uint8_t);
  static void setArpeggioDirection(uint8_t);

  static void setBendRange(uint8_t);

  static void setModWheelLevel(uint8_t);
private:
  static void setWaveform(uint8_t, uint8_t);
  static void setVoiceLevel(uint8_t, uint8_t);
  static void setVoiceOffset(uint8_t, uint8_t);
};

#endif /* SETPARAMETERS_H_ */
