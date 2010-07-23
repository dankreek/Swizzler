#include "SoundDriver.h"

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
  resetVoices     = 0x00
};

SoundDriver::SoundDriver(uint8_t addy) {
  twiAddress = addy;
}

void SoundDriver::setFrequency(uint8_t voiceNum, uint16_t freq) {
  Wire.beginTransmission(this->twiAddress);
  Wire.send(voiceNum+1);
  Wire.send((uint8_t)setVoiceFrequency);
  Wire.send((uint8_t)(freq>>8));
  Wire.send((uint8_t)(freq&0xff));
  Wire.endTransmission();
}

void SoundDriver::setEnvelopeGate(uint8_t voiceNum, bool isClosed) {
  Wire.beginTransmission(this->twiAddress);
  Wire.send(voiceNum+1); 
  Wire.send((uint8_t)setGateState);
  Wire.send((uint8_t)isClosed ? 1 : 0);
  Wire.endTransmission();
}

void SoundDriver::resetSound() {
  Wire.beginTransmission(this->twiAddress);
  Wire.send(0x00);
  Wire.send(0x00);
  Wire.endTransmission();
}

void SoundDriver::setVoiceLevel(uint8_t voiceNum, uint8_t level) {
  Wire.beginTransmission(this->twiAddress);
  Wire.send(voiceNum+1);
  Wire.send((uint8_t)setVolume);
  Wire.send(level);
  Wire.endTransmission();
}

void SoundDriver::setWaveform(uint8_t voiceNum, WaveformType waveform) {
 Wire.beginTransmission(this->twiAddress);
 Wire.send(voiceNum+1);
 Wire.send((uint8_t)setVoiceWaveform);
 Wire.send((uint8_t)waveform);
 Wire.endTransmission();
}

void SoundDriver::setAttackTime(uint8_t voiceNum, uint16_t attackTime) {
  Wire.beginTransmission(this->twiAddress);
  Wire.send(voiceNum+1);
  Wire.send((uint8_t)setVoiceAttackTime);
  Wire.send((uint8_t)(attackTime>>8));
  Wire.send((uint8_t)(attackTime&0xff));
  Wire.endTransmission();
}

void SoundDriver::setDecayTime(uint8_t voiceNum, uint16_t decayTime) {
  Wire.beginTransmission(this->twiAddress);
  Wire.send(voiceNum+1);
  Wire.send((uint8_t)setVoiceDecayTime);
  Wire.send((uint8_t)(decayTime>>8));
  Wire.send((uint8_t)(decayTime&0xff));
  Wire.endTransmission();
}

void SoundDriver::setReleaseTime(uint8_t voiceNum, uint16_t releaseTime) {
  Wire.beginTransmission(this->twiAddress);
  Wire.send(voiceNum+1);
  Wire.send((uint8_t)setVoiceReleaseTime);
  Wire.send((uint8_t)(releaseTime>>8));
  Wire.send((uint8_t)(releaseTime&0xff));
  Wire.endTransmission();
}

void SoundDriver::setSustainLevel(uint8_t voiceNum, uint8_t sustainLevel) {
  Wire.beginTransmission(this->twiAddress);
  Wire.send(voiceNum+1);
  Wire.send((uint8_t)setVoiceSustainLevel);
  Wire.send(sustainLevel);
  Wire.endTransmission();
}

void SoundDriver::setPuleseWidth(uint8_t voiceNum, uint16_t pw) {
  Wire.beginTransmission(this->twiAddress);
  Wire.send(voiceNum+1);
  Wire.send((uint8_t)setVoicePulseWidth);
  Wire.send((uint8_t)(pw >> 8));
  Wire.send((uint8_t)(pw & 0xff));
  Wire.endTransmission();
}
