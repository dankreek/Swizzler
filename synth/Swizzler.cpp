/*
 * Swizzler.cpp
 *
 *  Created on: Jan 31, 2010
 *      Author: justin
 */
#include "Swizzler.h"
#include "PresetManager.h"

SoundDriver Swizzler::soundChip = SoundDriver(0x70);

void Swizzler::init() {
  pinMode(ledPin, OUTPUT);

  //Wire.begin();
  //soundChip.resetSound();

  // 31.250kbps is the speed a which MIDI travels in a vacuum.
  Serial.begin(31250);

  // Generate wavetables
  //Wavetable::init();

  // Initialize MIDI input
  //MidiInput::init();

  // Initialize the Note Manager
  //NoteManager::init();

  // Initialize Frequency Manager
  //FrequencyManager::init();

  // Initialize the surface controls
  //SurfaceControlManager::init();

  // Reset all presets
  /*
  for (int i=0; i < 128; i++) {
          PresetManager::curPreset = i;
          PresetManager::storePreset();
  }
  */

  // Begin with initial preset of 0
  //PresetManager::loadPreset(0);

  // Turn the on-board LED off
  digitalWrite(ledPin, HIGH);
}

/**
 * This is the non-ending loop, essentially it contains the lowest priority
 * tasks which are constantly being interrupted by the frequency-keeping and
 * time-keeping ISR's.
 */
void Swizzler::mainLoop() {
  while (true) {
    // Shove everything that's read by the serial port into the MIDI input
    if (Serial.available() > 0) {
      digitalWrite(13, LOW);
      delay(250);
      digitalWrite(13, HIGH);
      delay(100);
      //MidiInput::pushByte(Serial.read());
      byte a = Serial.read();
    }

  }
}

/*
void Swizzler::setErrorState() {
	while (true) {
		digitalWrite(ledPin, 0);
	}
}
*/

Swizzler swizzler = Swizzler();
