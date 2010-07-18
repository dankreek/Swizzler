/*
 * InputHandler.h
 *
 *  Created on: Jul 17, 2010
 *      Author: justin
 *
 *  The sound chip's command format works as such:
 *
 *  The first byte is either a 0, which signifies a command that has a global effect
 *  on the chip, or a number 1-8 which signifies a command that has an effect on a
 *  particular voice. All the commands available are as follows:
 *
 *  Global Commands:
 *  ================
 *
 *  Set output volume: 0x00 0x00 <volume>
 *  (NOT YET IMPLEMENTED)
 *  ------------------
 *  Sets the master output volume of the sound chip, where <volume>==0x00 is complete silence
 *  and 0xff is the loudest possible volume. Default is 0xff.
 *
 *  Set filter cutoff frequency: 0x00 0x01 <cutoff>
 *  (NOT YET IMPLEMENTED)
 *  ----------------------------
 *
 *  Voice Commands:
 *  ===============
 *
 *  Set voice volume: <voice number> 0x00 <volume>
 *  -----------------
 *  Sets the output volume of the voice where 0x00 is completely silent and 0xff is fully loud.
 *
 *  Set voice waveform: <voice number> 0x01 <waveform type>
 *  -------------------
 *  Change the waveform of the voice to one of the following waveform types:
 *
 *  0x00 = Triangle wave
 *  0x01 = Square wave
 *  0x02 = Sawtooth
 *  0x03 = Noise (random)
 *
 *  Set voice's square pulse width: <voice number> 0x02 <pulse width high byte> <pulse width low byte>
 *  -------------------------------
 *  Sets the pulse width of the square wave, can be a number between 0x0000 and 0xffff
 *  which signifies the duty cycle of the square wave form. 0x0000 would mean a wave that
 *  is always low, 0xffff would be a wave that's always high, and 0x8000 would be a totally
 *  Symmetrical square wave.
 *
 *  Set voice attack speed: <voice number> 0x03 <attack speed high byte> <attack speed low byte>
 *  -----------------------
 *  Sets the duration of the attack phase of the envelope generator. Which would be the time
 *  starting from when the gate if first closed going to when the envelop reaches max
 *  level. Attack speed is specified in milliseconds.
 *
 *  Set voice decay speed: <voice number> 0x04 <decay speed high byte> <decay speed low byte>
 *  ----------------------
 *  Sets the duration of the envelope generator's decay phase in milliseconds.
 *
 *  Set voice sustain level: <voice number> 0x05 <sustain level>
 *  ------------------------
 *  Sets the envelope generator's sustain level where 0x00 is total silence, and 0xff is maximum volume
 *
 *  Set voice release speed: <voice number> 0x06 <release speed high byte> <release speed low byte>
 *  ------------------------
 *  Sets the duration of the envelope generator's release phase in milliseconds.
 *
 *  Set voice's envelope gate state: <voice number> 0x07 <gate state>
 *  --------------------------------
 *  Set the envelope generator's gate status. 0x00 opens the gate, 0x01 closes the gate.
 *
 *  Turn filter on/off for a voice: <voice number> 0x08 <filter on/off>
 *  (NOT YET IMPLEMENTED)
 *  -------------------------------
 *
 *  Set voice's oscillator frequency: <voice number> 0x09 <frequency high byte> <frequency low byte>
 *  --------------------------------
 *  Set the voice's oscillator frequency (in hz).
 *
 */

#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include <inttypes.h>
#include "Sound.h"

class InputHandler {
public:
  static void init();

  /**
   * Read in a byte from the input stream and interpret it
   */
  static void handleInput(uint8_t i);

  static void setVoiceVolume(uint8_t, uint8_t);
  static void setVoiceWaveform(uint8_t, uint8_t);
  static void setVoiceSustain(uint8_t, uint8_t);
  static void setVoiceGateState(uint8_t, uint8_t);
  static void setVoiceFilterState(uint8_t, uint8_t);

  static void setVoicePulseWidth(uint8_t, uint16_t);
  static void setVoiceAttack(uint8_t, uint16_t);
  static void setVoiceDecay(uint8_t, uint16_t);
  static void setVoiceRelease(uint8_t, uint16_t);
  static void setVoiceFrequency(uint8_t, uint16_t);

private:
  /**
   * Input handler states
   */
  enum State {
    readingVoiceNumber,
    readingCommandType,
    readingCommandData
  };

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
    setFrequency    = 0x09
  };

  /**
   * Different global commands available
   */
  enum GlobalCommand {
    setMasterVolume = 0x00,
    setFilterCutoff = 0x01
  };

  // Current input handler state
  static InputHandler::State state;

  // The current command's voice number (0 = global)
  static uint8_t commandVoiceNumber;

  static GlobalCommand globalCommand;
  static VoiceCommand voiceCommand;

  // Each commands data gets put here (2 bytes is the max command data size right now)
  static const uint8_t maxCommandDataSize = 2;
  static uint8_t commandData[maxCommandDataSize];
  static uint8_t commandDataSize;

  static void handleReadingVoiceNumber(uint8_t data);
  static void handleReadingCommandType(uint8_t data);
  static void handleReadingCommandData(uint8_t data);
  static void handleGlobalCommand();
  static void handleChannelCommand();

  // This is called when a command has been executed, or determined invalid and thrown out
  // and a new command
  static void resetCommand();

  // Simple functin to check and see if a voice number is in range
  static bool checkVoiceNumber(uint8_t voiceNumber);
};

inline bool InputHandler::checkVoiceNumber(uint8_t voiceNumber) {
  return (voiceNumber < Sound::numVoices);
}

#endif /* INPUTHANDLER_H_ */
