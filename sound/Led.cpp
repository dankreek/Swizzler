/*
 * Led.cpp
 *
 *  Created on: Nov 13, 2010
 *      Author: justin
 */
#include <avr/io.h>

#include "Led.h"

void Led::init() {
  // Set the LED pin to output
  DDRB |= _BV(PB0);
}

void Led::setLedOn(bool onOff) {
  if (onOff)
    PORTB |= _BV(PB0);
  else
    PORTB &= ~_BV(PB0);
}

void Led::toggleLed() {
  uint8_t cur = (PORTB & 0x01);
  if (cur > 0) {
    PORTB &= ~1;
  } else {
    PORTB |= 1;
  }
}
