#ifndef PRESET_H
#define PRESET_H

#include <inttypes.h>

/**
 * This struct represents one Preset stored in RAM
 * Note that all stored values are in raw MIDI controller values (0-127)
 * and will be translated to real values through the midi input shits (SetParameters)
 *
 * Currently 36 bytes long
 */
struct Preset {
	// Preset name
	char name[16];

	// LFO effects
	uint8_t lfoFreq;
	uint8_t lfoType;

	// Envelope
	uint8_t	attackTime;
	uint8_t	decayTime;
	uint8_t sustainLevel;
	uint8_t releaseTime;

	// Oscillators
	uint8_t waveform1;
	uint8_t voiceLevel1;

        uint8_t waveform2;
        uint8_t voiceLevel2;
        uint8_t freqOffset2;

        uint8_t waveform3;
        uint8_t voiceLevel3;
        uint8_t freqOffset3;

        uint8_t noiseLevel;

	uint8_t pulseWidth;

	// Portamento
	uint8_t portamentoTime;
	uint8_t portamentoOn;

	// Arpeggiator
	uint8_t arpeggioTime;
	uint8_t arpeggioMinNotes;
	uint8_t arpeggioOn;
	uint8_t arpeggioDirection;

	// Range of bend
	uint8_t bendRange;
};

#endif
