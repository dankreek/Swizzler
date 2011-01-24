/*
 * DoubleBuffer.h
 *
 *  Created on: Jan 17, 2011
 *      Author: justin
 */

#ifndef DOUBLEBUFFER_H_
#define DOUBLEBUFFER_H_

#include "ITimerCall.h"
#include <inttypes.h>

class DisplayFrameBuffer : public ITimerCall {
public:
  DisplayFrameBuffer();

  // The number of ticks that go by before the frameBuffer is updated
  static const uint8_t refreshTime = 28;

  static const uint8_t numColumns = 16;
  static const uint8_t numRows = 2;

  // Clear the screen buffer
  void clear();

  // Write a string from EEPROM to a line
  void writeEepromString(uint8_t* eeprom_str, uint8_t lineNum, uint8_t offset);

  // Direct access to the frame buffer
  uint8_t frameBuffer[numRows][numColumns+1];

  /**
   * Printf wrapper
   *
   * @lineNum   Line number to put output on
   * @formatStr Format string
   * @... list of arguments
   */
  void printf(uint8_t lineNum, char* formatStr, ...);

  void nextTick();

  // Is sending updates to the display unit turned on
  bool isOutputOn;
private:
  uint8_t curTime;

  uint8_t diffBuffer[numRows][numColumns+1];

  // Record the differences between the frame buffer and the last sent buffer
  void recordChanges();

  // Write all the differences found in changeList[][] by nextTick()
  void writeChangesToDisplay();

  // Keeps a list of the first and last index of area of change a
  int8_t changeList[numRows][2];
};

#endif /* DOUBLEBUFFER_H_ */
