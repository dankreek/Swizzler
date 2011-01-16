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
#include "RingBuffer.cpp"

class Sound {
public:
  // The number of voices to output
  static const uint8_t numVoices=3;

  // Initialize the sound module
  static void init();

  // Initialize all the noise-making parts of the chip
  static void initSound();

  // The main thread loop
  static void mainLoop();

  // This chip's TWI slave address
//  static const uint8_t twiSlaveAddress = 0x70;
//
//  // Buffer where the incoming TWI data is stored
//  static const uint8_t twiBufferSize = 64;
//  static uint8_t twiData[twiBufferSize];
//
//  // Ring buffer wrapper around the twiData array
//  static RingBuffer<uint8_t> twiInputBuffer;

  // This number is incremented every millisecond
  volatile static uint16_t  msCounter;

  // The one envelope generator to bind them all
  static Envelope envelope;

  // All the voices to be mixed and output
  static Voice voices[numVoices];

  static uint8_t masterVolume;

private:
  // Reset each voice to power-on defaults
  static void initVoices();
};

#endif /* SOUND_H_ */
