/*
 * DisplayOutput.h
 *
 *  Created on: Jul 7, 2010
 *      Author: justin
 */

#ifndef DISPLAYOUTPUT_H_
#define DISPLAYOUTPUT_H_


#include "ITimerCall.h"
#include <inttypes.h>
#include <stdio.h>
#include <avr/eeprom.h>

class DisplayDriver  {
public:
  static void init();

  // These functions print directly to the display
  static void putChar(uint8_t c);
  static void printMem(uint8_t*, uint8_t len);

  // Display commands
  static void clearDisplay();
  static void setAutoScroll(bool onOff);
  static void setAutowrap(bool onOff);
  static void moveCursor(uint8_t col, uint8_t row);

private:
  static const uint8_t twiAddress = 0x69;
  static const uint8_t commandByte = 0xfe;

  static const uint8_t twiDelay = 100;  // Time to wait after sending twi data (in microseconds)

  static uint8_t greetingString[];

  enum DiplayCommand {
    autoScrollOn = 0x51,
    autoScrollOff = 0x52,
    clearHome = 0x58,
    autoWrapOn  = 0x43,
    autoWrapOff = 0x44,
    setCursorPosition = 0x47
  };

  static void sendCommand(DiplayCommand cmd);

};

#endif /* DISPLAYOUTPUT_H_ */
