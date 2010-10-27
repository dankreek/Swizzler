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

uint8_t EEMEM DisplayOutput::eepromstring1[]={"   Welcome To\n"};
uint8_t EEMEM DisplayOutput::eepromstring2[]={"    Swizzler"};

uint8_t DisplayOutput::strBuffer[17];

void DisplayOutput::init() {
  setAutowrap(true);
  clearDisplay();


  printEepromString(eepromstring1);
  printEepromString(eepromstring2);

//  print("   Welcome To\n");
//  print("    Swizzler");
}

void DisplayOutput::putChar(uint8_t c) {
  Wire.beginTransmission(twiAddress);
  Wire.send(c);
  Wire.endTransmission();
}

void DisplayOutput::printEepromString(uint8_t *eepromStrPtr) {
  readString(eepromStrPtr, strBuffer);
  print((char*)strBuffer);
}

void DisplayOutput::readString(uint8_t *eepromAddy, uint8_t *sramAddy) {
  uint8_t i=0;

  do {
    sramAddy[i] = eeprom_read_byte(&eepromAddy[i]);
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
