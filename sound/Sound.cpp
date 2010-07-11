/*
 * Sound.cpp
 *
 *  Created on: Jul 10, 2010
 *      Author: justin
 */

#include "Sound.h"
#include <util/delay.h>

Voice Sound::voices[Sound::numVoices];
volatile uint16_t Sound::msCounter;

void Sound::init() {
  // Draw and initialize all wave forms
  Waveform::init();

  // Initialize each voice
  for (int i=0; i < numVoices; i++) {
    voices[i].init();
  }

  // Start the sound output going
  PwmOut::init();
}

void Sound::mainLoop() {
  // Output a triangle wave a 440hz as a demo
  voices[0].envelope.attack = 2000;
  voices[0].envelope.decay = 2000;
  voices[0].envelope.sustain = 0;
  voices[0].envelope.release = 100;

  voices[0].setFrequency(440);
  voices[0].waveform.setWaveform(squareWave);

  voices[0].envelope.setGate(true);

  while (true) {
    uint16_t now = Sound::msCounter;

    // Service each envelope generator
    for (int i=0; i < numVoices; i++) {
      voices[i].envelope.msTickHandler();
    }

    // Wait for a full millisecond to go by before looping again
    while(now == Sound::msCounter) {}

    if (msCounter == 1000) voices[0].envelope.setGate(false);
  }
}
