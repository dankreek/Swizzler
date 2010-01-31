/*
 * Swizzler.h
 *
 *  Created on: Jan 31, 2010
 *      Author: justin
 */

#ifndef SWIZZLER_H_
#define SWIZZLER_H_

#include <WProgram.h>
#include "envelope.h"
#include "wavetable.h"
#include "waveout.h"
#include "MidiInput.h"
#include "FreqMan.h"

class Swizzler {
  public:
	static const int ledPin = 13;

	static void init();
	static void mainLoop();
};

#endif /* SWIZZLER_H_ */
