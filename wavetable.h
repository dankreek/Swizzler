#ifndef WAVETABLE_H_
#define WAVETABLE_H_

#define TABLE_SIZE 16
#define WAVE_HEIGHT 16

class Wavetable {
    public:
	static void genTriangle();
	static void genSawtooth();
	static void genNoise();

	static unsigned char noiseTable[TABLE_SIZE];
	static unsigned char triTable[TABLE_SIZE];
	static unsigned char sawTable[TABLE_SIZE];
};

#endif /*WAVETABLE_H_*/
