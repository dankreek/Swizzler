#include <WProgram.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "Swizzler.h"

extern "C" void __cxa_pure_virtual() {}

int main(void) {
	// Initialize Arduino library
	init();

	// Initialize the swizzler!
	Swizzler::init();
	
	// Enter the main loop
	Swizzler::mainLoop();
}
