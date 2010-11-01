/*
 * DisplayOutput.cpp
 *
 *  Created on: Jul 7, 2010
 *      Author: justin
 */

#include "DisplayOutput.h"
#include "Swizzler.h"
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/eeprom.h>

uint8_t EEMEM DisplayOutput::eepromstring1[]={"   Welcome To\n    Swizzler"};

void DisplayOutput::init() {
  setAutowrap(true);
  clearDisplay();

  printEepromString(eepromstring1);
}

void DisplayOutput::putChar(uint8_t c) {
  Wire.beginTransmission(twiAddress);
  Wire.send(c);
  Wire.endTransmission();
}

void DisplayOutput::printEepromString(uint8_t *eepromStrPtr) {
//  readString(eepromStrPtr, strBuffer);
//  print((char*)strBuffer);

  uint8_t *cPtr = eepromStrPtr;
  Wire.beginTransmission(twiAddress);
  uint8_t c; // = eeprom_read_byte(cPtr);
  eeprom_read_block(&c, cPtr, 1);
  while(c != 0) {
    Wire.send(c);
    cPtr++;
    eeprom_busy_wait();
    eeprom_read_block(&c, cPtr, 1);
  }
  Wire.endTransmission();
  _delay_ms(5);
}

void DisplayOutput::readString(uint8_t *eepromAddy, uint8_t *sramAddy) {
  uint8_t i=0;

  do {
    sramAddy[i] = eeprom_read_byte(&eepromAddy[i]);
    eeprom_busy_wait();
    i++;
  } while (sramAddy[i-1] != 0);
}

void DisplayOutput::print(char s[]) {
  char* c;

  Wire.beginTransmission(twiAddress);
  for (c=s; *c; c++) {
    Wire.send(*c);
  }
  Wire.endTransmission();
  _delay_ms(5);
}

void DisplayOutput::clearDisplay() {
  sendCommand(clearHome);
}

void DisplayOutput::setAutowrap(bool onOff) {
  sendCommand(onOff ? autoWrapOn : autoWrapOff);
}

void DisplayOutput::sendCommand(DiplayCommand cmd) {
  Wire.beginTransmission(twiAddress);
  Wire.send(commandByte);
  Wire.send(cmd);
  Wire.endTransmission();
  _delay_ms(5);
}
