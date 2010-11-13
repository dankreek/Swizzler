/*
 * DisplayOutput.h
 *
 *  Created on: Jul 7, 2010
 *      Author: justin
 */

#ifndef DISPLAYOUTPUT_H_
#define DISPLAYOUTPUT_H_


#include "RingBuffer.cpp"
#include <inttypes.h>
#include <stdio.h>
#include <avr/eeprom.h>
#include "Print.h"

class DisplayOutput : public Print {
public:
  static void init();

  static void putChar(uint8_t c);

  static void clearDisplay();
  static void setAutowrap(bool onOff);

  static void printEepromString(uint8_t*);

  // Flushes the output bugger
  static void flush();

  void write(uint8_t);
  using Print::write;
private:
  static const uint8_t twiAddress = 0x69;
  static const uint8_t commandByte = 0xfe;

  static const uint8_t twiDelay = 130;  // Time to wait after sending twi data (in microseconds)

  static uint8_t greetingString[];

  static const int outputBufferSize = 32;
  static uint8_t outputBufferStorage[outputBufferSize];
  static RingBuffer<uint8_t> outputBuffer;

  enum DiplayCommand {
    clearHome = 0x58,
    autoWrapOn  = 0x43,
    autoWrapOff = 0x44
  };

  static void sendCommand(DiplayCommand cmd);

};

#endif /* DISPLAYOUTPUT_H_ */
