/*
 * TimedLineBuffer.h
 *
 *  Created on: Nov 14, 2010
 *      Author: justin
 */

#ifndef TIMEDLINEBUFFER_H_
#define TIMEDLINEBUFFER_H_

#include <inttypes.h>
#include "ITimerCall.h"

/**
 * This is a timed buffer for the display output. Essentially, an instance of this class
 * controls one line of display text. This class allows a line of text to be written once
 * during a time interval, and all other attempted writes to the display are buffered. The
 * buffer holds one line of text and is continually overwritten until a new line can be
 * flushed out to the display again.
 */
class TimedLineBuffer : public ITimerCall {
public:
  /**
   * Creates a new line buffer.
   * @rowNumber The row number that this class is buffering (0-1)
   */
  TimedLineBuffer(uint8_t rowNumber);

  static const uint8_t displayWidth = 16;
  char displayBuffer[displayWidth + 1];

  // Either send the buffer out, or wait
  void flush();

  void nextTick();
private:
  // Time interval for displaying messages, measured in ticks (currently 8ms/tick)
  static const uint16_t displayInterval = 20;

  // Send the buffer out to the screen
  void outputBuffer();

  // Amount of time left before a new message can be displayed
  int16_t timerCountdown;

  // Is the data in the buffer waiting to be sent out?
  bool isBufferFull;

  uint8_t rowNumber;
};

#endif /* TIMEDLINEBUFFER_H_ */
