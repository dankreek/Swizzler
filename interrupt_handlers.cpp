#include "wavetable.h"
#include "envelope.h"
#include <avr/interrupt.h>

/**
 * This is the ISR that handles doing sound output. One sample is output during the interrupt.
 * The timing for this interrupt is done in Waveout::setFreq() . See "waveout.h"
 */
ISR(TIMER1_COMPA_vect) {	
	// Output the current sample
	OCR2A = ((int)(Wavetable::triTable[Wavetable::wtIndex] << 4) * envelopeOut.scalar) / (int)ENV_SCALAR_RANGE;

	// Go to the next sample
	Wavetable::incWtIndex();
}

// Update the envelope every millisecond
ISR(TIMER0_OVF_vect)
{	
	// Get the next envelope value
	envelopeOut.next();
}
