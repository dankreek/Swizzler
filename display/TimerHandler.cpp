/*
 * TimerHandler.cpp
 *
 *  Created on: Jun 20, 2010
 *      Author: justin
 *
 *  This source file handles the timer functionality for debouncing the keypad
 *  keys.
 *
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "TimerHandler.h"
#include "LcdDisplay.h"
#include "KeypadInput.h"

// 1ms timer interrupt vector
ISR(TIMER0_OVF_vect) {
  KeypadInput::decCounters();
}

/**
 * Set the timer interrupt handler to fire off once every millisecond
 */
void TimerHandler::init() {
  // this needs to be called before setup() or some functions won't
  // work there
  sei();

  TCCR0A |= _BV(WGM01) | _BV(WGM00);

  /*
  sbi(TCCR0A, WGM01);
  sbi(TCCR0A, WGM00);
  */

  // set timer 0 prescale factor to 64
  TCCR0B |= _BV(CS01) | _BV(CS00);
  /*
  sbi(TCCR0B, CS01);
  sbi(TCCR0B, CS00);
   */

  // enable timer 0 overflow interrupt
  TIMSK0 |= _BV(TOIE0);
  //sbi(TIMSK0, TOIE0);
}
