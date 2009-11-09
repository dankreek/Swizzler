#include "WProgram.h"
#include "wavegen.h"

VOICE outVoice;

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


