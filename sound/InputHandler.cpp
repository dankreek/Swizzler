/*
 * InputHandler.cpp
 *
 *  Created on: Jul 17, 2010
 *      Author: justin
 */

#include "InputHandler.h"
#include "Sound.h"

InputHandler::State InputHandler::state;
uint8_t InputHandler::commandVoiceNumber;
InputHandler::GlobalCommand InputHandler::globalCommand;
InputHandler::VoiceCommand InputHandler::voiceCommand;
uint8_t InputHandler::commandData[2];
uint8_t InputHandler::commandDataSize;


void InputHandler::init() {
  state = readingVoiceNumber;
  commandDataSize = 0;
}

void InputHandler::handleInput(uint8_t data) {
  switch (state) {
    case readingVoiceNumber:
      handleReadingVoiceNumber(data);
      return;
    case readingCommandType:
      handleReadingCommandType(data);
      return;
    case readingCommandData:
      handleReadingCommandData(data);
      return;
  }
}

void InputHandler::handleReadingVoiceNumber(uint8_t data) {
  commandVoiceNumber = data;
  state = readingCommandType;
}

void InputHandler::handleReadingCommandType(uint8_t data) {
  // This is a global command
  if (commandVoiceNumber == 0)
    globalCommand = (GlobalCommand)data;
  // This is a voice command
  else
    voiceCommand = (VoiceCommand)data;

  state = readingCommandData;
}

void InputHandler::handleReadingCommandData(uint8_t data) {
  // Safety valve
  if (commandDataSize >= maxCommandDataSize) {
    resetCommand();
    return;
  }

  commandData[commandDataSize] = data;
  commandDataSize++;

  if (commandVoiceNumber == 0) handleGlobalCommand();
  else handleChannelCommand();
}

void InputHandler::handleGlobalCommand() {
  // Check and see if a 1 byte command needs execution
  if (commandDataSize == 1) {
    switch (globalCommand) {
      case setMasterVolume:
        Sound::masterVolume = commandData[0];
        break;
      case setFilterCutoff:
        // Not implemented yet
        break;
      default:
        // Not a 1 byte command
        return;
    }

    // Reset a command since a command was executed successfully
    resetCommand();
  }
}

void InputHandler::handleChannelCommand() {
  if (!checkVoiceNumber(commandVoiceNumber-1)) return;

  if (commandDataSize == 1) {
    switch (voiceCommand) {
      case setVolume:
        setVoiceVolume(commandVoiceNumber-1, commandData[0]);
        break;
      case setWaveform:
        setVoiceWaveform(commandVoiceNumber-1, commandData[0]);
        break;
      case setSustainLevel:
        setVoiceSustain(commandVoiceNumber-1, commandData[0]);
        break;
      case setGateState:
        setVoiceGateState(commandVoiceNumber-1, commandData[0]);
        break;
      case setFilterOnOff:
        setVoiceFilterState(commandVoiceNumber-1, commandData[0]);
        break;
      default:
        return;
    }
  }
  // Look for two byte commands
  else {
    uint16_t data = (commandData[0]<<8) | commandData[1];

    switch (voiceCommand) {
    case setPulseWidth:
      setVoicePulseWidth(commandVoiceNumber-1, data);
      break;
    case setAttackTime:
      setVoiceAttack(commandVoiceNumber-1, data);
      break;
    case setDecayTime:
      setVoiceDecay(commandVoiceNumber-1, data);
      break;
    case setReleaseTime:
      setVoiceRelease(commandVoiceNumber-1, data);
      break;
    default:
      return;
    }
  }

  resetCommand();
}

void InputHandler::resetCommand() {
  state = readingVoiceNumber;
  commandDataSize = 0;
}

void InputHandler::setVoiceVolume(uint8_t voiceNumber, uint8_t volume) {
  Sound::voices[voiceNumber].outputVolume = volume;
}

void InputHandler::setVoiceWaveform(uint8_t voiceNumber, uint8_t waveFormNumber) {
  if (waveFormNumber > 3) return;
  Sound::voices[voiceNumber].waveform.curWaveType = (WaveformType)waveFormNumber;
}

void InputHandler::setVoiceGateState(uint8_t voiceNumber, uint8_t gateState) {
  Sound::voices[voiceNumber].envelope.setGate(gateState == 0 ? false : true);
}

void InputHandler::setVoiceSustain(uint8_t voiceNumber, uint8_t sustainLevel) {
  Sound::voices[voiceNumber].envelope.sustain = (sustainLevel << 8);
}

void InputHandler::setVoiceFilterState(uint8_t voiceNumber, uint8_t filterState) {
  Sound::voices[voiceNumber].isFiltered = (filterState == 0) ? false : true;
}

void InputHandler::setVoiceAttack(uint8_t voiceNumber, uint16_t attackTime) {
  Sound::voices[voiceNumber].envelope.attack = attackTime;
}

void InputHandler::setVoiceDecay(uint8_t voiceNumber, uint16_t decayTime) {
  Sound::voices[voiceNumber].envelope.decay = decayTime;
}

void InputHandler::setVoicePulseWidth(uint8_t voiceNumber, uint16_t pulseWidth) {
  Sound::voices[voiceNumber].waveform.pulseWidth = pulseWidth;
}

void InputHandler::setVoiceRelease(uint8_t voiceNumber, uint16_t releaseTime) {
  Sound::voices[voiceNumber].envelope.release = releaseTime;
}



