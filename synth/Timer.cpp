#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <WProgram.h>
#include <wiring.h>
#include "Swizzler.h"
#include "PresetManager.h"

// Update the envelope every millisecond
// This routine is no longer envelope-specific, it should be moved
ISR(TIMER0_OVF_vect) {	
	//NoteManager::nextTick();
	//FrequencyManager::nextTick();

  // Call the arduino library's time keeping functions. May not be needed later.
  timerhook();
}
