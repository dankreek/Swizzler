/*
 * DoubleBuffer.cpp
 *
 *  Created on: Jan 17, 2011
 *      Author: justin
 */

#include "DisplayFrameBuffer.h"
#include "DisplayOutput.h"

DisplayFrameBuffer::DisplayFrameBuffer() {
  curTime = refreshTime;

  // Make both the framebuffer and the diffbuffer full of empty spaces
  for (uint8_t i=0; i < height; i++) {
    for (uint8_t j=0; j < width; j++) {
      frameBuffer[i][j] = ' ';
      diffBuffer[i][j] = ' ';
    }
  }
}

void DisplayFrameBuffer::nextTick() {
  curTime--;
  if (curTime == 0) {
    // Find the distance between the first and last change for each line of the buffer
    for (uint8_t i=0; i < height; i++) {
      int8_t firstChange = -1;
      int8_t lastChange = -1;
      bool nullWasFound = false;

      for (uint8_t j=0; j < width; j++) {
        if (frameBuffer[i][j] == '\0') {
          nullWasFound = true;
        }

        uint8_t compareChar;
        if (nullWasFound) {
          // Compare a space to the diffbuffer
          compareChar = ' ';
        } else {
          // Compare this character with the diffbuffer
          compareChar = frameBuffer[i][j];
        }

        if (compareChar != diffBuffer[i][j]) {
          // If this is the first different character mark it
          if (firstChange == -1) {
            firstChange = j;
          }

          // mark this as a potential last change
          lastChange = j;
        }

        // Write the character to the diffbuffer
        diffBuffer[i][j] = compareChar;
      }

      // Record changes found on this line
      changeList[i][0] = firstChange;
      changeList[i][1] = lastChange;
    }

    writeChangesToDisplay();

    curTime = refreshTime;
  }
}

void DisplayFrameBuffer::clear() {
  for (uint8_t i=0; i < height; i++) {
    for (uint8_t j=0; j < width; j++) {
      frameBuffer[i][j] = ' ';
    }
  }
}

void DisplayFrameBuffer::writeChangesToDisplay() {
  for (uint8_t i=0; i < height; i++) {
    // If a change was found on this line, write it out
    if (changeList[i][0] != -1) {
      int8_t firstChange = changeList[i][0];
      int8_t lastChange = changeList[i][1];

      DisplayOutput::moveCursor(firstChange, i);
      DisplayOutput::printMem(&diffBuffer[i][firstChange], lastChange - firstChange + 1);
    }
  }
}

void DisplayFrameBuffer::writeEepromString(uint8_t* eepromStrPtr, uint8_t lineNum, uint8_t offset) {
  uint8_t i;

  // Insert leading spaces
  for (i=0; i < offset; i++) { frameBuffer[lineNum][i] = ' '; }

  // Paste in the text
  uint8_t b = eeprom_read_byte(eepromStrPtr);
  for (; (b != 0); i++) {
    frameBuffer[lineNum][i] = b;
    eepromStrPtr++;
    b = eeprom_read_byte(eepromStrPtr);
  }

  // Write trailing spaces
  for (; i < width; i++) { frameBuffer[lineNum][i] = ' '; }
}
