/** @file DisplayFrameBuffer.h
 *  @date Jan 17, 2011
 */

#ifndef DOUBLEBUFFER_H_
#define DOUBLEBUFFER_H_

#include "ITimerCall.h"
#include <inttypes.h>

/**
 * The display frame buffer is used to allow direct memory access to the display unit. After REFRESH_TIME number
 * of ticks, all the differences between the last screen update and what's in the current frame buffer are sent
 * to the display unit.
 *
 * @author Justin May <may.justin@gmail.com>
 */
class DisplayFrameBuffer : public ITimerCall {
public:
  DisplayFrameBuffer();

  /// The number of ticks that go by before the frameBuffer is updated
  static const uint8_t REFRESH_TIME = 28;

  /// Number of columns on the connected display
  static const uint8_t NUMBER_OF_COLUMNS = 16;

  /// Number of rows on the connected display
  static const uint8_t NUMBER_OF_ROWS = 2;

  /// Clear the contents of the frame buffer
  void clear();

  /**
   * Write a string from EEPROM to a location on the display.
   *
   * @param eepromString	Pointer to the string located in EEPROM to print
   * @param lineNum			The line number to put the string on
   * @param offset			Column to start printing string on
   */
  void writeEepromString(uint8_t* eepromString, uint8_t lineNum, uint8_t offset);

  /// Direct access to the frame buffer.
  uint8_t frameBuffer[ NUMBER_OF_ROWS ][ NUMBER_OF_COLUMNS + 1 ];

  /**
   * Printf wrapper for the display's frame buffer
   *
   * @param lineNum   Line number to put output on
   * @param formatStr Format string to put on line
   * @param ...       List of variables to put into format string
   */
  void printf(uint8_t lineNum, char* formatStr, ...);

  /// Update curTime and possible send a screen update
  void nextTick();

  /// If false then no updates will be sent to the display.
  bool isOutputOn;

private:

  /// The current time in number of ticks. This is used to decide when to sent a screen update.
  uint8_t curTime;

  /// Contains the contents of the last display update that was sent
  uint8_t diffBuffer[ NUMBER_OF_ROWS ][ NUMBER_OF_COLUMNS + 1 ];


  /// Record the differences between the current frame buffer and what's currently on the display.
  void recordChanges();

  /// Write all the differences found in changeList[][] by nextTick()
  void writeChangesToDisplay();

  /**
   *  Keeps a list of the first and last index of area of change. This is used to find the smallest
   *  number of characters that need to be sent to the display device.
   */
  int8_t changeList[ NUMBER_OF_ROWS ][ 2 ];
};

#endif /* DOUBLEBUFFER_H_ */
