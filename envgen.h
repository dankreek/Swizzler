#ifndef ENVGEN_H
#define ENVGEN_H

#include <stdlib.h>
#include "bresenham.h"

// Set the maximum envelope scalar value
#define ENV_SCALAR_RANGE	32

class Envelope {
    private:
	bool		gate;		// TRUE=gate close (signal start envelope)
					// FALSE=gate open (signalt start release)
	
	bool		sustaining;	// Is the envelope currently sustaining while the gate's open?

	bool		last_gate;	// Is this still needed

	Bresenham	attack;		// The attack leg of the envelope
	Bresenham	decay;		// The decay leg 
	int		sustain;	// The sustain level
	Bresenham	release;	// The release leg

	Bresenham	*cur;		// Pointer to the current phase of the envelope

    public:
	int		scalar;		// The last calculated amplitude scalar
	
	void setup(int attack, int decay, int sustain, int release); 
	void next();

	// The gate's newly opened, start attack phase
	inline
	void closeGate() {
		this->gate = true;
		this->sustaining = false;
		this->cur = &attack;
		this->cur->reset();	
	}

	inline
	void openGate() {
		this->gate = false;
	}
	
	
}; 

#endif
