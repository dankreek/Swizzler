#include <stdlib.h>

enum WAVE_TYPE {TRI_WAVE, SQ_WAVE, NOISE_WAVE};

#define SAMPLE_RATE 16000

// Set 2X oversampling
#define OVERSAMPLING 2 
#define LOWER_BOUND (-128 * OVERSAMPLING)
#define UPPER_BOUND ((128 * OVERSAMPLING)-1)  

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

void setup_env(int attack, int decay, int sustain, int release, VOICE* voice); 

