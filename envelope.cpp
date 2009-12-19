#include <stdint.h>
#include <avr/interrupt.h>
#include "envelope.h"
#include "bresenham.h"
#include <wiring.h>

// Update the envelope every millisecond
ISR(TIMER0_OVF_vect)
{	
	// Get the next envelope value
//	envelopeOut.next();
	
	timerhook();
}

/**
 * TODO: The release line CAN'T be setup until the gate is opened because the amp_scalar needs to be used as the first Y point
 * 
 * Setup a new set of envelope lines. In the envelope context the x coordinate measures time (in ms)
 * and the Y coordinate is an amplitude scaling
 * @attack	Attack time (in ms)
 * @decay	Decay time (in ms)
 * @sustain	Sustain level
 * @release	Release time (in ms)
 * @voice	Voice containing envelope needs
 */
void Envelope::setup(int attack, int decay, int sustain, int release) {
	// Record the sustain level
	this->sustain = sustain;

	// Initialize the attack and decay lines
	this->attack.init(0,0,attack,ENV_SCALAR_RANGE);
	this->decay.init(0,ENV_SCALAR_RANGE,decay,sustain);

	// This is done here for now, but needs to be moved!
	this->release.init(0,sustain,release,0);

	// Envelope starts with a scalar of 0 and at the beginning of the attack phase
	this->scalar = 0;
	this->cur = &this->attack;
	this->cur->reset();
		
	// Gate is open until the user closes it
	this->openGate();
	
	// Not sustaining until the decay cycle is over
	this->sustaining = false;
}

/**
 * Call this every millisecond to keep envelope in time
 */
void Envelope::next() {
	// If gate is closed follow attack-decay-sustain cycle
	if (this->gate) {			
		// If the envelope is not currently sustaining, then follow a line		
		if (!this->sustaining) {	
			// Set the amplitude scalar to the next y-value in the envelope
			if (!this->cur->next(&this->scalar)) {
				// If this leg of the cycle is over, move on to the next
				if (this->cur == &this->attack)
					this->cur = &this->decay;
				else if (this->cur == &this->decay) {
					// Signal that the decay cycle is over and now're just chilling at the sustain level
					this->sustaining = true;
					// Get ready for release cycle
					this->cur = &this->release;
					this->scalar = this->sustain;
				}
				
				// Reset the next line in the trip
				this->cur->reset();
			}
		}
	}
	// If gate is open follow release cycle until completed
	else {
		if (this->cur != NULL) {
			// Release cycle if finished, set amp_scalar to 0 and signal to stop following lines
			if (!this->cur->next(&this->scalar)) {
				this->scalar = 0;
				this->cur = NULL;
			}
		}
	}
} 

Envelope envelopeOut = Envelope();

