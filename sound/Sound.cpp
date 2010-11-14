/*
 * Sound.cpp
 *
 *  Created on: Jul 10, 2010
 *      Author: justin
 */

#include <util/delay.h>
#include <avr/interrupt.h>
#include "Sound.h"
#include "InputHandler.h"
#include "HardwareSerial.h"
#include "Led.h"

Voice Sound::voices[numVoices];
volatile uint16_t Sound::msCounter;
uint8_t Sound::masterVolume;

//#define USE_UART_INPUT

void Sound::init() {
  Led::init();
  Led::setLedOn(false);

  initVoices();

  Waveform::initNoiseGenerator();

  // Start the sound output going
  msCounter = 0;
  PwmOut::init();

  Serial.init(31250);

  Led::setLedOn(true);
}

void Sound::initVoices() {
  masterVolume = 0xff;

  for (int i=0; i < numVoices; i++) {
    voices[i].init();
    voices[i].phaseAccumulator=i*10;
  }
}

void Sound::mainLoop() {
  uint16_t now = 0;

  while (true) {
    // Update the envelopes every millisecond
    if (now != Sound::msCounter) {
      // Service each envelope generator
      for (int i=0; i < numVoices; i++) {
        voices[i].envelope.msTickHandler();
      }

      now = Sound::msCounter;
    }

    // Get data from the TWI interface and pass it into the input handler
#ifdef USE_TWI_INPUT
    while (twiInputBuffer.hasData()) {
      InputHandler::handleInput(twiInputBuffer.get());
    }
#else
    while (Serial.available() > 0) {
      InputHandler::handleInput(Serial.read());
    }
#endif

  }
}
