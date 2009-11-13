#include <WProgram.h>
#include "wavetable.h"

int Wavetable::wtIndex;

unsigned char Wavetable::noiseTable[TABLE_SIZE];
unsigned char Wavetable::triTable[TABLE_SIZE];	
unsigned char Wavetable::sawTable[TABLE_SIZE];

void Wavetable::genNoise() {
	int i;
	
	for (i=0; i < TABLE_SIZE; i++) {
		Wavetable::noiseTable[i] = random(WAVE_HEIGHT-1);
	}
}

void Wavetable::genTriangle() {
	short x1,x2,y1,y2;
	short slope;
	int i, sample=0;
	
	x1=0;
	y1=0;
	y2 = WAVE_HEIGHT;
	x2 = TABLE_SIZE/2;
	slope = (y2-y1)/(x2-x1);
	sample = y1;
	for (i=0; i < (TABLE_SIZE/2); i++) {
		Wavetable::triTable[i]= sample;
		sample += slope;
	}
	
	x1 = TABLE_SIZE/2;
	y1 = WAVE_HEIGHT;
	x2 = TABLE_SIZE;
	y2 = 0;
	slope = (y2-y1)/(x2-x1);
	sample = y1-1;
	for (; i < TABLE_SIZE; i++) {
		Wavetable::triTable[i] = sample;
		sample += slope;
	}
}

void Wavetable::genSawtooth() {
	short x1=0,x2,y1=0,y2;
	short slope;
	int i,sample=0;
	
	y2 = WAVE_HEIGHT;
	x2 = TABLE_SIZE;
	slope = (y2-y1)/(x2-x1);
	sample = 0;
	for (i=0; i < TABLE_SIZE; i++) {
		Wavetable::sawTable[i]= sample;
		sample += slope;
	}
}

