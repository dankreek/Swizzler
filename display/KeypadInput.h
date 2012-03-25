/*
 * KeypadInput.h
 *
 * This class handles keypad input from a 3x4 matrix kaypad
 *
 *  Created on: Jun 20, 2010
 *      Author: justin
 */

#ifndef KEYPADINPUT_H_
#define KEYPADINPUT_H_

#define KEYPAD_ROW_PORT PORTB
#define KEYPAD_ROW_DDR  DDRB
#define KEYPAD_ROW_PIN  PINB
#define ROW_0_BIT       0
#define ROW_1_BIT       1
#define ROW_2_BIT       2
#define ROW_3_BIT       3

#define KEYPAD_COL_PORT PORTD
#define KEYPAD_COL_DDR  DDRD
#define KEYPAD_COL_PIN  PIND
#define COL_0_BIT       0
#define COL_1_BIT       1
#define COL_2_BIT       2

#define KEYPRESS_BUFFER_SIZE    12

#include <inttypes.h>
#include "RingBuffer.cpp"

class KeypadInput {
  public:
    static void init();

    /**
     * Read the keypad and fire off events if they have occurred
     */
    static void pollKeypad();

    /**
     * Decrement the debounce counter
     */
    static inline void decCounter() {
      if ( debounceCounter >= 0 ) debounceCounter--;
    }

    static uint16_t debounceTime;

    // Buffer to hold which keys have been pressed
    static RingBuffer<uint8_t> keyPressBuffer;

  private:
    // The default debounce time, set during init()
    static const uint16_t defaultDebounceTime = 10;

    static uint8_t keyPressSpace[];
    static const uint8_t keyPressSpaceSize = 12;

    // Key event handlers
    static void keyDownHandler(uint8_t key);
    static void keyUpHandler(uint8_t key);

    // Test a keypad row to see if a key had been struck
    static int16_t testRow(uint8_t colBitLow, uint8_t colBitHi1, uint8_t colBitHi2, uint8_t columnNum);

    // Keep track of last key pressed to remove repeats
    static uint8_t lastKey;

    // The debounce counter
    static int8_t  debounceCounter;

    // Array of which keys map to which ascii characters
    static uint8_t padChars[][3];

};

#endif /* KEYPADINPUT_H_ */
