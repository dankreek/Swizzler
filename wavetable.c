#include <WProgram.h>
#include "wavetable.h"

void Wavetable::generateNoise(unsigned char *buffer) {
	int i;
	
	for (i=0; i < TABLE_SIZE; i++) {
		buffer[i] = random(WAVE_HEIGHT-1);
	}
}

void Wavetable::generateTriangle(unsigned char *buffer) {
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
		buffer[i]= sample;
		sample += slope;
	}
	
	x1 = TABLE_SIZE/2;
	y1 = WAVE_HEIGHT;
	x2 = TABLE_SIZE;
	y2 = 0;
	slope = (y2-y1)/(x2-x1);
	sample = y1-1;
	for (; i < TABLE_SIZE; i++) {
		buffer[i] = sample;
		sample += slope;
	}
}

void Wavetable::generateSawtooth(unsigned char *buffer) {
	short x1=0,x2,y1=0,y2;
	short slope;
	int i,sample=0;
	
	y2 = WAVE_HEIGHT;
	x2 = TABLE_SIZE;
	slope = (y2-y1)/(x2-x1);
	sample = 0;
	for (i=0; i < TABLE_SIZE; i++) {
		buffer[i]= sample;
		sample += slope;
	}
}