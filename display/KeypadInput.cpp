/*
 * KeypadInput.cpp
 *
 *  Created on: Jun 20, 2010
 *      Author: justin
 */

#include <avr/io.h>
#include <stdio.h>
#include "KeypadInput.h"

uint16_t KeypadInput::keysPressed;
int16_t KeypadInput::debounceCounters[3][4];
uint16_t KeypadInput::debounceTime;

void KeypadInput::init() {
  keysPressed = 0;

  for (int i=0; i < 3; i++)
    for (int j=0; j < 4; j++)
      debounceCounters[i][j] = -1;

  // Thedefault debounce time in ms
  debounceTime = 10;

  // Set all column lines to output
  KEYPAD_COL_DDR |= _BV(COL_0_BIT) | _BV(COL_1_BIT) | _BV(COL_2_BIT);

  // Set row lines to input
  KEYPAD_ROW_DDR &= ~(_BV(ROW_0_BIT)|_BV(ROW_1_BIT)|_BV(ROW_2_BIT)|_BV(ROW_3_BIT));

  // Set all row lines high
  KEYPAD_ROW_PORT |= _BV(ROW_0_BIT)|_BV(ROW_1_BIT)|_BV(ROW_2_BIT)|_BV(ROW_3_BIT);
}

void KeypadInput::testKey(uint8_t col, uint8_t row) {
  // This is a new keypress
  if (debounceCounters[col][row] < 0) {
    // Start new debounce timer
    debounceCounters[col][row] = debounceTime;

    // Mark key in the bitmask
    keysPressed |= _BV(row*3+col);
  }
}

void KeypadInput::testRow(uint8_t rowMask, uint8_t columnBit, uint8_t columnNum) {
  if (rowMask & _BV(ROW_0_BIT)) {
    testKey(columnNum, 0);
  }

  if (rowMask & _BV(ROW_1_BIT)) {
    testKey(columnNum, 1);
  }

  if (rowMask & _BV(ROW_2_BIT)) {
    testKey(columnNum, 2);
  }

  if (rowMask & _BV(ROW_3_BIT)) {
    testKey(columnNum, 3);
  }
}

/**
 * This function reads all keys and stores their status in the keysPressed bitmap
 *
 * NOTE: This function depends on the current pin configuration.
 */
void KeypadInput::getKeys() {
  uint8_t rowMask;

  // Save the old keys pressed for comparing to new keypressed. Decide which events to fire.
  uint16_t oldKeysPresed=keysPressed;

  keysPressed = 0;

  // Test column 0
  KEYPAD_COL_PORT |= _BV(COL_1_BIT) | _BV(COL_2_BIT);
  KEYPAD_COL_PORT &= ~(_BV(COL_0_BIT));

  rowMask = ~(KEYPAD_ROW_PIN | ~(_BV(ROW_0_BIT)|_BV(ROW_1_BIT)|_BV(ROW_2_BIT)|_BV(ROW_3_BIT)) );

  testRow(rowMask, COL_0_BIT, 0);

  // Test column 1
  KEYPAD_COL_PORT |= _BV(COL_0_BIT) | _BV(COL_2_BIT);
  KEYPAD_COL_PORT &= ~(_BV(COL_1_BIT));

  rowMask = ~(KEYPAD_ROW_PIN | ~(_BV(ROW_0_BIT)|_BV(ROW_1_BIT)|_BV(ROW_2_BIT)|_BV(ROW_3_BIT)) );

  testRow(rowMask, COL_1_BIT, 1);

  // Test column 2
  KEYPAD_COL_PORT |= _BV(COL_0_BIT) | _BV(COL_1_BIT);
  KEYPAD_COL_PORT &= ~(_BV(COL_2_BIT));

  rowMask = ~(KEYPAD_ROW_PIN | ~(_BV(ROW_0_BIT)|_BV(ROW_1_BIT)|_BV(ROW_2_BIT)|_BV(ROW_3_BIT)) );

  testRow(rowMask, COL_2_BIT, 2);

  // Test mask for differences
  for (int i=0; i < 3; i++)
    for (int j=0; j < 4; j++) {
      uint8_t mask = _BV(j*3+i);
      if ((mask&oldKeysPresed) != (mask&keysPressed)) {
        printf("\n%x", keysPressed);

        // Key pressed event
        if (keysPressed & mask) {

        }
        // Key released event
        else {

        }
      }

    }
}
