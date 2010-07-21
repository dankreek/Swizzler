/**
 * SoundDriver.h
 *
 *  Created on: Jul 20, 2010
 *      Author: justin
 */
#ifndef SOUNDDRIVER_H_
#define SOUNDDRIVER_H_

#include <inttypes.h>
#include "Wire.h"

class SoundDriver {
public:
  SoundDriver(uint8_t twiAddress);

  enum WaveformType {
    triangleWave         = 0x00,
    sawtoothWave         = 0x01,
    reverseSawtoothWave  = 0x02,
    squareWave           = 0x03,
    noiseWave            = 0x04
  };

  void setVoiceLevel(uint8_t voiceNum, uint8_t level);
  void setWaveform(uint8_t voiceNum, WaveformType waveform);
  void setFrequency(uint8_t voiceNum, uint16_t frequency);
  void setEnvelopeGate(uint8_t voiceNum, bool isClosed);
  void setAttackTime(uint8_t voiceNum, uint16_t time);
  void setDecayTime(uint8_t voiceNum, uint16_t time);
  void setSustainLevel(uint8_t voiceNum, uint8_t level);
  void setReleaseTime(uint8_t voiceNum, uint16_t time);

private:
  uint8_t twiAddress;
};

#endif
