#include "WProgram.h"
#include "wavetable.h"

int Wavetable::wtIndex;

char Wavetable::noiseTable[TABLE_SIZE];
char Wavetable::triTable[TABLE_SIZE];	
char Wavetable::sawTable[TABLE_SIZE];
char Wavetable::sqTable[TABLE_SIZE];
char Wavetable::randTable[TABLE_SIZE];

char* Wavetable::curWaveTable;

void Wavetable::begin() {
	genNoise();
	genRand();
	genSquare();
	genTriangle();
	genSawtooth();
	curWaveTable = triTable;
}

void Wavetable::genRand() {
	int i;
	
	for (i=0; i < TABLE_SIZE; i++) {
		Wavetable::randTable[i] = random(WAVE_HEIGHT)-(WAVE_HEIGHT/2);
	}
}

void Wavetable::genNoise() {
	int i;
	
	for (i=0; i < TABLE_SIZE; i++) {
		Wavetable::noiseTable[i] = random(WAVE_HEIGHT)-(WAVE_HEIGHT/2);
	}
}

void Wavetable::genSquare() {
	int i;
	for (i=0; i < TABLE_SIZE/2; i++) {
		Wavetable::sqTable[i] = MIN_SAMPLE;
	}

	for (; i < TABLE_SIZE; i++) {
		Wavetable::sqTable[i] = MAX_SAMPLE;
	}
}

void Wavetable::genTriangle() {
	short x1,x2,y1,y2;
	short slope;
	int i, sample=0;
	
	x1=0;
	y1=MIN_SAMPLE;
	y2 = MAX_SAMPLE;
	x2 = TABLE_SIZE/2;
	slope = (y2-y1)/(x2-x1);
	sample = y1;
	for (i=0; i < (TABLE_SIZE/2); i++) {
		Wavetable::triTable[i]= sample;
		sample += slope;
	}
	
	x1 = TABLE_SIZE/2;
	y1 = MAX_SAMPLE;
	x2 = TABLE_SIZE;
	y2 = MIN_SAMPLE;
	slope = (y2-y1)/(x2-x1);
	sample = y1-1;
	for (; i < TABLE_SIZE; i++) {
		Wavetable::triTable[i] = sample;
		sample += slope;
	}
}

void Wavetable::genSawtooth() {
	short x1,x2,y1,y2;
	short slope;
	int i,sample;
	
	x1 = 0;
	y1 = MIN_SAMPLE; 
	y2 = MAX_SAMPLE;
	x2 = TABLE_SIZE;
	slope = (y2-y1)/(x2-x1);
	sample = y1;
	for (i=0; i < TABLE_SIZE; i++) {
		Wavetable::sawTable[i]= sample;
		sample += slope;
	}
}

