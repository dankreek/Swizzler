/*
 * PwmOut.cpp
 *
 *  Created on: Jul 10, 2010
 *      Author: justin
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "PwmOut.h"
#include "Sound.h"

// Envelope resolution (in bits)
#define ENVELOPE_RESOLUTION     5

// Handle the PWM output
ISR(TIMER1_COMPA_vect) {
  static volatile uint16_t cycleCounter=0;
  int16_t out_sample=0;

  // Apply each envelope and mix each voice
  for (int i=0; i < Sound::numVoices; i++) {
    uint16_t oldPhase = Sound::voices[i].phaseAccumulator;

    // Convert envelope from 16 bit resolution to the set resolution
    out_sample += (Sound::voices[i].getNextSample() * (Sound::voices[i].envelope.level>>(16-ENVELOPE_RESOLUTION)));

    // If this voice is synced to a slave voice then restart its oscillation
    if ((Sound::voices[i].slaveSyncVoice > -1) && (oldPhase > Sound::voices[i].phaseAccumulator))
      Sound::voices[Sound::voices[i].slaveSyncVoice].phaseAccumulator = 0;
  }

  // Scale down to final 8-bit output level
  // (note that one more right shift is being done to prevent clipping from mixing)
  out_sample >>= (ENVELOPE_RESOLUTION+1);

  // Convert 8bit signed to 8bit unsigned, and output
  OCR2A = (out_sample+128);

  // Keep track of milliseconds depending upon the current sample rate
  cycleCounter++;
  if (cycleCounter >= PwmOut::sampleRate/1000) {
    cycleCounter = 0;
    Sound::msCounter++;
  }

  Waveform::pollNoiseGenerator();
}

void PwmOut::init() {
  DDRB = _BV(PB3);

  // Set up Timer 2 to do pulse width modulation on the speaker pin.

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

  // Set initial pulse width to the first sample.
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
  OCR1A = F_CPU / PwmOut::sampleRate;

  // Enable interrupt when TCNT1 == OCR1A (p.136)
  //TIMSK1 |= _BV(OCIE1A);
  TIMSK1 = _BV(OCIE1A);

  sei();
}
