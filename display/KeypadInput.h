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
    static void getKeys();

    /**
     * Decrement all the debounce counters
     */
    static inline void decCounters() {
      for (int i=0; i < 3; i++)
        for (int j=0; j < 4; j++)
          if (debounceCounters[i][j] >= 0) debounceCounters[i][j]--;
    }

    static uint16_t debounceTime;

  private:
    static void testRow(uint8_t rowMask, uint8_t columnBit, uint8_t columnNum);

    static void testKey(uint8_t col, uint8_t row);

    // Bitmap the stores which keys are currently pressed
    static uint16_t keysPressed;

    // The de-bounce counters for each key
    static int16_t  debounceCounters[3][4];
};

#endif /* KEYPADINPUT_H_ */
