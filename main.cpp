#include "Swizzler.h"

extern "C" void __cxa_pure_virtual() {}

int main(void) {
	// Initialize Arduino library
	init();

	// Initialize the swizzler!
	swizzler.init();
	
	// Enter the main loop
	swizzler.mainLoop();
}
