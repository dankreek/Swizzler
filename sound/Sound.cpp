/*
 * Sound.cpp
 *
 *  Created on: Jul 10, 2010
 *      Author: justin
 */

#include <util/delay.h>
#include "Sound.h"
#include "InputHandler.h"
#include "HardwareSerial.h"

Voice Sound::voices[numVoices];
volatile uint16_t Sound::msCounter;
uint8_t Sound::masterVolume;

//#define USE_TWI_INPUT

#ifdef USE_TWI_INPUT
// Needed for the TWI slave input data
uint8_t Sound::twiData[twiBufferSize];
RingBuffer<uint8_t> Sound::twiInputBuffer(twiData, twiBufferSize);
#endif

void Sound::init() {
  initVoices();

  Waveform::initNoiseGenerator();

  // Start the sound output going
  msCounter = 0;
  PwmOut::init();

  // Start up the TWI bus
#ifdef USE_TWI_INPUT
  twi.init(twiSlaveAddress, &twiInputBuffer);
#else
  Serial.init(31250);
#endif
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
