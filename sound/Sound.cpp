/*
 * Sound.cpp
 *
 *  Created on: Jul 10, 2010
 *      Author: justin
 */

#include "Sound.h"

Voice Sound::voices[Sound::numVoices];
volatile uint8_t Sound::msCounter;

void Sound::init() {
  // Initialize each voice
  for (int i=0; i < numVoices; i++) {
    voices[i].init();
  }

  // Start the sound output going
  PwmOut::init();
}

void Sound::mainLoop() {
  while (true) {
    uint8_t now = Sound::msCounter;

    // Service each envelope generator
    for (int i=0; i < numVoices; i++) {
      voices[i].envelope.msTickHandler();
    }

    // Wait for a full millisecond to go by before looping again
    while(now == Sound::msCounter) {}
  }
}
