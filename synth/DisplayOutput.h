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
#include <avr/eeprom.h>

extern uint8_t *eepromstring1;
extern uint8_t *eepromstring2;


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
  static void printEepromString(uint8_t*);
  static void readString(uint8_t* eeprom, uint8_t* sram);

  static uint8_t strBuffer[];

  static const uint8_t twiAddress = 0x69;
  static const uint8_t commandByte = 0xfe;

  static uint8_t eepromstring1[];
  static uint8_t eepromstring2[];

  enum DiplayCommand {
    clearHome = 0x58,
    autoWrapOn  = 0x43,
    autoWrapOff = 0x44
  };

  static void sendCommand(DiplayCommand cmd);

};

#endif /* DISPLAYOUTPUT_H_ */
