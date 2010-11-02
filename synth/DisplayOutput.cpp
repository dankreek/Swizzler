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
#include <stdio.h>

uint8_t DisplayOutput::printfBufferStorage[printfBufferSize];
RingBuffer<uint8_t> DisplayOutput::printfBuffer(printfBufferStorage, printfBufferSize);

uint8_t EEMEM DisplayOutput::greetingString[]={"   Welcome To\n    Swizzler"};

// --- Needed to output a character to the LCD if using printf.
#ifdef __cplusplus
extern "C"{
 FILE * uart_str;
}
#endif
static int lcd_putchar(char,FILE*);
#undef FDEV_SETUP_STREAM
#define FDEV_SETUP_STREAM(p, g, f) { 0, 0, f, 0, 0, p, g, 0 }
FILE lcd_out = FDEV_SETUP_STREAM(DisplayOutput::putCharBuffered, NULL, _FDEV_SETUP_WRITE);
int DisplayOutput::putCharBuffered(char ch, FILE *unused) {
  printfBuffer.push((uint8_t)ch);

  // If the buffer is full, or if this is an end-line flush it
  if (printfBuffer.isFull()) {
    flushPrintfBuffer();
  }

  return 0;
}

void DisplayOutput::flushPrintfBuffer() {
  Wire.beginTransmission(twiAddress);
  while (printfBuffer.hasData()) {
    Wire.send(printfBuffer.get());
  }
  Wire.endTransmission();
}
// --- End printf code


void DisplayOutput::init() {
  setAutowrap(true);
  clearDisplay();

  printf("poop (#%d)\n", 1);
  flushPrintfBuffer();

  //printEepromString(greetingString);
}

void DisplayOutput::putChar(uint8_t c) {
  Wire.beginTransmission(twiAddress);
  Wire.send(c);
  Wire.endTransmission();
}

//void DisplayOutput::printEepromString(uint8_t *eepromStrPtr) {
//  uint8_t *cPtr = eepromStrPtr;
//  Wire.beginTransmission(twiAddress);
//  uint8_t c; // = eeprom_read_byte(cPtr);
//  eeprom_read_block(&c, cPtr, 1);
//  while(c != 0) {
//    Wire.send(c);
//    cPtr++;
//    eeprom_busy_wait();
//    eeprom_read_block(&c, cPtr, 1);
//  }
//  Wire.endTransmission();
//  _delay_us(5);
//}

void DisplayOutput::print(char s[]) {
  char* c;

  Wire.beginTransmission(twiAddress);
  for (c=s; *c; c++) {
    Wire.send(*c);
  }
  Wire.endTransmission();
  _delay_us(5);
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
  _delay_us(5);
}
