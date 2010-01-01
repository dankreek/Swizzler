#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <WProgram.h>
#include <inttypes.h>
#include "wavetable.h"
#include "waveout.h"
#include "envelope.h"

/**
 * This is the ISR that handles doing sound output. One sample is output during the interrupt.
 */
ISR(TIMER1_COMPA_vect) {	
	// Calculate the output sample (signed 8bit sample)
	int out;

	// Output the next sample 
	out = Wavetable::outputTable[Wavetable::wtIndex];

	// Apply envelope scaling
	out *= envelopeOut.scalar;
	out /= ENV_SCALAR_RANGE;

	// Output the mixed and modulated sample, convert to unsigned 8bit
	OCR2A = out+128;

	// Go to the next sample
	Wavetable::incWtIndex();
}

/**
 * Initialize the sound output
 */
void Waveout::start() {
    pinMode(WAVEOUT_PIN, OUTPUT);

    // Set up Timer 2 to do pulse width modulation on the speaker
    // pin.

    // Use internal clock (datasheet p.160)
    ASSR &= ~(_BV(EXCLK) | _BV(AS2));

    // Set fast PWM mode  (p.157)
    TCCR2A |= _BV(WGM21) | _BV(WGM20);
    TCCR2B &= ~_BV(WGM22);

    // Do non-inverting PWM on pin OC2A (p.155)
    // On the Arduino this is pin 11.
    TCCR2A = (TCCR2A | _BV(COM2A1)) & ~_BV(COM2A0);
    TCCR2A &= ~(_BV(COM2B1) | _BV(COM2B0));

    // No prescaler (p.158)
    TCCR2B = (TCCR2B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);

    // Set initial pulse width to 0
    OCR2A = 0;

    // Set up Timer 1 to send a sample every interrupt.
    cli();

    // Set CTC mode (Clear Timer on Compare Match) (p.133)
    // Have to set OCR1A *after*, otherwise it gets reset to 0!
    TCCR1B = (TCCR1B & ~_BV(WGM13)) | _BV(WGM12);
    TCCR1A = TCCR1A & ~(_BV(WGM11) | _BV(WGM10));

    // No prescaler (p.134)
    TCCR1B = (TCCR1B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);

    //OCR1A = F_CPU / SAMPLE_RATE;    // 16e6 / 16000 = 1000
    setFreq(440);
	
    // Enable interrupt when TCNT1 == OCR1A (p.136)
    TIMSK1 |= _BV(OCIE1A);

    sei();

    // Ramp up the DAC from 0 to 128 to prevent the popping noise
    for (uint8_t i=0; i < 128; i++)
        OCR2A = i;
    
    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);
}

void Waveout::stop() {
    // Disable playback per-sample interrupt.
    TIMSK1 &= ~_BV(OCIE1A);

    // Disable the per-sample timer completely.
    TCCR1B &= ~_BV(CS10);

    // Disable the PWM timer.
    TCCR2B &= ~_BV(CS10);

    digitalWrite(WAVEOUT_PIN, LOW);
}

/**
 * Figure out the value of OCR1A for the input frequency. This basically finds how many CPU cycles
 * pass during the output of one sample from the wavetable. This is done by using the following formula:
 * interrupt_counts = (1 / frequency) *
 *
 * Note that at 16Mhz there are 16 clock cycles in a microsecond
 */
void Waveout::setFreq(int freq) {
	OCR1A = (unsigned long)1000000 / (unsigned long)freq;
}
