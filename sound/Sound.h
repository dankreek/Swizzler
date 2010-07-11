/*
 * Sound.h
 *
 *  Created on: Jul 10, 2010
 *      Author: justin
 */

#ifndef SOUND_H_
#define SOUND_H_

#include "PwmOut.h"
#include "Voice.h"

class Sound {
public:
  // Initialize the sound module
  static void init();

  // Enter the main loop
  static void mainLoop();

  // This number is incremented every millisecond
  volatile static uint8_t  msCounter;

  // The number of voices to output
  static const uint8_t numVoices=3;

  // All the voices to be mixed and output
  static Voice voices[numVoices];
};

#endif /* SOUND_H_ */
