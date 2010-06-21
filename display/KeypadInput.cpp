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
bool KeypadInput::keyDown;

uint8_t KeypadInput::padChars[][3]  = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};


void KeypadInput::init() {
  lastKey = 0;

  // The default debounce time in ms
  debounceTime = 20;

  // Set all column lines to output
  KEYPAD_COL_DDR |= _BV(COL_0_BIT) | _BV(COL_1_BIT) | _BV(COL_2_BIT);

  // Set row lines to input
  KEYPAD_ROW_DDR &= ~(_BV(ROW_0_BIT)|_BV(ROW_1_BIT)|_BV(ROW_2_BIT)|_BV(ROW_3_BIT));

  // Set all row lines high
  KEYPAD_ROW_PORT |= _BV(ROW_0_BIT)|_BV(ROW_1_BIT)|_BV(ROW_2_BIT)|_BV(ROW_3_BIT);
}

int16_t KeypadInput::testRow(uint8_t rowMask, uint8_t columnBit, uint8_t columnNum) {
  if (rowMask & _BV(ROW_0_BIT)) {
    return padChars[0][columnNum];
  }

  if (rowMask & _BV(ROW_1_BIT)) {
    return padChars[1][columnNum];
  }

  if (rowMask & _BV(ROW_2_BIT)) {
    return padChars[2][columnNum];
  }

  if (rowMask & _BV(ROW_3_BIT)) {
    return padChars[3][columnNum];
  }


  return 0;
}

/**
 * This function reads all keys and stores their status in the keysPressed bitmap
 *
 * NOTE: This function depends on the current pin configuration.
 */
uint8_t KeypadInput::getKey() {
  uint8_t rowMask;
  uint8_t gotKey;

  // If waiting for debounce, just skip this
  if (debounceCounter < 0) {
    // Test column 0
    KEYPAD_COL_PORT |= _BV(COL_1_BIT) | _BV(COL_2_BIT);
    KEYPAD_COL_PORT &= ~(_BV(COL_0_BIT));

    _delay_us(10);

    rowMask = ~(KEYPAD_ROW_PIN | ~(_BV(ROW_0_BIT)|_BV(ROW_1_BIT)|_BV(ROW_2_BIT)|_BV(ROW_3_BIT)) );

    gotKey = testRow(rowMask, COL_0_BIT, 0);
    if (gotKey && (gotKey != lastKey)) {
      lastKey = gotKey;
      debounceCounter = debounceTime;
      keyDown = true;
      return gotKey;
    }

    // Test column 1
    KEYPAD_COL_PORT |= _BV(COL_0_BIT) | _BV(COL_2_BIT);
    KEYPAD_COL_PORT &= ~(_BV(COL_1_BIT));

    _delay_us(10);

    rowMask = ~(KEYPAD_ROW_PIN | ~(_BV(ROW_0_BIT)|_BV(ROW_1_BIT)|_BV(ROW_2_BIT)|_BV(ROW_3_BIT)) );

    gotKey = testRow(rowMask, COL_1_BIT, 1);
    if (gotKey && (gotKey != lastKey)) {
      lastKey = gotKey;
      debounceCounter = debounceTime;
      keyDown = true;
      return gotKey;
    }

    // Test column 2
    KEYPAD_COL_PORT |= _BV(COL_0_BIT) | _BV(COL_1_BIT);
    KEYPAD_COL_PORT &= ~(_BV(COL_2_BIT));

    _delay_us(10);

    rowMask = ~(KEYPAD_ROW_PIN | ~(_BV(ROW_0_BIT)|_BV(ROW_1_BIT)|_BV(ROW_2_BIT)|_BV(ROW_3_BIT)) );

    gotKey = testRow(rowMask, COL_2_BIT, 2);
    if (gotKey && (gotKey != lastKey)) {
      lastKey = gotKey;
      debounceCounter = debounceTime;
      keyDown = true;
      return gotKey;
    }


    lastKey = 0;
    return 0;
  }
  else
    return 0;
}
