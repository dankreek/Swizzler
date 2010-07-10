#include <avr/io.h>
#include <inttypes.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void setup_pwm();
void setup_waveform();
void setup_timer();
uint16_t calc_freq(uint16_t);

#define SAMPLE_RATE 16000

#define WAVE_SIZE	256
int8_t waveform[WAVE_SIZE];

uint16_t freq_coef=0;
uint16_t wave_i=0;

// Timer handler
//ISR(TIMER0_OVF_vect) {
ISR(TIMER1_COMPA_vect) {
  int16_t out_sample;

  out_sample = (waveform[wave_i>>8]) + 128;
  OCR2A = out_sample;
  wave_i += freq_coef;
}

int main() {
  DDRB = _BV(PB1) | _BV(PB2);

  setup_waveform();

  setup_timer();
  freq_coef = calc_freq(440);
  sei();

  while (true) {
    freq_coef = calc_freq(440);
    _delay_ms(2000);
    freq_coef = calc_freq(880);
    _delay_ms(2000);
    freq_coef = calc_freq(440);
  }
}

void setup_timer() {
    DDRB = _BV(PB3);

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
     OCR1A = F_CPU / SAMPLE_RATE;

     // Enable interrupt when TCNT1 == OCR1A (p.136)
     //TIMSK1 |= _BV(OCIE1A);
     TIMSK1 = _BV(OCIE1A);

}

void setup_waveform() {
  int val=-128;
  for (int i=0; i < WAVE_SIZE; i++) {
          waveform[i] = val;
          val++;
  }
}

uint16_t calc_freq(uint16_t f) {
	uint32_t templong;
	
	templong=f;
	return (f*0x10000)/SAMPLE_RATE;
}
