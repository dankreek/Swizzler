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
#include <inttypes.h>
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

private:
  static const uint8_t twiAddress = 0x69;
  static const uint8_t commandByte = 0xfe;

  enum DiplayCommand {
    clearHome = 0x58,
    autoWrapOn  = 0x43,
    autoWrapOff = 0x44
  };

  static void sendCommand(DiplayCommand cmd);

};

#endif /* DISPLAYOUTPUT_H_ */
