#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <WProgram.h>
#include <wiring.h>
#include "Swizzler.h"
#include "Envelope.h"

// Update the envelope every millisecond
// This routine is no longer envelope-specific, it should be moved
ISR(TIMER0_OVF_vect) {	
	// Get the next envelope value
	swizzler.envelope.next();

	NoteManager::nextTick();
	FrequencyManager::nextTick();

	// Every

	// Call the arduino library's time keeping functions. May not be needed later.	
	//timerhook();
}

void Envelope::init() {
	attackTime = ATTACK;
	decayTime = DECAY;
	sustainLevel = SUSTAIN;
	releaseTime = RELEASE;
	this->openGate();	

	// The envelope is in the "not doing anything" state
	this->setState(ENV_CLOSED);
}

void Envelope::setState(EnvelopeState state) {
	this->state = state;
	this->time = 0;

	switch (this->state) {
		case ENV_ATTACK:
			line.init(0, ENV_SCALAR_RANGE, this->attackTime);
			break;
		case ENV_DECAY:
			line.init(ENV_SCALAR_RANGE, this->sustainLevel, this->decayTime);
			break;
		case ENV_SUSTAIN:
			scalar = sustainLevel;
			break;
		case ENV_RELEASE:
			line.init(scalar, 0, this->releaseTime);
			break;
		case ENV_CLOSED:
			scalar = 0;
			break;
	};
}

/**
 * Call this every millisecond to keep envelope in time
 */
void Envelope::next() {
	time++;

	// Advance envelope lines where needed
	switch (state) {
		case ENV_ATTACK:
			line.next(&scalar);
			if (time >= attackTime)	setState(ENV_DECAY);
			break;
		case ENV_DECAY:
			line.next(&scalar);
			if (time >= decayTime) setState(ENV_SUSTAIN);
			break;
		case ENV_RELEASE:
			line.next(&scalar);
			if (time >= releaseTime) setState(ENV_CLOSED);
			break;
	};
} 

