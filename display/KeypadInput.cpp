/*
 * KeypadInput.cpp
 *
 *  Created on: Jun 20, 2010
 *      Author: justin
 */

#include <avr/io.h>
#include <stdio.h>
#include "KeypadInput.h"
#include <util/delay.h>

int8_t KeypadInput::debounceCounter;
uint16_t KeypadInput::debounceTime;
uint8_t KeypadInput::lastKey;

uint8_t KeypadInput::padChars[][3]  = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};


void KeypadInput::init() {
  lastKey = 0;

  // The default debounce time in ms
  debounceTime = defaultDebounceTime;

  // Set all column lines to output
  KEYPAD_COL_DDR |= _BV(COL_0_BIT) | _BV(COL_1_BIT) | _BV(COL_2_BIT);

  // Set row lines to input
  KEYPAD_ROW_DDR &= ~(_BV(ROW_0_BIT)|_BV(ROW_1_BIT)|_BV(ROW_2_BIT)|_BV(ROW_3_BIT));

  // Set all row lines high
  KEYPAD_ROW_PORT |= _BV(ROW_0_BIT)|_BV(ROW_1_BIT)|_BV(ROW_2_BIT)|_BV(ROW_3_BIT);
}

int16_t KeypadInput::testRow(uint8_t colBitLow, uint8_t colBitHi1, uint8_t colBitHi2, uint8_t colNum) {
  KEYPAD_COL_PORT |= _BV(colBitHi1) | _BV(colBitHi2);
  KEYPAD_COL_PORT &= ~(_BV(colBitLow));

  _delay_us(10);

  uint8_t rowMask = ~(KEYPAD_ROW_PIN | ~(_BV(ROW_0_BIT)|_BV(ROW_1_BIT)|_BV(ROW_2_BIT)|_BV(ROW_3_BIT)) );

  if (rowMask & _BV(ROW_0_BIT)) {
    return padChars[0][colNum];
  }

  if (rowMask & _BV(ROW_1_BIT)) {
    return padChars[1][colNum];
  }

  if (rowMask & _BV(ROW_2_BIT)) {
    return padChars[2][colNum];
  }

  if (rowMask & _BV(ROW_3_BIT)) {
    return padChars[3][colNum];
  }

  return 0;
}

/**
 * This function reads all keys and stores their status in the keysPressed bitmap
 *
 * NOTE: This function depends on the current pin configuration. I know its begging
 */
uint8_t KeypadInput::getKey() {
  uint8_t gotKey;

  // If waiting for debounce, just skip this
  if (debounceCounter < 0) {
    // Note that this "loop" is unrolled because it's WAY smaller than using a for loop

    // Test column 0
    gotKey = testRow(COL_0_BIT, COL_1_BIT, COL_2_BIT, 0);
    if (gotKey && (gotKey != lastKey)) {
      lastKey = gotKey;
      debounceCounter = debounceTime;
      return gotKey;
    }
    else if (gotKey && (gotKey == lastKey)) return 0;

    // Test column 1
    gotKey = testRow(COL_1_BIT, COL_0_BIT, COL_2_BIT, 1);
    if (gotKey && (gotKey != lastKey)) {
      lastKey = gotKey;
      debounceCounter = debounceTime;
      return gotKey;
    }
    else if (gotKey && (gotKey == lastKey)) return 0;

    // Test column 2
    gotKey = testRow(COL_2_BIT, COL_0_BIT, COL_1_BIT, 2);
    if (gotKey && (gotKey != lastKey)) {
      lastKey = gotKey;
      debounceCounter = debounceTime;
      return gotKey;
    }
    else if (gotKey && (gotKey == lastKey)) return 0;

    // Handle a key-up event
    if (lastKey != 0) {
      printf("%c", lastKey+0x20);
      lastKey = 0;
      // Key-up events need to be debounced as well
      debounceCounter = debounceTime;
    }

    return 0;
  }
  // Waiting for debounce, so return no-data
  else
    return 0;
}
