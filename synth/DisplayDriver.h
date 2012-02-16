/** @file   DisplayDriver.h
 *  @author Justin May <may.justin@gmail.com>
 *  @date   Created on: Jul 7, 2010
 */

#ifndef DISPLAYOUTPUT_H_
#define DISPLAYOUTPUT_H_


#include "ITimerCall.h"
#include <inttypes.h>
#include <stdio.h>
#include <avr/eeprom.h>

/**
 * This is utility class is used to send characters and commands to the display unit.
 */
class DisplayDriver  {
public:
  /**
   * Initialize the display by clearing the screen and setting autoscroll to off 
   */
  static void init();

  /**
   * Send a single character to the display at the current cursor position
   *
   * @param c   Character to send to the display
   */
  static void putChar( uint8_t c );

  /**
   * Send a length-based string of bytes to the display.
   *
   * @param str The string to send
   * @param len The number of bytes to send to the display
   * 
   * @warn The string is not null terminated, its length is set by the len parameter
   */   
  static void printMem( uint8_t* str, uint8_t len );

  /// Send the command to clear the display   
  static void clearDisplay();

  /**
   * Enable or disable the auto scroll feature.
   *
   * The auto scroll feature enables the display to scrolls up one line 
   * when the end of a line is reached.
   *
   * @param onOff   If true auto scroll is to be turned on, false if turned off
   */
  static void setAutoScroll( bool onOff );

  /**
   * Enable or disable the auto wrap feature. 
   *
   * Auto wrap enables the display to wrap to the next line when the current line being written to 
   * reaches the end.
   *
   * @param onOff   If true auto wrap is to be turned on, false if turned off
   */
  static void setAutowrap( bool onOff );

  /**
   * Move the cursor to a coordinate on the display
   *
   * @param col     Column to move the cursor to
   * @param row     Row to move the cursor to
   */
  static void moveCursor( uint8_t col, uint8_t row );

private:
  /// TWI address of the display unit
  static const uint8_t twiAddress = 0x69;

  /// The special characger code used to send a command to the display
  static const uint8_t commandByte = 0xfe;

  /// Time to wait after sending twi data (in microseconds)
  static const uint8_t twiDelay = 200;

  /// Greeting string to be sent upon power up
  static uint8_t greetingString[];

  /// Bytes signifying commands to be sent to the display
  enum DiplayCommand {
    autoScrollOn = 0x51,
    autoScrollOff = 0x52,
    clearHome = 0x58,
    autoWrapOn  = 0x43,
    autoWrapOff = 0x44,
    setCursorPosition = 0x47
  };

  /**
   * Send the command byte and then a command to the display
   * 
   * @param cmd The command to send to the display
   */
  static void sendCommand( DiplayCommand cmd );
};

#endif /* DISPLAYOUTPUT_H_ */
