#ifndef ENVGEN_H
#define ENVGEN_H

#include <stdlib.h>
#include "AudioLine.h"

enum EnvelopeState {ENV_CLOSED, ENV_ATTACK, ENV_DECAY, ENV_SUSTAIN, ENV_RELEASE};

// Set the maximum envelope scalar value
#define ENV_SCALAR_RANGE	16	

// Default envelope values
#define ATTACK 2 
#define DECAY 1500
#define SUSTAIN 8 
#define RELEASE 1500 

class Envelope {
    private:
	EnvelopeState	state;		// Current state of envelope generator

	int		attackTime;	// The attack time
	int		decayTime;	// The decay time
	int		sustainLevel;	// The sustain level
	int		releaseTime;	// The release time
	int		time;		// Current time (in ms) of current envelope phase

	void		setState(EnvelopeState state);	// Set the envelope's state

    public:
	bool		gate;		// TRUE=gate close (signal start envelope)
					// FALSE=gate open (signalt start release)

	int		scalar;		// The last calculated amplitude scalar

	AudioLine	line;		// Line used to calculate amplitudes
	
	// Setup the envelope generator
	void begin();

	void setup(int attack, int decay, int sustain, int release); 

	// Calculate the next envelope scalar
	void next();

	// The gate's newly opened, start attack phase
	inline
	void closeGate() {
		this->gate = true;
		this->setState(ENV_ATTACK);
	}

	inline
	void openGate() {
		this->gate = false;
		this->setState(ENV_RELEASE);
	}
	
	
}; 

extern Envelope envelopeOut;

#endif
