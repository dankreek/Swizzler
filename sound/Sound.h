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
#include "TwoWireSlave.h"
#include "RingBuffer.cpp"

class Sound {
public:
  // Initialize the sound module
  static void init();

  // The main thread loop
  static void mainLoop();

  // This chip's TWI slave address
  static const uint8_t twiSlaveAddress = 0x70;

  // Buffer where the incoming TWI data is stored
  static const uint8_t twiBufferSize = 64;
  static uint8_t twiData[twiBufferSize];

  // Ring buffer wrapper around the twiData array
  static RingBuffer<uint8_t> twiInputBuffer;

  // This number is incremented every millisecond
  volatile static uint16_t  msCounter;

  // The number of voices to output
  static const uint8_t numVoices=8;

  // All the voices to be mixed and output
  static Voice voices[numVoices];

  static uint8_t masterVolume;
};

#endif /* SOUND_H_ */
