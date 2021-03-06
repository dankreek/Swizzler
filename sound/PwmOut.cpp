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

// Handle the PWM output
ISR(TIMER1_COMPA_vect) {
  static volatile uint16_t cycleCounter=0;
  static volatile int16_t lastSample=0;
  int16_t renderedSample=0;

  // Mix each voice (and partially calculate voice output level)
  for (int i=0; i < (Sound::numVoices); i++) {
#ifdef SYNC_ENABLED
    uint16_t oldPhase = Sound::voices[i].phaseAccumulator;
#endif

    renderedSample += (Sound::voices[i].getNextSample() * Sound::voices[i].outputVolume);

#ifdef SYNC_ENABLED
    // If this voice is synced to a slave voice then restart its oscillator
    if ((Sound::voices[i].slaveSyncVoice > -1) && (oldPhase > Sound::voices[i].phaseAccumulator))
      Sound::voices[Sound::voices[i].slaveSyncVoice].phaseAccumulator = 0;
#endif
  }

  // Finish calculating voice output levels (divide by common denominator)
  // (note that more right shifts are being done to prevent clipping from mixing)
  renderedSample >>= (Voice::outputVolumeResolution+2);

  // Envelope the output sound
  renderedSample = Sound::envelope.scaleSample(renderedSample);

  // Apply the global volume control
//  renderedSample = (renderedSample * Sound::masterVolume) / 0xff;

  // Generate an interpolated output sample
//  int16_t outputSample = (renderedSample + lastSample) >> 2;
//  lastSample = renderedSample;

  // Convert 8bit signed to 8bit unsigned, and output
  OCR0A = (renderedSample + 128);

  // Keep track of milliseconds depending upon the current sample rate
  cycleCounter++;
  if (cycleCounter >= PwmOut::sampleRate/1000) {
    cycleCounter = 0;
    Sound::msCounter++;
  }


  //Waveform::pollNoiseGenerator();
}

void PwmOut::init() {
  DDRD |= _BV(PD6);

  // Set up Timer 0 to do pulse width modulation on the speaker pin.

  // Use internal clock (datasheet p.160)
  ASSR &= ~(_BV(EXCLK) | _BV(AS2));

  // Set fast PWM mode
  TCCR0A |= _BV(WGM21) | _BV(WGM20);
  TCCR0B &= ~_BV(WGM22);

  // Do non-inverting PWM on pin OC0A
  TCCR0A = (TCCR0A | _BV(COM0A1)) & ~_BV(COM0A0);
  TCCR0A &= ~(_BV(COM0B1) | _BV(COM0B0));

  // No prescaler
  TCCR0B = (TCCR0B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);

  // Set initial pulse width to the first sample.
  OCR0A = 0;

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
