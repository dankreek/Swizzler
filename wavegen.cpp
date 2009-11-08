#include "WProgram.h"
#include "wavegen.h"

VOICE outVoice;

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
		init_line_trip(peak_sample, UPPER_BOUND, wave_length, LOWER_BOUND, &voice->wave.end);
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
 * Swap to the next line in the wave loop
 */
inline
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
inline
bool next_sample(VOICE *voice) {
	if (next_bres(voice->wave.cur, &voice->wave.sample)) {
		//voice->wave.sample = (voice->wave.sample * voice->envelope.amp_scalar)/127;
		return true;
	}
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
	voice->envelope.sustain = sustain;

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



