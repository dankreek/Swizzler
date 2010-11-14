/*
 * TimedLineBuffer.cpp
 *
 *  Created on: Nov 14, 2010
 *      Author: justin
 */

#include "TimedLineBuffer.h"
#include "DisplayOutput.h"

TimedLineBuffer::TimedLineBuffer(uint8_t rowNumber) {
  this->rowNumber = rowNumber;
  this->timerCountdown = -1;
  this->isBufferFull = false;
}

void TimedLineBuffer::flush() {
  // If there's no countdown, just flush it and start the timer
  if (timerCountdown < 0) {
    outputBuffer();
    timerCountdown = displayInterval;
  // Otherwise just buffer it for later
  } else {
    isBufferFull = true;
  }
}

void TimedLineBuffer::outputBuffer() {
  DisplayOutput::moveCursor(0, rowNumber);
  DisplayOutput::printString(displayBuffer);
  isBufferFull= false;
}

void TimedLineBuffer::nextTick() {
  if (timerCountdown >= 0) timerCountdown--;

  // If the countdown has finished and the buffer is full, print it
  if ((timerCountdown < 0) && (isBufferFull)) {
    outputBuffer();
  }
}
