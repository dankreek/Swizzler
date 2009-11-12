#include <WProgram.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "wavetable.h"
#include "wavegen.h"
#include "envelope.h"

extern "C" void __cxa_pure_virtual() {}

#define ATTACK 0
#define DECAY 10
// 0-32
#define SUSTAIN 28 
#define RELEASE 1000
 
int ledPin = 13;
int buttonPin = 9;

int output;
unsigned long ms=0;

void setup()
{	
	pinMode(ledPin, OUTPUT);
	pinMode(buttonPin, INPUT);

	// Try and make sure our noise pattern is different every bootup!
	randomSeed(analogRead(0));
	
	//lastSample = 0;
	Serial.begin(19200);
		
	// Setup the envelope generator
	envelopeOut.setup(ATTACK, DECAY, SUSTAIN, RELEASE);
	envelopeOut.openGate();	
	
	// Generate wavetables
	Wavetable::genTriangle();
	Wavetable::genSawtooth();
	Wavetable::genNoise();
	
	// Startup the wave generation
	initWavegen();

	setFreq(440);
}


bool gate=false;
int main(void)
{
	init();
	setup();

	while(true) {
		if ((digitalRead(buttonPin) == 1) && (envelopeOut.gate == false)) {
			envelopeOut.closeGate();
		}
		else if ((digitalRead(buttonPin) == 0) && (envelopeOut.gate == true)) {
			envelopeOut.openGate();
		}
	}
}
