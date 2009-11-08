#include <stdlib.h>

enum WAVE_TYPE {TRI_WAVE, SQ_WAVE, NOISE_WAVE};

#define SAMPLE_RATE 16000

// Set the maximum envelope scalar value
#define ENV_SCALAR_RANGE	32

// Set 2X oversampling
#define OVERSAMPLING 2 
#define LOWER_BOUND (-128 * OVERSAMPLING)
#define UPPER_BOUND ((128 * OVERSAMPLING)-1)  

// These are all variables needed by Bresenham's algo
struct LINE_TRIP {
	int diffX, diffY;
	int initY, plotY, unitY;
	int i, error_term;
};

// A trip across the envelope!
struct ENV_TRIP {
	bool		gate;		// TRUE=gate close (signal start envelope), FALSE=gate open (signalt start release)
	bool		sustaining;	// Is the envelope currently sustaining while the gate's open?
	bool		last_gate;
	LINE_TRIP	attack;		// The attack leg of the envelope
	LINE_TRIP	decay;		// The decay leg 
	int		sustain;	// The sustain level
	LINE_TRIP	release;	// The release leg
	int		amp_scalar;	// The last calculated amplitude scalar  
	LINE_TRIP	*cur;		// Pointer to the current phase of the envelope
};

// A trip across the wave form!
struct WAVE_TRIP {
	enum WAVE_TYPE wave_type;	// The type of wave that's being generated
	LINE_TRIP start, end;	// The first and second line in the wave
	LINE_TRIP *cur;			// Pointer to the current line in the trip
	int sample;				// The last calculated sample value
};

// Struct defining a voice (audible oscillator)
struct VOICE {
	WAVE_TRIP wave;			// The oscillator wave generator
	ENV_TRIP envelope;
};

extern VOICE outVoice;


/**
 * Start a line over from the beginning
 */
inline
void reset_line(LINE_TRIP *line) {
	line->plotY = line->initY;
	line->i = 0;
	line->error_term = 0;
}

// The gate's newly opened, start attack phase
inline
void close_gate(VOICE *voice) {
	voice->envelope.gate = true;
	voice->envelope.sustaining = false;
	voice->envelope.cur =& voice->envelope.attack;
	reset_line(voice->envelope.cur);	
}

inline
void open_gate(VOICE *voice) {
	voice->envelope.gate = false;
}

/**
 * Calculate next value in the line using Bresenham's audio-enhanced algorithm/
 * @line Pointer to line struct to traverse
 * @output Pointer to the output of the next sample in the line
 * returns FALSE if this was the last sample to in the line, or TRUE if there is still points left in the line
 */
inline
bool next_bres(LINE_TRIP *line, int *output) {
	if (line->diffX >= line->diffY) {
		*output = line->plotY;
		line->error_term += line->diffY;
		
		if (line->error_term > line->diffX) {
			line->error_term -= line->diffX;
			line->plotY += line->unitY;
		}
		line->i++;
		
		if (line->i >= line->diffX)
			return false;
		else
			return true;
	}
	else {
		//int startY = line->plotY;
		for (; (line->error_term <= 0) && (line->i <= line->diffY); line->i++) {
			line->plotY += line->unitY;
			line->error_term += line->diffX;
		}
		line->error_term -= line->diffY;
		
		// Put the sample in the midpoint of the verticle line
		//*output = ((line->plotY + startY)/2);
		*output = line->plotY;
		
		if (line->i > line->diffY)  
			return false;
		else
			return true;
	}
}

/**
 * Call this every millisecond to keep envelope in time
 */
inline
void next_envelope(VOICE *voice) {
	// If gate is closed follow attack-decay-sustain cycle
	if (voice->envelope.gate) {			
		// If the envelope is not currently sustaining, then follow a line		
		if (!voice->envelope.sustaining) {	
			// Set the amplitude scalar to the next y-value in the envelope
			if (!next_bres(voice->envelope.cur, &voice->envelope.amp_scalar)) {
				// If this leg of the cycle is over, move on to the next
				if (voice->envelope.cur == &voice->envelope.attack)
					voice->envelope.cur = &voice->envelope.decay;
				else if (voice->envelope.cur == &voice->envelope.decay) {
					// Signal that the decay cycle is over and now're just chilling at the sustain level
					voice->envelope.sustaining = true;
					// Get ready for release cycle
					voice->envelope.cur = &voice->envelope.release;
					voice->envelope.amp_scalar =  voice->envelope.sustain;
				}
				
				// Reset the next line in the trip
				reset_line(voice->envelope.cur);
			}
		}
		
	}
	// If gate is open follow release cycle until completed
	else {
		if (voice->envelope.cur != NULL) {
			// Release cycle if finished, set amp_scalar to 0 and signal to stop following lines
			if (!next_bres(voice->envelope.cur, &voice->envelope.amp_scalar)) {
				voice->envelope.amp_scalar = 0;
				voice->envelope.cur = NULL;
			}
		}
	}
} 

void setup_env(int attack, int decay, int sustain, int release, VOICE* voice); 

