#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <WProgram.h>
#include "wavetable.h"
#include "wavegen_int.h"


int wt_index;		// The current index in the wavetable

// This is called at SAMPLE_RATE Hz to load the next sample.
ISR(TIMER1_COMPA_vect) {	
	// Output the current sample
	OCR2A = Wavetable::tri_wt[wt_index];

	// Go to the next sample
	wt_index = (wt_index+1) % TABLE_SIZE;

	//next_sample(&outVoice);
	
	// Convert signed oversampled data to unsigned 8-bit output
	//OCR2A = (output - LOWER_BOUND) / OVERSAMPLING;

	// Not enveloped
	//OCR2A = ((outVoice.wave.sample+outVoice2.wave.sample+outVoice3.wave.sample) - LOWER_BOUND) / OVERSAMPLING;
}

/**
 * Initialize the sound output
 */
void initWavegen()
{
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

    // Set the compare register (OCR1A).
    // OCR1A is a 16-bit register, so we have to do this with
    // interrupts disabled to be safe.
    //OCR1A = F_CPU / SAMPLE_RATE;    // 16e6 / 16000 = 1000
	
    // Enable interrupt when TCNT1 == OCR1A (p.136)
    TIMSK1 |= _BV(OCIE1A);

    sei();
    
    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);
}

void stopWavegen()
{
    // Disable playback per-sample interrupt.
    TIMSK1 &= ~_BV(OCIE1A);

    // Disable the per-sample timer completely.
    TCCR1B &= ~_BV(CS10);

    // Disable the PWM timer.
    TCCR2B &= ~_BV(CS10);

    digitalWrite(WAVEOUT_PIN, LOW);
}

/**
 * Figure out the value of OCR1A for the input frequency
 */
void setFreq(int freq) {
	OCR1A = (unsigned long)1000000 / (unsigned long)freq;
}