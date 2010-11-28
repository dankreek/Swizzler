#include "SoundDriver.h"
#include "HardwareSerial.h"

/**
 * Different types of commands available for a voice
 */
enum VoiceCommandType {
  setVolume         = 0x00,
  setVoiceWaveform  = 0x01,
  setVoicePulseWidth     = 0x02,
  setVoiceAttackTime = 0x03,
  setVoiceDecayTime      = 0x04,
  setVoiceSustainLevel   = 0x05,
  setVoiceReleaseTime    = 0x06,
  setGateState      = 0x07,
  setFilterOnOff    = 0x08,
  setVoiceFrequency = 0x09,
  setSlaveSync      = 0x0a
};

enum GlobalCommandType {
  resetVoices     = 0x00,
  masterPulsewidth = 0x03
};

SoundDriver::SoundDriver(uint8_t addy) {
  twiAddress = addy;
}

void SoundDriver::setFrequency(uint8_t voiceNum, uint16_t freq) {
  Serial.write(voiceNum+1);
  Serial.write((uint8_t)setVoiceFrequency);
  Serial.write((uint8_t)(freq>>8));
  Serial.write((uint8_t)(freq&0xff));
}

void SoundDriver::setEnvelopeGate(uint8_t voiceNum, bool isClosed) {
  Serial.write(voiceNum+1);
  Serial.write((uint8_t)setGateState);
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

void SoundDriver::setAttackTime(uint8_t voiceNum, uint16_t attackTime) {
  Serial.write(voiceNum+1);
  Serial.write((uint8_t)setVoiceAttackTime);
  Serial.write((uint8_t)(attackTime>>8));
  Serial.write((uint8_t)(attackTime&0xff));
}

void SoundDriver::setDecayTime(uint8_t voiceNum, uint16_t decayTime) {
  Serial.write(voiceNum+1);
  Serial.write((uint8_t)setVoiceDecayTime);
  Serial.write((uint8_t)(decayTime>>8));
  Serial.write((uint8_t)(decayTime&0xff));
}

void SoundDriver::setReleaseTime(uint8_t voiceNum, uint16_t releaseTime) {
  Serial.write(voiceNum+1);
  Serial.write((uint8_t)setVoiceReleaseTime);
  Serial.write((uint8_t)(releaseTime>>8));
  Serial.write((uint8_t)(releaseTime&0xff));
}

void SoundDriver::setSustainLevel(uint8_t voiceNum, uint8_t sustainLevel) {
  Serial.write(voiceNum+1);
  Serial.write((uint8_t)setVoiceSustainLevel);
  Serial.write(sustainLevel);
}

void SoundDriver::setPuleseWidth(uint8_t voiceNum, uint8_t pw) {
  Serial.write(voiceNum+1);
  Serial.write((uint8_t)setVoicePulseWidth);
  Serial.write(pw);
}

void SoundDriver::setMasterPulseWidth(uint8_t pw) {
  Serial.write(0x00);
  Serial.write((uint8_t)masterPulsewidth);
  Serial.write(pw);
}
