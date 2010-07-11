/*
 * Voice.h
 *
 *  Created on: Jul 10, 2010
 *      Author: justin
 */

#ifndef VOICE_H_
#define VOICE_H_

#include <inttypes.h>
#include "Envelope.h"
#include "Waveform.h"

class Voice {
public:
	// Calculate the next sample and apply the envelope
	int8_t renderSample();

        // Initialize this voice
        void init();

	Envelope envelope;
	Waveform waveform;


};

#endif /* VOICE_H_ */
