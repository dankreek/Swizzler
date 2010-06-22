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

#include <inttypes.h>

class KeypadInput {
  public:
    static void init();

    /**
     * Read the keypad and fire off events if they have occured
     */
    static uint8_t getKey();

    /**
     * Decrement all the debounce counters
     */
    static inline void decCounter() {
      if (debounceCounter >=0) debounceCounter--;
    }

    static uint16_t debounceTime;

  private:
    // The default debounce time, set during init()
    static const uint16_t defaultDebounceTime = 10;

    static int16_t testRow(uint8_t rowMask, uint8_t columnBit, uint8_t columnNum);

    // Keep track of last key pressed to remove repeats
    static uint8_t lastKey;

    // The de-bounce counter
    static int8_t  debounceCounter;

    // true if a key is currently being held down
    static bool keyDown;

    // Array of which keys map to which ascii characters
    static uint8_t padChars[][3];

};

#endif /* KEYPADINPUT_H_ */
