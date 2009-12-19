#include <WProgram.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "wavetable.h"
#include "waveout.h"
#include "envelope.h"
#include "NoteLookupTable.h"
#include "MidiInput.h"
#include "MidiNoteBuffer.h"

extern "C" void __cxa_pure_virtual() {}

#define ATTACK 2 
#define DECAY 10
#define SUSTAIN ENV_SCALAR_RANGE/2 
#define RELEASE 700 
 
int ledPin = 13;
//int buttonPin = 2;

//void handle_button();

void setup() {	
	pinMode(ledPin, OUTPUT);

	// Try and make sure our noise pattern is different every bootup!
	randomSeed(analogRead(0));
	
	// For debugging. This will be turned into MIDI later.
	Serial.begin(31250);
		
	// Setup the envelope generator with some static values
	envelopeOut.setup(ATTACK, DECAY, SUSTAIN, RELEASE);
	envelopeOut.openGate();	
	
	// Generate wavetables
	Wavetable::genTriangle();
	Wavetable::genSawtooth();
	Wavetable::genNoise();
	Wavetable::genSquare();
	
	// Startup the wave generation
	Waveout::start();
	Waveout::setFreq(440);

	// Initialize MIDI input
	MidiInput::begin();
	MidiNoteBuffer::begin();
}

int main(void) {
	init();		// Initialize Arduino code
	setup();	// Setup my code

	while (true) {
		// Shove everything that's read by the serial port into the MIDI input
		if (Serial.available() > 0)
			MidiInput::pushByte(Serial.read());
	}

/*
	last = 0;
	while(true) {
		now = analogRead(0);

		if (last != now) {
			Waveout::setFreq(analogRead(0) << 2);
		}

		last = now;
		delay(10);
	}
*/
}

/*
// Eventually this will be a serial port read interrupt! Yay
void handle_button() {
	if ((digitalRead(buttonPin) == 1) && (envelopeOut.gate == false)) {
		envelopeOut.closeGate();
	}
	else if ((digitalRead(buttonPin) == 0) && (envelopeOut.gate == true)) {
		envelopeOut.openGate();
	}	
}
*/
