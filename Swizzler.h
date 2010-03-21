/*
 * Swizzler.h
 *
 *  Created on: Jan 31, 2010
 *      Author: justin
 */

#ifndef SWIZZLER_H_
#define SWIZZLER_H_

#include <WProgram.h>
#include "Envelope.h"
#include "Wavetable.h"
#include "Waveout.h"
#include "MidiInput.h"
#include "FrequencyManager.h"
#include "NoteManager.h"
#include "Wire.h"
#include "SetParameters.h"

class Swizzler {
  public:
	static const int ledPin = 13;
	static const int eepromAddress = 0x50;

	void init();
	void mainLoop();

	Envelope envelope;
};

extern Swizzler swizzler;

#endif /* SWIZZLER_H_ */
