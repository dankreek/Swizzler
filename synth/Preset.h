#ifndef PRESET_H
#define PRESET_H

#include <inttypes.h>

/**
 * This struct reprents one Preset stored in RAM
 * Note that all stored values are in raw MIDI controller values (0-127)
 * and will be translated to real values through the midi input shits
 *
 * Currently 24 bytes long
 */
struct Preset {
	// Preset name
	char name[8];

	// Envelope
	uint8_t	attackTime;
	uint8_t	decayTime;
	uint8_t sustainLevel;
	uint8_t releaseTime;

	// Oscillator mix
	uint8_t triLevel;
	uint8_t sawLevel;
	uint8_t sqLevel;
	uint8_t randLevel;
	uint8_t noiseLevel;
	uint8_t pulseWidth;

	// Portamento
	uint8_t portamentoTime;
	uint8_t portamentoOn;

	// Arpeggiator
	uint8_t arpeggioTime;
	uint8_t arpeggioMinNotes;
	uint8_t arpeggioOn;

	// Range of bend
	uint8_t bendRange;
};

#endif
