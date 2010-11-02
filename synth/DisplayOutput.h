/*
 * DisplayOutput.h
 *
 *  Created on: Jul 7, 2010
 *      Author: justin
 */

#ifndef DISPLAYOUTPUT_H_
#define DISPLAYOUTPUT_H_

#include "DisplayOutput.h"
#include "Swizzler.h"
#include "RingBuffer.cpp"
#include <inttypes.h>
#include <stdio.h>
#include <avr/eeprom.h>
#include <stdio.h>

class DisplayOutput {
public:
  /**
   * Initialize the display unit and show the power-on greeting
   */
  static void init();

  static void putChar(uint8_t c);
  static void print(char*);

  static void clearDisplay();
  static void setAutowrap(bool onOff);

  static void printEepromString(uint8_t*);

  // Put a char into the printf buffer
  static int putCharBuffered(char ch, FILE *unused);

  // Flushes the printf buffer out to the display
  static void flushPrintfBuffer();

  static void printNumber(uint8_t n);
private:
  static const uint8_t twiAddress = 0x69;
  static const uint8_t commandByte = 0xfe;

  static const uint8_t twiDelay = 130;  // Time to wait after sending twi data (in microseconds)

  static uint8_t greetingString[];

  static const int printfBufferSize = 32;
  static uint8_t printfBufferStorage[printfBufferSize];
  static RingBuffer<uint8_t> printfBuffer;

  enum DiplayCommand {
    clearHome = 0x58,
    autoWrapOn  = 0x43,
    autoWrapOff = 0x44
  };

  static void sendCommand(DiplayCommand cmd);

};

#endif /* DISPLAYOUTPUT_H_ */
