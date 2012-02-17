/** @file DisplayDriver.cpp
 *
 *  Created on: Jul 7, 2010
 *      Author: justin
 */

#include "DisplayDriver.h"
#include "Swizzler.h"
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/eeprom.h>

void DisplayDriver::init() {
  clearDisplay();
  setAutoScroll(false);
}

void DisplayDriver::putChar(uint8_t c) {
  Wire.beginTransmission(twiAddress);
  Wire.send(c);
  Wire.endTransmission();
  _delay_us(twiDelay);
}

void DisplayDriver::printMem(uint8_t *str, uint8_t len) {
  Wire.beginTransmission(twiAddress);
  for (uint8_t i=0; i < len; i++) {
    Wire.send(str[i]);
    _delay_us(twiDelay);
  }
  Wire.endTransmission();
  _delay_us(twiDelay);
  _delay_us(twiDelay);
}

void DisplayDriver::clearDisplay() {
  sendCommand(clearHome);
}

void DisplayDriver::setAutowrap(bool onOff) {
  sendCommand(onOff ? autoWrapOn : autoWrapOff);
}

void DisplayDriver::setAutoScroll(bool onOff) {
  sendCommand(onOff ? autoScrollOn : autoScrollOff);
}

void DisplayDriver::moveCursor(uint8_t col, uint8_t row) {
  Wire.beginTransmission(twiAddress);
  Wire.send(commandByte);       _delay_us(twiDelay);
  Wire.send(setCursorPosition); _delay_us(twiDelay);
  Wire.send(col);               _delay_us(twiDelay);
  Wire.send(row);               _delay_us(twiDelay);
  Wire.endTransmission();
}

void DisplayDriver::sendCommand(DiplayCommand cmd) {
  Wire.beginTransmission(twiAddress);
  Wire.send(commandByte); _delay_us(twiDelay);
  Wire.send(cmd);         _delay_us(twiDelay);
  Wire.endTransmission();
}
