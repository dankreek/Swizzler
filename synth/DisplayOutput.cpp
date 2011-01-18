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

void DisplayOutput::init() {
  clearDisplay();
  setAutoScroll(false);
}

void DisplayOutput::putChar(uint8_t c) {
  Wire.beginTransmission(twiAddress);
  Wire.send(c);
  Wire.endTransmission();
  _delay_us(twiDelay);
}

void DisplayOutput::printMem(uint8_t str[], uint8_t len) {
  Wire.beginTransmission(twiAddress);
  for (uint8_t i=0; i < len; i++) {
    Wire.send(str[i]);
    _delay_us(twiDelay);
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
