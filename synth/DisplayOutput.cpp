/*
 * DisplayOutput.cpp
 *
 *  Created on: Jul 7, 2010
 *      Author: justin
 */

#include "DisplayOutput.h"
#include "Swizzler.h"
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/eeprom.h>


TimedLineBuffer DisplayOutput::lineBuffer1 = TimedLineBuffer(0);
TimedLineBuffer DisplayOutput::lineBuffer2 = TimedLineBuffer(1);

uint8_t EEMEM DisplayOutput::greetingString[]={"   Welcome To\n    Swizzler"};

char buf[17];

void DisplayOutput::init() {
  clearDisplay();
  setAutoScroll(false);

  printEepromString(greetingString);
}

void DisplayOutput::putChar(uint8_t c) {
  Wire.beginTransmission(twiAddress);
  Wire.send(c);
  Wire.endTransmission();
  _delay_us(twiDelay);
}

void DisplayOutput::printString(char str[]) {
  Wire.beginTransmission(twiAddress);
  for (uint8_t i=0; str[i] != 0; i++) {
    Wire.send(str[i]);
    _delay_us(twiDelay);
  }
  Wire.endTransmission();
}

void DisplayOutput::printEepromString(uint8_t *eepromStrPtr) {
  Wire.beginTransmission(twiAddress);
  uint8_t b = eeprom_read_byte(eepromStrPtr);
  while (b != 0) {
    Wire.send(b); _delay_us(twiDelay);
    eepromStrPtr++;
    b = eeprom_read_byte(eepromStrPtr);
  }
  Wire.endTransmission();
}

void DisplayOutput::clearDisplay() {
  sendCommand(clearHome);
}

void DisplayOutput::setAutowrap(bool onOff) {
  sendCommand(onOff ? autoWrapOn : autoWrapOff);
}

void DisplayOutput::setAutoScroll(bool onOff) {
  sendCommand(onOff ? autoScrollOn : autoScrollOff);
}

void DisplayOutput::moveCursor(uint8_t col, uint8_t row) {
  Wire.beginTransmission(twiAddress);
  Wire.send(commandByte);       _delay_us(twiDelay);
  Wire.send(setCursorPosition); _delay_us(twiDelay);
  Wire.send(col);               _delay_us(twiDelay);
  Wire.send(row);               _delay_us(twiDelay);
  Wire.endTransmission();
}

void DisplayOutput::sendCommand(DiplayCommand cmd) {
  Wire.beginTransmission(twiAddress);
  Wire.send(commandByte); _delay_us(twiDelay);
  Wire.send(cmd);         _delay_us(twiDelay);
  Wire.endTransmission();
}
