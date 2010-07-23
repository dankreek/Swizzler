/*
 * Sound.cpp
 *
 *  Created on: Jul 10, 2010
 *      Author: justin
 */

#include <util/delay.h>
#include "Sound.h"
#include "InputHandler.h"

Voice Sound::voices[numVoices];
volatile uint16_t Sound::msCounter;
uint8_t Sound::masterVolume;

// Needed for the TWI slave input data
uint8_t Sound::twiData[twiBufferSize];
RingBuffer<uint8_t> Sound::twiInputBuffer(twiData, twiBufferSize);

void Sound::init() {
  initVoices();

  Waveform::initNoiseGenerator();

  // Start the sound output going
  msCounter = 0;
  PwmOut::init();

  // Start up the TWI bus
  twi.init(twiSlaveAddress, &twiInputBuffer);
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
    while (twiInputBuffer.hasData()) {
      InputHandler::handleInput(twiInputBuffer.get());
    }


  }
}
