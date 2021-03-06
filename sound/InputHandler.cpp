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
  if (commandVoiceNumber == 0) {
    globalCommand = (GlobalCommand)data;

    // This is the only command with no data
    if (globalCommand == resetVoices) {
      Sound::initSound();
      resetCommand();
      return;
    }
  }
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
      case setGlobalGateState:
        Sound::envelope.setGate( (commandData[0] > 0) ? true : false);
        break;
      case setGlobalSustain:
        setSustain(commandData[0]);
        break;
      case setMasterVolume:
        Sound::masterVolume = commandData[0];
        break;
      case setFilterCutoff:
        // Not implemented yet
        break;
      case setGlobalPulsewidth:
        for (uint8_t i=0; i < Sound::numVoices; i++) setVoicePulseWidth(i, commandData[0]<<8);
        break;

      default:
        // Not a 1 byte command
        return;
    }

    // Reset a command since a command was executed successfully
    resetCommand();
  }
  else if (commandDataSize == 2) {
    uint16_t data = (commandData[0]<<8) | commandData[1];

    switch (globalCommand) {
      case setGlobalAttack:
        setAttack(data);
        break;
      case setGlobalDecay:
        setDecay(data);
        break;
      case setGlobalRelease:
        setRelease(data);
        break;
    }

    resetCommand();
  }
}

void InputHandler::handleChannelCommand() {
  if (!checkVoiceNumber(commandVoiceNumber-1)) return;

  if (commandDataSize == 1) {
    switch (voiceCommand) {
      case setPulseWidth:
        setVoicePulseWidth(commandVoiceNumber-1, commandData[0]<<8);
        break;
      case setVolume:
        setVoiceVolume(commandVoiceNumber-1, commandData[0]);
        break;
      case setWaveform:
        setVoiceWaveform(commandVoiceNumber-1, commandData[0]);
        break;
      case setFilterOnOff:
        setVoiceFilterState(commandVoiceNumber-1, commandData[0]);
        break;
      case setSlaveSync:
        setVoiceSlaveSync(commandVoiceNumber-1, commandData[0]);
      default:
        return;
    }
  }
  // Look for two byte commands
  else {
    uint16_t data = (commandData[0]<<8) | commandData[1];

    switch (voiceCommand) {
    case setFrequency:
      setVoiceFrequency(commandVoiceNumber-1, data);
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
  // The spec lists voice volume as an 8-bit number, but internally
  // I'm only using 5-bit resolution
  Sound::voices[voiceNumber].outputVolume = volume >> (8-Voice::outputVolumeResolution);
}

void InputHandler::setVoiceWaveform(uint8_t voiceNumber, uint8_t waveFormNumber) {
  //if (waveFormNumber > 5) return;
  Sound::voices[voiceNumber].waveform.curWaveType = (WaveformType)waveFormNumber;
}

void InputHandler::setGateState(uint8_t gateState) {
  Sound::envelope.setGate(gateState == 0 ? false : true);
}

void InputHandler::setSustain(uint8_t sustainLevel) {
  Sound::envelope.sustain = (sustainLevel << 7)|0x7f;
}

void InputHandler::setVoiceFilterState(uint8_t voiceNumber, uint8_t filterState) {
  Sound::voices[voiceNumber].isFiltered = (filterState == 0) ? false : true;
}

void InputHandler::setVoiceSlaveSync(uint8_t voiceNumber, uint8_t slaveSyncVoice) {
  Sound::voices[voiceNumber].slaveSyncVoice = slaveSyncVoice;
}

void InputHandler::setAttack(uint16_t attackTime) {
  Sound::envelope.attack = attackTime;
}

void InputHandler::setDecay(uint16_t decayTime) {
  Sound::envelope.decay = decayTime;
}

void InputHandler::setVoicePulseWidth(uint8_t voiceNumber, uint16_t pulseWidth) {
  Sound::voices[voiceNumber].waveform.pulseWidth = pulseWidth;
}

void InputHandler::setRelease(uint16_t releaseTime) {
  Sound::envelope.release = releaseTime;
}

void InputHandler::setVoiceFrequency(uint8_t voiceNumber, uint16_t frequency) {
  Sound::voices[voiceNumber].setFrequency(frequency);
}

