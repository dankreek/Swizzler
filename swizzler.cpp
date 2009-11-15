#include <WProgram.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "wavetable.h"
#include "waveout.h"
#include "envelope.h"
#include "note_lookup_table.h"

extern "C" void __cxa_pure_virtual() {}

#define ATTACK 2 
#define DECAY 10
#define SUSTAIN ENV_SCALAR_RANGE/2 
#define RELEASE 700 
 
int ledPin = 13;
int buttonPin = 2;

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
	Wavetable::genSquare();
	
	// Startup the wave generation
	Waveout::start();

	attachInterrupt(0, handle_button, CHANGE);
}

int freq=440;
bool gate=false;
int d=20;
int main(void) {
	init();
	setup();

	while(true) {
		Waveout::setFreq(noteToFreq(69));
		delay(d);
		Waveout::setFreq(noteToFreq(72));
		delay(d);
		Waveout::setFreq(noteToFreq(76));
		delay(d);
		Waveout::setFreq(noteToFreq(81));
	}
}

// Eventually this will be a serial port read interrupt! Yay
void handle_button() {
	if ((digitalRead(buttonPin) == 1) && (envelopeOut.gate == false)) {
		envelopeOut.closeGate();
	}
	else if ((digitalRead(buttonPin) == 0) && (envelopeOut.gate == true)) {
		envelopeOut.openGate();
	}	
}
