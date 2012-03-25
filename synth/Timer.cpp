/** @file Timer.cpp
 *  @date Aug 1, 2010
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "Swizzler.h"
#include "PresetManager.h"
#include "Timer.h"

// Call timer services
ISR(TIMER0_OVF_vect) {
  Swizzler::tickCounter++;
}

void Timer::init() {
  // this needs to be called before setup() or some functions won't work there
  sei();

  TCCR0A |= _BV(WGM01) | _BV(WGM00);

  // set timer 0 prescale factor to 64
  //TCCR0B |= _BV(CS01) | _BV(CS00);
  TCCR0B |= _BV(CS02);

  // enable timer 0 overflow interrupt
  TIMSK0 |= _BV(TOIE0);
}
