#include "Swizzler.h"

extern "C" void __cxa_pure_virtual() {}

// --- Needed to output a character to the LCD if using printf.
// TODO - get rid of this
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
  swizzler.init();
  swizzler.mainLoop();
}
