#include "SoundDriver.h"

/**
 * Different types of commands available for a voice
 */
enum VoiceCommand {
  setVolume       = 0x00,
  setWaveform     = 0x01,
  setPulseWidth   = 0x02,
  setAttackTime   = 0x03,
  setDecayTime    = 0x04,
  setSustainLevel = 0x05,
  setReleaseTime  = 0x06,
  setGateState    = 0x07,
  setFilterOnOff  = 0x08,
  setFrequency    = 0x09,
  setSlaveSync    = 0x0a
};

SoundDriver::SoundDriver(uint8_t addy) {
  twiAddress = addy;
}

void SoundDriver::setEnvelopeGate(uint8_t voiceNum, bool isClosed) {
  Wire.beginTransmission(this->twiAddress);
  Wire.send(voiceNum+1); 
  Wire.send(setGateState);
  Wire.send(isClosed ? 1 : 0); 
  Wire.endTransmission();
}
