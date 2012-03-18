/** @file SoundDriver.cpp
 *  @date Jul 20, 2010
 */

#include "SoundDriver.h"
#include "HardwareSerial.h"

// TODO - Put these enums somewhere in a location common to this and the sound project

/**
 * Different types of commands available for a voice
 */
enum VoiceCommandType {
  setVolume         = 0x00,
  setVoiceWaveform  = 0x01,
  setVoicePulseWidth     = 0x02,
  setFilterOnOff    = 0x08,
  setVoiceFrequency = 0x09,
  setSlaveSync      = 0x0a
};

enum GlobalCommandType {
  resetVoices     = 0x00,
  globalPulsewidth = 0x03,
  globalAttack     = 0x04,
  globalDecay      = 0x05,
  globalSustain    = 0x06,
  globalRelease    = 0x07,
  globalGateState  = 0x08
};

SoundDriver::SoundDriver(uint8_t addy) {
  _twiAddress = addy;
}

// TODO - Maybe inline this code?
void SoundDriver::restartGate() {
  setEnvelopeGate(false);
  setEnvelopeGate(true);
}

void SoundDriver::setFrequency(uint8_t voiceNum, uint16_t freq) {
  Serial.write(voiceNum+1);
  Serial.write((uint8_t)setVoiceFrequency);
  Serial.write((uint8_t)(freq>>8));
  Serial.write((uint8_t)(freq&0xff));
}

void SoundDriver::setEnvelopeGate(bool isClosed) {
  Serial.write(0);
  Serial.write((uint8_t)globalGateState);
  Serial.write((uint8_t)isClosed ? 1 : 0);
}

void SoundDriver::reset() {
  Serial.write(0x00);
  Serial.write(0x00);
}

void SoundDriver::setVoiceLevel(uint8_t voiceNum, uint8_t level) {
  Serial.write(voiceNum+1);
  Serial.write((uint8_t)setVolume);
  Serial.write(level);
}

void SoundDriver::setWaveform(uint8_t voiceNum, WaveformType waveform) {
 Serial.write(voiceNum+1);
 Serial.write((uint8_t)setVoiceWaveform);
 Serial.write((uint8_t)waveform);
}

void SoundDriver::setAttackTime(uint16_t time) {
  Serial.write(0x00);
  Serial.write((uint8_t)globalAttack);
  Serial.write((uint8_t)(time>>8));
  Serial.write((uint8_t)(time&0xff));
}

void SoundDriver::setDecayTime(uint16_t time) {
  Serial.write(0x00);
  Serial.write((uint8_t)globalDecay);
  Serial.write((uint8_t)(time>>8));
  Serial.write((uint8_t)(time&0xff));
}

void SoundDriver::setSustainLevel(uint8_t level) {
  Serial.write(0x00);
  Serial.write((uint8_t)globalSustain);
  Serial.write(level);
}

void SoundDriver::setReleaseTime(uint16_t time) {
  Serial.write(0x00);
  Serial.write((uint8_t)globalRelease);
  Serial.write((uint8_t)(time>>8));
  Serial.write((uint8_t)(time&0xff));
}

void SoundDriver::setPuleseWidth(uint8_t voiceNum, uint8_t pw) {
  Serial.write(voiceNum+1);
  Serial.write((uint8_t)setVoicePulseWidth);
  Serial.write(pw);
}

void SoundDriver::setGlobalPulseWidth(uint8_t pw) {
  Serial.write(0x00);
  Serial.write((uint8_t)globalPulsewidth);
  Serial.write(pw);
}
