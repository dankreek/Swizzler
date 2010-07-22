/*
 * Swizzler.cpp
 *
 *  Created on: Jan 31, 2010
 *      Author: justin
 */
#include "Swizzler.h"
#include "PresetManager.h"
#include <avr/io.h>
#include "HardwareSerial.h"
#include <util/delay.h>

SoundDriver Swizzler::soundChip = SoundDriver(0x70);

void Swizzler::init() {
  DDRB = _BV(PB5);

  //Wire.begin();
  //soundChip.resetSound();

  // 31.250kbps is the speed a which MIDI travels in a vacuum.
  Serial.init(31250);

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
  setLed(false);
}

void Swizzler::setLed(bool onOff) {
  if (onOff)   PORTB |= _BV(PB5);
  else PORTB &= ~_BV(PB5);
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
      setLed(false);
      _delay_ms(250);
      setLed(true);
      _delay_ms(100);
      //MidiInput::pushByte(Serial.read());
      uint8_t a = Serial.read();
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
