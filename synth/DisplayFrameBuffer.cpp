/*
 * DoubleBuffer.cpp
 *
 *  Created on: Jan 17, 2011
 *      Author: justin
 */
#include <stdarg.h>
#include <avr/eeprom.h>
#include "DisplayFrameBuffer.h"
#include "DisplayDriver.h"
#include "Swizzler.h"

DisplayFrameBuffer::DisplayFrameBuffer() {
  isOutputOn = true;
  curTime = REFRESH_TIME;

  // Make both the framebuffer and the diffbuffer full of empty spaces
  for (uint8_t i=0; i < NUMBER_OF_ROWS; i++) {
    for (uint8_t j=0; j < NUMBER_OF_COLUMNS; j++) {
      frameBuffer[i][j] = ' ';
      diffBuffer[i][j] = ' ';
    }
  }
}

void DisplayFrameBuffer::nextTick() {
  curTime--;
  if (curTime == 0) {
    if (isOutputOn) {
      recordChanges();
      writeChangesToDisplay();
    }
    curTime = REFRESH_TIME;
  }
}

void DisplayFrameBuffer::clear() {
  for (uint8_t i=0; i < NUMBER_OF_ROWS; i++) {
    for (uint8_t j=0; j < NUMBER_OF_COLUMNS; j++) {
      frameBuffer[i][j] = ' ';
    }
  }
}

void DisplayFrameBuffer::recordChanges() {
  int8_t firstChange;
  int8_t lastChange;
  bool nullWasFound;

  // Find the distance between the first and last change for each line of the buffer
  for (uint8_t row=0; row < NUMBER_OF_ROWS; row++) {
    firstChange = -1;
    lastChange = -1;
    nullWasFound = false;

    for (uint8_t column=0; column < NUMBER_OF_COLUMNS; column++) {
      if (frameBuffer[row][column] == '\0') {
        nullWasFound = true;
      }

      uint8_t compareChar;
      if (nullWasFound) {
        // Compare a space to the diffbuffer
        compareChar = ' ';
      } else {
        // Compare this character with the diffbuffer
        compareChar = frameBuffer[row][column];
      }

      if (compareChar != diffBuffer[row][column]) {
        // If this is the first different character mark it
        if (firstChange == -1) {
          firstChange = column;
        }

        // mark this as a potential last change
        lastChange = column;
      }

      // Write the character to the diffbuffer
      diffBuffer[row][column] = compareChar;
    }

    // This is a workaround for a problem outputting only 1 char to the display... wtf?
    // TODO - Figure out what's wrong. It's probably the TWI driver
    if ((lastChange - firstChange) == 0) {
      if (lastChange == 15) {
        firstChange = 14;
      } else {
        lastChange = firstChange + 1;
      }
    }

    // Record changes found on this line
    changeList[row][0] = firstChange;
    changeList[row][1] = lastChange;
  }
}

void DisplayFrameBuffer::writeChangesToDisplay() {
  for (uint8_t row=0; row < NUMBER_OF_ROWS; row++) {
    // If a change was found on this line, write it out
    if (changeList[row][0] != -1) {
      int8_t firstChange = changeList[row][0];
      int8_t lastChange = changeList[row][1];

      DisplayDriver::moveCursor(firstChange, row);
      DisplayDriver::printMem(&diffBuffer[row][firstChange], lastChange - firstChange + 1);
    }
  }
}

void DisplayFrameBuffer::writeEepromString(uint8_t* eepromStrPtr, uint8_t lineNum, uint8_t offset) {
  uint8_t b = eeprom_read_byte(eepromStrPtr);
  for (uint8_t i=offset; (b != 0); i++) {
    frameBuffer[lineNum][i] = b;
    eepromStrPtr++;
    b = eeprom_read_byte(eepromStrPtr);
  }
}

void DisplayFrameBuffer::printf(uint8_t lineNum, char* fmt, ...) {
  va_list  args;
  va_start(args,fmt);
  vsprintf((char*)frameBuffer[lineNum], fmt, args);
  va_end(args);
}
