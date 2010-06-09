#include "WProgram.h"
#include "Wavetable.h"

int Wavetable::wtIndex;

int8_t Wavetable::noiseTable[TABLE_SIZE];
int8_t Wavetable::triTable[TABLE_SIZE];
int8_t Wavetable::sawTable[TABLE_SIZE];
int8_t Wavetable::sqTable[TABLE_SIZE];
int8_t Wavetable::randTable[TABLE_SIZE];

int8_t Wavetable::outputTable[TABLE_SIZE];

uint8_t Wavetable::pulseWidth;

int8_t Wavetable::triLevel;
int8_t Wavetable::sawLevel;
int8_t Wavetable::sqLevel;
int8_t Wavetable::randLevel;
int8_t Wavetable::noiseLevel;

void Wavetable::init() {
	pulseWidth = TABLE_SIZE/2;

	// Generate waveforms
	genNoise();
	genRand();
	genSquare();
	genTriangle();
	genSawtooth();
	
	// By default triangle wave is up full and the rest are at 0
	triLevel = WAVE_MIX_AMP;
	sqLevel = 0;
	sawLevel = 0;
	randLevel = 0;

	mixWaves();
}

/**
 * Mix all the waves together!
 */
void Wavetable::mixWaves() {
	for (uint8_t i=0; i < TABLE_SIZE; i++) {
		outputTable[i] = ((int16_t)triTable[i]*(int16_t)triLevel)/WAVE_MIX_AMP;
		outputTable[i] += ((int16_t)sawTable[i]*(int16_t)sawLevel)/WAVE_MIX_AMP;
		outputTable[i] += ((int16_t)sqTable[i]*(int16_t)sqLevel)/WAVE_MIX_AMP;
		outputTable[i] += ((int16_t)randTable[i]*(int16_t)randLevel)/WAVE_MIX_AMP;
		outputTable[i] += ((int16_t)noiseTable[i]*(int16_t)noiseLevel)/WAVE_MIX_AMP;
	}
}

void Wavetable::genRand() {
	uint8_t i;
	
	for (i=0; i < TABLE_SIZE; i++) {
		Wavetable::randTable[i] = random(WAVE_HEIGHT)-(WAVE_HEIGHT/2);
	}
}

void Wavetable::genNoise() {
	uint8_t i;
	
	for (i=0; i < TABLE_SIZE; i++) {
		Wavetable::noiseTable[i] = random(WAVE_HEIGHT)-(WAVE_HEIGHT/2);
	}
}

void Wavetable::genSquare() {
	uint8_t i;
	for (i=0; i < pulseWidth; i++) {
		Wavetable::sqTable[i] = MIN_SAMPLE;
	}

	for (; i < TABLE_SIZE; i++) {
		Wavetable::sqTable[i] = MAX_SAMPLE;
	}
}

void Wavetable::genTriangle() {
	int8_t x1,x2,y1,y2;
	int8_t slope;
	int8_t i, sample=0;
	
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
	int8_t x1,x2,y1,y2;
	int8_t slope;
	int8_t i,sample;
	
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

