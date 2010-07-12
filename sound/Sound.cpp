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
  msCounter = 0;
  PwmOut::init();
}

void Sound::mainLoop() {
  // Output a triangle wave a 440hz as a demo
  voices[0].envelope.attack = 250;
  voices[0].envelope.decay = 250;
  voices[0].envelope.sustain = 128<<8;
  voices[0].envelope.release = 1000;

  voices[0].setFrequency(440);
  voices[0].waveform.setWaveform(sawtoothWave);

  voices[1].envelope.attack = 250;
  voices[1].envelope.decay = 250;
  voices[1].envelope.sustain = 128<<8;
  voices[1].envelope.release = 100;

  voices[1].setFrequency(523);
  voices[1].waveform.setWaveform(sawtoothWave);

  voices[0].envelope.setGate(true);

  uint16_t now = Sound::msCounter;
  while (true) {
    if (msCounter == 500) voices[1].envelope.setGate(true);

    if (msCounter == 1000) voices[0].envelope.setGate(false);

    if (msCounter == 2000) voices[1].envelope.setGate(false);

    // Service each envelope generator
    for (int i=0; i < numVoices; i++) {
      voices[i].envelope.msTickHandler();
    }

    // Wait for a full millisecond to go by before looping again
    while (now == Sound::msCounter);
    now = Sound::msCounter;
  }
}
