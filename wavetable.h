#ifndef WAVETABLE_H_
#define WAVETABLE_H_

#include <inttypes.h>

// The length (in samples) of the wavetable
// this number is used to calculate the interrupt
// timer length for correct frequency generation
#define TABLE_SIZE 16

// The maximum amplitude of a waveform to be mixed
#define WAVE_MIX_AMP 16

// The total amplitude for the wave generation (-31 to 31)
// 64 is currently chosed as it is 1/4th the total amplitude
// available with 8-bit output
#define WAVE_HEIGHT 128 
#define MIN_SAMPLE (WAVE_HEIGHT/2*-1)/2
#define MAX_SAMPLE ((WAVE_HEIGHT/2)-1)/2

class Wavetable {
    public:
	static int wtIndex;

	inline static
	void incWtIndex() {
		wtIndex = (wtIndex + 1) % TABLE_SIZE;
	}

	// Initialize the wavetables and mix levels
	static void begin();

	// Generate waveforms
	static void genTriangle();
	static void genSawtooth();
	static void genNoise();
	static void genSquare();
	static void genRand();

	// Mix all the wave tables into the output table
	static void mixWaves();

	static char noiseTable[TABLE_SIZE];
	static char randTable[TABLE_SIZE];
	static char triTable[TABLE_SIZE];
	static char sawTable[TABLE_SIZE];
	static char sqTable[TABLE_SIZE];

	// The pulsewidth of the square wave
	static uint8_t pulseWidth;

	// The mix levels of each waveform
	static char triLevel;	
	static char sawLevel;
	static char sqLevel;
	static char randLevel;
	static char noiseLevel;

	// The combined waveforms are mixed into here and then output
	static char outputTable[TABLE_SIZE];
};

#endif /*WAVETABLE_H_*/
