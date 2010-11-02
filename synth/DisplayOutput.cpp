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

uint8_t DisplayOutput::printfBufferStorage[printfBufferSize];
RingBuffer<uint8_t> DisplayOutput::printfBuffer(printfBufferStorage, printfBufferSize);

uint8_t EEMEM DisplayOutput::greetingString[]={"   Welcome To\n    Swizzler"};

void DisplayOutput::init() {
  setAutowrap(true);
  clearDisplay();

  printEepromString(greetingString);
  printNumber(25);
}

void DisplayOutput::putChar(uint8_t c) {
  Wire.beginTransmission(twiAddress);
  Wire.send(c);
  Wire.endTransmission();

}

void DisplayOutput::printEepromString(uint8_t *eepromStrPtr) {
  uint8_t len=0;
  uint8_t *cPtr = eepromStrPtr;
  Wire.beginTransmission(twiAddress);
  uint8_t c; // = eeprom_read_byte(cPtr);
  eeprom_read_block(&c, cPtr, 1);
  while(c != 0) {
    len++;
    Wire.send(c);
    cPtr++;
    eeprom_busy_wait();
    eeprom_read_block(&c, cPtr, 1);
  }
  Wire.endTransmission();
  _delay_us(twiDelay*len);
}

void DisplayOutput::print(char s[]) {
  char* c;

  Wire.beginTransmission(twiAddress);
  for (c=s; *c; c++) {
    Wire.send(*c);
  }
  Wire.endTransmission();
  _delay_us(twiDelay);
}

void DisplayOutput::printNumber(uint8_t n) {
  uint8_t num=n;

  Wire.beginTransmission(twiAddress);
  if (num >= 100) {
    Wire.send('0'+(num/100));
    num -= (num/100)*100;
  }

  if (num >= 10) {
    Wire.send('0'+(num/10));
    num -= (num/10)*10;
  } else if (n >= 100) {
    Wire.send('0');
  }

  if (num >= 1) {
    Wire.send('0'+num);
  } else {
    Wire.send('0');
  }

  Wire.endTransmission();
  _delay_us(twiDelay);
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
  _delay_us(twiDelay);
}
