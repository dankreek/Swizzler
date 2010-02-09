#ifndef ENVGEN_H
#define ENVGEN_H
#include <WProgram.h>
#include <stdlib.h>
#include "Bresenham.h"

enum EnvelopeState {ENV_CLOSED, ENV_ATTACK, ENV_DECAY, ENV_SUSTAIN, ENV_RELEASE};

// Set the maximum envelope scalar value
#define ENV_SCALAR_RANGE	32	

// Default envelope values
#define ATTACK 10 
#define DECAY 20
#define SUSTAIN ENV_SCALAR_RANGE/4 
#define RELEASE 500 

class Envelope {
    private:
	EnvelopeState	state;		// Current state of envelope generator
	int		time;		// Current time (in ms) of current envelope phase

	void		setState(EnvelopeState state);	// Set the envelope's state

    public:
	int		attackTime;	// The attack time
	int		decayTime;	// The decay time
	int		sustainLevel;	// The sustain level
	int		releaseTime;	// The release time

	bool		gate;		// TRUE=gate close (signal start envelope)
					// FALSE=gate open (signalt start release)

	int16_t		scalar;		// The last calculated amplitude scalar

	Bresenham	line;		// Line used to calculate amplitudes
	
	// Setup the envelope generator
	void begin();

	void setup(int attack, int decay, int sustain, int release); 

	// Calculate the next envelope scalar
	void next();

	// The gate's closed, start attack phase
	inline
	void closeGate() {
		this->gate = true;
		this->setState(ENV_ATTACK);
		digitalWrite(13, LOW);
	}

	// The gate's been open start release phase
	inline
	void openGate() {
		this->gate = false;
		this->setState(ENV_RELEASE);
		digitalWrite(13, HIGH);
	}
}; 

#endif