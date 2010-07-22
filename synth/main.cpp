#include "Swizzler.h"
#include "DisplayOutput.h"
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include "HardwareSerial.h"
#include <avr/interrupt.h>

extern "C" void __cxa_pure_virtual() {}

// --- Needed to output a character to the LCD if using printf.
/*
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
  DisplayOutput::putChar(ch);
  return 0;
}
// --- End printf code
*/

int main(void) {
  //pinMode(13, OUTPUT);
  DDRB = _BV(PB5);

  Serial.init(31250);

  sei();

  //digitalWrite(13, HIGH)
  swizzler.setLed(true);

  // Initialize the swizzler!
  /*
  swizzler.init();

  // Enter the main loop
  swizzler.mainLoop();
  */

  while (true) {
    if (Serial.available() > 0) {
      //digitalWrite(13, LOW);
      swizzler.setLed(false);

      _delay_ms(250);
      //digitalWrite(13, HIGH);
      swizzler.setLed(true);

      _delay_ms(100);
      //MidiInput::pushByte(Serial.read());
      uint8_t a = Serial.read();
    }
  }
}
