/*
 * Swizzler.cpp
 *
 *  Created on: Jan 31, 2010
 *      Author: justin
 */

#include "Oscillators.h"
#include "Swizzler.h"
#include "PresetManager.h"
#include <avr/io.h>
#include "HardwareSerial.h"
#include "Timer.h"
#include <util/delay.h>
#include <avr/interrupt.h>

SineGenerator Swizzler::freqModSineWave;
EnvelopeNoteFilter Swizzler::envelopeController;
ArpeggiatorNoteFilter Swizzler::arp;
Oscillators Swizzler::oscillators;
uint16_t Swizzler::portamentoTime;

SoundDriver Swizzler::soundChip = SoundDriver(0x70);
uint16_t Swizzler::msCounter = 0;

void Swizzler::handlePitchBend() {
  oscillators.updateFrequencies();
}

void Swizzler::enableArpeggio(bool onOff) {
  if (onOff) MidiInput::noteReceiver = &arp;
  else MidiInput::noteReceiver = &envelopeController;
}

void Swizzler::init() {
  portamentoTime = 100;

  freqModSineWave.setFrequency(0);

  // Setup chain
  MidiInput::pitchBendEventHandler = Swizzler::handlePitchBend;
  enableArpeggio(false);
  //MidiInput::noteReceiver = &envelopeController;
  //MidiInput::noteReceiver = &arp;

  //  MidiInput::noteReceiver points to whichever one of these is controlling the notes and envelope
  envelopeController.linkTo(&oscillators);
  arp.linkTo(&oscillators);

  // Setup the first note receiver
  //MidiInput::noteReceiver = &noteManager;


  // Set the LED pin to output
  DDRB = _BV(PB5);

  // 31.250kbps is the speed a which MIDI travels in a vacuum.
  Serial.init(31250);

  // Generate wavetables
  //Wavetable::init();

  // Initialize MIDI input
  MidiInput::init();

  // Initialize the Note Manager
  //NoteManager::init();

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

  // Turn on interrupts (let the games begin)

  //Wire.begin();
  Timer::init();

  //soundChip.resetSound();

  setLed(false);
}

void Swizzler::setLed(bool onOff) {
  if (!onOff)
    PORTB |= _BV(PB5);
  else
    PORTB &= ~_BV(PB5);
}

/**
 * This is the non-ending loop, essentially it contains the lowest priority
 * tasks which are constantly being interrupted by the time-keeping and TWI
 * ISR.
 */
void Swizzler::mainLoop() {
  uint16_t lastMs=msCounter;

  while (true) {
    // Only call these services once every millisecond
    if (lastMs != msCounter) {
      lastMs = msCounter;
      oscillators.nextTick();
      arp.nextTick();
      freqModSineWave.nextTick();
    }

    // Shove everything that's read by the serial port into the MIDI input
    while (Serial.available() > 0) {
      MidiInput::pushByte(Serial.read());
    }

  }
}

void Swizzler::setErrorState() {
  // Turn off interrupts and just blink the LED
  cli();
  while (true) {
    setLed(true);
    _delay_ms(1000);
    setLed(false);
    _delay_ms(500);
  }
}

Swizzler swizzler = Swizzler();
