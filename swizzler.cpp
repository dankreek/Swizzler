#include <WProgram.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "wavetable.h"
#include "waveout.h"
#include "envelope.h"

extern "C" void __cxa_pure_virtual() {}

#define ATTACK 2 
#define DECAY 10
// 0-32
#define SUSTAIN ENV_SCALAR_RANGE 
#define RELEASE 1200 
 
int ledPin = 13;
int buttonPin = 2;

int output;

void handle_button();

void setup() {	
	pinMode(ledPin, OUTPUT);
	pinMode(buttonPin, INPUT);

	// Try and make sure our noise pattern is different every bootup!
	randomSeed(analogRead(0));
	
	// For debugging. This will be turned into MIDI later.
	Serial.begin(19200);
		
	// Setup the envelope generator with some static values
	envelopeOut.setup(ATTACK, DECAY, SUSTAIN, RELEASE);
	envelopeOut.openGate();	
	
	// Generate wavetables
	Wavetable::genTriangle();
	Wavetable::genSawtooth();
	Wavetable::genNoise();
	
	// Startup the wave generation
	Waveout::start();

	attachInterrupt(0, handle_button, CHANGE);
}

int freq=440;
bool gate=false;
int d=25;
int main(void) {
	init();
	setup();

	while(true) {
		Waveout::setFreq(440);
		delay(d);
		Waveout::setFreq(523);
		delay(d);
		Waveout::setFreq(659);
		delay(d);
		Waveout::setFreq(880);
		delay(d);
	}
}

void handle_button() {
	if ((digitalRead(buttonPin) == 1) && (envelopeOut.gate == false)) {
		envelopeOut.closeGate();
	}
	else if ((digitalRead(buttonPin) == 0) && (envelopeOut.gate == true)) {
		envelopeOut.openGate();
	}	
}
