#ifndef WAVETABLE_H_
#define WAVETABLE_H_

// The length (in samples) of the wavetable
// this number is used to calculate the interrupt
// timer length for correct frequency generation
#define TABLE_SIZE 16

// The total amplitude for the wave generation (-31 to 31)
// 64 is currently chosed as it is 1/4th the total amplitude
// available with 8-bit output
#define WAVE_HEIGHT 128 
#define MIN_SAMPLE (WAVE_HEIGHT/2*-1)
#define MAX_SAMPLE (WAVE_HEIGHT/2)-1

class Wavetable {
    public:
	static int wtIndex;

	inline static
	void incWtIndex() {
		wtIndex = (wtIndex + 1) % TABLE_SIZE;
	}

	static void begin();

	static void genTriangle();
	static void genSawtooth();
	static void genNoise();
	static void genSquare();
	static void genRand();

	static char noiseTable[TABLE_SIZE];
	static char randTable[TABLE_SIZE];
	static char triTable[TABLE_SIZE];
	static char sawTable[TABLE_SIZE];
	static char sqTable[TABLE_SIZE];

	// Points to the current
	static char *curWaveTable;
};

#endif /*WAVETABLE_H_*/
