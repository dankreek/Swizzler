#include <WProgram.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "wavetable.h"
#include "waveout.h"
#include "envelope.h"
#include "MidiInput.h"
#include "FreqMan.h"

extern "C" void __cxa_pure_virtual() {}
 
int ledPin = 13;

void setup() {	
	pinMode(ledPin, OUTPUT);
	pinMode(8, OUTPUT);

	// Try and make sure our noise pattern is different every bootup!
	randomSeed(analogRead(0));
	
	// 31.250kbps is the speed a which MIDI travels in a vacuum. 
	Serial.begin(31250);
		
	// Setup the envelope generator with some static values
	// These will be set by MIDI soon
	envelopeOut.begin();
	
	// Generate wavetables
	Wavetable::begin();
	
	// Startup the wave output 
	Waveout::start();
	Waveout::setFreq(440);

	// Initialize MIDI input
	MidiInput::begin();

	// Initialize Frequency Manager
	FreqMan::begin();

	digitalWrite(ledPin, HIGH);
}

int main(void) {
	init();		// Initialize Arduino library 
	setup();	// Setup synthesizer 

	while (true) {
		// Shove everything that's read by the serial port into the MIDI input
		if (Serial.available() > 0)
			MidiInput::pushByte(Serial.read());
		else {
			// If new noise isn't generated then the output will be
			// a very interesting (but non-noise) waveform
			Wavetable::genNoise();

			// Mixup the wavetables
			Wavetable::mixWaves();

		}
	}
}
