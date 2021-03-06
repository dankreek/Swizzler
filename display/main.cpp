#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "TwoWireSlave.h"
#include "LcdDisplay.h"
#include "InputHandler.h"
#include "TimerHandler.h"
#include "KeypadInput.h"
#include "RingBuffer.cpp"

// Space for the i2c input buffer.
#define TWI_INPUT_BUFER_SIZE	64
uint8_t inputSpace[TWI_INPUT_BUFER_SIZE];

// The ring buffer class that wraps the space
RingBuffer<uint8_t> inputBuffer(inputSpace, TWI_INPUT_BUFER_SIZE);

void handleOutputRequest();

// --- Needed to output a character to the LCD if using printf.
#ifdef __cplusplus
extern "C"{
 FILE * uart_str;
}
#endif
static int lcd_putchar(char,FILE*);
#undef FDEV_SETUP_STREAM 
#define FDEV_SETUP_STREAM(p, g, f) { 0, 0, f, 0, 0, p, g, 0 }
FILE lcd_out = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);
static int lcd_putchar(char ch, FILE *unused) {
  LcdDisplay::write(ch);
  return 0;
}
// --- End printf code

int main(void) {	
  stdout = &lcd_out;

  // Initialize the LCD
  LcdDisplay::init(16, 2);

  // Initialize TWI bus
  twi.init(0x69, &inputBuffer);
  twi.onRequest(handleOutputRequest);

  KeypadInput::init();

  // Initialize the timer interrupt
  TimerHandler::init();

  // Initialize the input handler
  InputHandler::init();

  // Enable interrupts
  sei();

  while(true) {
    // Scan the keypad for key presses (and store them in the buffer if there are any)
    KeypadInput::pollKeypad();

    // See if the i2c bus has any incoming data
    if (inputBuffer.hasData()) {
      InputHandler::recvByte(inputBuffer.get());
    }

    // See if the keypad has any data
    /*
    if (KeypadInput::keyPressBuffer.hasData()) {
      printf("%c", KeypadInput::keyPressBuffer.get());
    }
    */
  }

  return 0;
}

void handleOutputRequest() {
  if (KeypadInput::keyPressBuffer.hasData()) {
    twi.send(KeypadInput::keyPressBuffer.get());
  }
  else {
    twi.send(0);
  }
}
