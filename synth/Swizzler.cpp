/** @file Swizzler.cpp
 *  @date Jan 31, 2010
 */

#include "Oscillators.h"
#include "Swizzler.h"
#include "PresetManager.h"
#include <avr/io.h>
#include "HardwareSerial.h"
#include "Timer.h"
#include <util/delay.h>
#include <avr/interrupt.h>


LfoController Swizzler::lfoController;
ArpeggiatorNoteFilter Swizzler::arp;
Oscillators Swizzler::oscillators;
uint16_t Swizzler::portamentoTime;
FreqFilterChain Swizzler::freqModEffectChain;
int16_t Swizzler::bendRange;
uint8_t Swizzler::modWheelLevel;

SoundDriver Swizzler::soundChip = SoundDriver(0x70);
uint16_t Swizzler::tickCounter = 0;

void Swizzler::handlePitchBend() {
  freqModEffectChain.update();
}

void Swizzler::enableArpeggio(bool onOff) {
//  if (onOff) MidiInput::noteReceiver = &arp;
//  else MidiInput::noteReceiver = &envelopeController;
  arp.setBypass(!onOff);
}

void Swizzler::init() {
  setLed(false);

  bendRange = 64;
  portamentoTime = 100;
  lfoController.sinGenerator.setFrequency(60);
  MidiInput::pitchBendEventHandler = Swizzler::handlePitchBend;
  modWheelLevel = 0;
  arp.setBypass(true);

  // Setup note filter chain
  MidiInput::noteReceiver = &arp;
//  arp.linkTo(&oscillators);
  arp.linkTo(&freqModEffectChain);
  freqModEffectChain.linkTo(&oscillators);

  // Set the LED pin to output
  DDRB = _BV(PB5);

  // 31.250kbps is the speed a which MIDI travels in a vacuum.
  Serial.init(31250);

  // Initialize MIDI input
  MidiInput::init();

  // Reset all presets
  /*
  for (int i=0; i < 128; i++) {
          PresetManager::curPreset = i;
          PresetManager::storePreset();
  }
  */

  // Begin with initial preset of 0
  //PresetManager::loadPreset(0);

  Wire.begin();
  Timer::init();

  // Wait for display to power up
  _delay_ms(poweronDisplayDelay);

  // Initialize the surface controls
  SurfaceControlManager::init();

  soundChip.reset();

  SurfaceControlManager::displayOut.isOutputOn = false;
  PresetManager::loadPreset(0);
  SurfaceControlManager::displayGreeting();
  SurfaceControlManager::displayOut.isOutputOn = true;

//  PresetManager::setFactoryDefaults();

  setLed(true);
}

void Swizzler::setLed(bool onOff) {
  if (onOff) {
    PORTB |= _BV(PB5);
  } else {
    PORTB &= ~_BV(PB5);
  }
}

/**
 * This is the non-ending loop, essentially it contains the lowest priority
 * tasks which are constantly being interrupted by the time-keeping and TWI
 * ISR.
 */
void Swizzler::mainLoop() {
  uint16_t lastMs=tickCounter;

  while (true) {
    // Only call these services once every millisecond
    if (lastMs != tickCounter) {
      lastMs = tickCounter;

      if ((tickCounter % 2) == 0) {
        lfoController.nextTick();
        freqModEffectChain.nextTick();
        arp.nextTick();
        SurfaceControlManager::displayOut.nextTick();
      }
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
