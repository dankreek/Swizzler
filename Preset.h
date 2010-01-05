#ifndef PRESET_H
#define PRESET_H

#include <inttypes.h>

/**
 * This struct reprents one Preset stored in RAM
 */
struct PresetType {
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
	bool portamentoOn;

	// Arpeggiator
	uint8_t arpeggioTime;
	uint8_t arpeggioMinNotes;
	bool arpeggioOn;
};

#endif
