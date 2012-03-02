/** @file MidiInput.cpp
 */

#include <inttypes.h>
#include "MidiInput.h"
#include "Swizzler.h"
#include "PresetManager.h"
#include "MidiControllerMapping.h"

ANoteReceiver *MidiInput::noteReceiver;
void (*MidiInput::pitchBendEventHandler)();

int16_t MidiInput::pitchbendAmount;
int16_t MidiInput::midiCmd;
int16_t MidiInput::midiData1;
int16_t MidiInput::midiData2;

void MidiInput::handleNoteOn() {
  /**
   * Most MIDI input devices send a NOTE ON message with a velocity of 0
   * to signal the note ending.
   */
  if (midiData2 == 0) noteReceiver->noteOff(midiData1);
  else noteReceiver->noteOn(midiData1, midiData2);
}

void MidiInput::handleNoteOff() {
  noteReceiver->noteOff(midiData1);
}

void MidiInput::init() {
  pitchbendAmount=0;
  midiCmd=-1;
  midiData1=-1;
  midiData2=-1;
}

void MidiInput::handlePitchBend() {
  // I'm going to ignore the least significant byte of this message for now
  // (my controller only sends 0 for the LSB anyway, so who cares)
  // This number comes in as an unsigned 7bit number, but internally I store it
  // as a signed 7 bit number. The -64 is to convert to signed.
  //OscillatorMux::setBendAmount((int8_t)midiData2-64);
  pitchbendAmount = (int16_t)midiData2-64;
  pitchBendEventHandler();
}

// Launch a controller change hook
void MidiInput::handleControlChange() {
  MidiControllerMapping::executeController(midiData1, midiData2);
}

// TODO : Make this function a statically compiled reference in MidiControllerMapping
void MidiInput::handleProgramChange() {
  PresetManager::loadPreset(midiData1);
}
