/** @file Timer.h
 *  @date Aug 1, 2010
 */

#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

/**
 * Contains the code to initialize the Atmega's timer and the
 * ISR which handles incrementing the tick counter on every interrupt.
 *
 * @author Justin May <may.justin@gmail.com>
 */
class Timer {
public:
  /** Setup the registers for the timer hardware */
  static void init();
};

#endif
