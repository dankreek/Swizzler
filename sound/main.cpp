#include "Sound.h"
#include <util/delay.h>

#include <avr/io.h>
#include <avr/interrupt.h>

int main() {
  Sound::init();
  Sound::mainLoop();

  return 0;
}
