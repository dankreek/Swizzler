/*
 * Swizzler.cpp
 *
 *  Created on: Jan 31, 2010
 *      Author: justin
 */
#include "Swizzler.h"

void Swizzler::init() {
	pinMode(ledPin, OUTPUT);
	pinMode(8, OUTPUT);

	// Try and make sure our noise pattern is different every bootup!
	randomSeed(analogRead(0));

	// 31.250kbps is the speed a which MIDI travels in a vacuum.
	Serial.begin(31250);

	// Setup the envelope generator with some static values
	// These will be set by MIDI soon
	envelope.begin();

	// Generate wavetables
	Wavetable::begin();

	// Startup the wave output
	Waveout::start();
	Waveout::setFreq(440);

	// Initialize MIDI input
	MidiInput::begin();

	// Initialize Frequency Manager
	FrequencyManager::init();

	NoteManager::enableArpeggio(false);

	digitalWrite(ledPin, HIGH);
}

void Swizzler::mainLoop() {
	while (true) {
		// Shove everything that's read by the serial port into the MIDI input
		if (Serial.available() > 0) {
			MidiInput::pushByte(Serial.read());
		}
		else {
			// If new noise isn't generated then the output will be
			// a very interesting (but non-noise) waveform
			Wavetable::genNoise();

			// Mixup the wavetables
			Wavetable::mixWaves();
		}
	}
}

Swizzler swizzler = Swizzler();
