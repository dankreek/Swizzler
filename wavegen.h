enum WAVE_TYPE {TRI_WAVE, SQ_WAVE, NOISE_WAVE};

#define NULL 0

#define SAMPLE_RATE 32000

// Set the maximum envelope scalar value
#define ENV_SCALAR_RANGE	127

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
	int			sustain;	// The sustain level
	LINE_TRIP	release;	// The release leg
	int			amp_scalar;	// The last calculated amplitude scalar  
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

/**
 * Start a line over from the beginning
 */
void reset_line(LINE_TRIP *line) {
	line->plotY = line->initY;
	line->i = 0;
	line->error_term = 0;
}

/**
 * Setup one line trip
 */
void init_line_trip(int x1, int y1, int x2, int y2, LINE_TRIP *line) {
#ifdef DEBUG
	printf("Drawing line (%d, %d) - (%d, %d)\n", x1, y1, x2, y2);
#endif
	line->initY = y1;
 	line->diffY = y2-y1;
 	line->diffX = x2-x1;
 	
 	if (line->diffY < 0) {
 		line->diffY = -line->diffY;
 		line->unitY = -1;
 	}
 	else
 		line->unitY = 1;
}
/**
 * Setup the two lines that create a square or triangle wave
 * @freq	Frequency
 * @phase	Period (0-127)
 * @type	0=triangle, 1=square
 * @voice	Voice to setup wave on
 */
void setup_wave(int freq, int phase, WAVE_TYPE type, VOICE *voice) {
	// Make the wave type for future reference
	voice->wave.wave_type = type;
	
	// Find the wavelength (in # of samples)
	int wave_length = SAMPLE_RATE / freq;
	
#ifdef DEBUG	
	double length_time = (1.0/((double)SAMPLE_RATE /  (double)wave_length));
	printf("wave_length = %d samples @ %dhz = %fms\n", wave_length, SAMPLE_RATE, length_time*1000.0);
	printf("Actual rendered frequency: %fhz\n", (double)SAMPLE_RATE/(double)wave_length); 
#endif

	// Find the peak point
	int peak_sample = (wave_length * phase)/128;
	
	// Calculate the waves
	if (type == TRI_WAVE) {
		init_line_trip(0, LOWER_BOUND, peak_sample, UPPER_BOUND, &voice->wave.start);
		init_line_trip(peak_sample+1, UPPER_BOUND, wave_length, LOWER_BOUND, &voice->wave.end);
	}
	else if (type == SQ_WAVE) {
		init_line_trip(0, LOWER_BOUND, peak_sample, LOWER_BOUND, &voice->wave.start);
		init_line_trip(peak_sample+1, UPPER_BOUND, wave_length, UPPER_BOUND, &voice->wave.end);
	}
	
	// Set the current trip to the first line
	voice->wave.cur = &voice->wave.start;
	reset_line(voice->wave.cur);
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
		int startY;
		for (startY = line->plotY; (line->error_term <= 0) && (line-> i <= line->diffY); line->i++) {
			line->plotY += line->unitY;
			line->error_term += line->diffX;
		}
		line->error_term -= line->diffY;
		
		// Put the sample in the midpoint of the verticle line
		*output = ((line->plotY + startY)/2);
		
		if (line->i > line->diffY)  
			return false;
		else
			return true;
	}
}

/**
 * Swap to the next line in the wave loop
 */
void next_wave_line(VOICE *voice) {
	if (voice->wave.cur == &voice->wave.start) {
		// Go to the downslope of the wave
		voice->wave.cur = &voice->wave.end;
	}
	else {
		// Go to the begining of the loop again
		voice->wave.cur = &voice->wave.start;
	}
	
	reset_line(voice->wave.cur);
}

/**
 * Get the next sample in the voice
 * TODO: apply the envelope scaling factor after initial audio sample calculation
 */
bool next_sample(VOICE *voice) {
	if (next_bres(voice->wave.cur, &voice->wave.sample))
		return true;
	else {
		next_wave_line(voice);
		return false;
	}	
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
void setup_env(int attack, int decay, int sustain, int release, VOICE* voice) {
	// Initialize the attack and decay lines
	init_line_trip(0,0,attack,ENV_SCALAR_RANGE, &voice->envelope.attack);
	init_line_trip(0,ENV_SCALAR_RANGE,decay,sustain, &voice->envelope.decay);

	// This is done here for now, but needs to be moved!
	init_line_trip(0,sustain,release,0, &voice->envelope.release);

	// Envelope starts with a scalar of 0 and at the beginning of the attack phase
	voice->envelope.amp_scalar = 0;
	voice->envelope.cur = &voice->envelope.attack;
	reset_line(voice->envelope.cur);
		
	// Gate is open until the user closes it
	voice->envelope.gate = false;
	
	// Not sustaining until the decay cycle is over
	voice->envelope.sustaining = false;
}

/**
 * Call this every millisecond to keep envelope in time
 */
void next_envelope(VOICE *voice) {
	// If gate is closed follow attack-decay-sustain cycle
	if (voice->envelope.gate) {
		// The gate's newly opened, start attack phase
		if (voice->envelope.cur == NULL) {
			voice->envelope.sustaining = false;
			voice->envelope.cur =& voice->envelope.attack;
			reset_line(voice->envelope.cur);
		}
		
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
