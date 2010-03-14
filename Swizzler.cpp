/*
 * Swizzler.cpp
 *
 *  Created on: Jan 31, 2010
 *      Author: justin
 */
#include "Swizzler.h"
#include "PresetManager.h"

void Swizzler::init() {
	Wire.begin();

	pinMode(ledPin, OUTPUT);
	pinMode(8, OUTPUT);

	// Try and make sure our noise pattern is different every bootup!
	randomSeed(analogRead(0));

	// 31.250kbps is the speed a which MIDI travels in a vacuum.
	Serial.begin(31250);

	// Intialize the envelope generator
	envelope.init();

	// Generate wavetables
	Wavetable::init();

	// Startup the wave output (PWM generator)
	Waveout::start();

	// The oscillator will startup at 440hz
	Waveout::setFreq(440);

	// Initialize MIDI input
	MidiInput::init();

	// Initialize the Note Manager
	NoteManager::init();

	// Initialize Frequency Manager
	FrequencyManager::init();

	// Restore previous settings
	PresetManager::loadPoweronSettings();

	// Turn the on-board LED off
	digitalWrite(ledPin, HIGH);
}

/**
 * This is the non-ending loop, essentially it contains the lowest priority
 * tasks which are constantly being interrupted by the frequency-keeping and
 * time-keeping ISR's.
 */
void Swizzler::mainLoop() {
	while (true) {
		// Shove everything that's read by the serial port into the MIDI input
		if (Serial.available() > 0) {
			MidiInput::pushByte(Serial.read());
		}
		else {
			// If new noise isn't constantly generated then the output will be
			// a very interesting (but non-noise) waveform
			Wavetable::genNoise();

			// Remix the wavetables (since the waveform mix could be constantly changing)
			Wavetable::mixWaves();
		}
	}
}

Swizzler swizzler = Swizzler();
