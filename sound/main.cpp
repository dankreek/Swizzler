#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void setup_pwm();
void setup_waveform();
void setup_timer();
uint16_t calc_freq(uint16_t);

// Timer frequency
#define FINT (F_CPU/512)	// 512=256PWM steps / 0.5 step per PWM interrupt
// FINT = 31250Hz @F_CPU16MHz

// PWM frequency
#define FS (FINT/2)
// FS = 15625Hz @F_CPU16MHz

#define WAVE_SIZE	256
int8_t waveform[WAVE_SIZE];

uint16_t freq_coef=0;
uint8_t wave_i=0;

// Timer handler
ISR(TIMER0_OVF_vect) {
	static uint8_t flag=0;
	
	// Output sound every other interrupt
	flag^=1;
	if (flag) {
		// Output sound
		OCR1A = waveform[wave_i];
	}
	else {
		// Mix sound
		wave_i += freq_coef;
	}
}

int main() {
	setup_waveform();
	freq_coef = calc_freq(440);
	setup_pwm();
	setup_timer();

	while(true) {
		_delay_ms(100);
	}
}

void setup_pwm() {
	// for FAST PWM (8-Bit PWM) on OC1A 
	TCCR1A = _BV(WGM10) | _BV(COM1A1);
}

// This is currently set for 1ms, needs to be WAY faster (F_CPU/512 to be exact). Do research.
void setup_timer() {
  sei();

  TCCR0A |= _BV(WGM01) | _BV(WGM00);

  // set timer 0 prescale factor to 64
  TCCR0B |= _BV(CS01) | _BV(CS00);

  // enable timer 0 overflow interrupt
  TIMSK0 |= _BV(TOIE0);	
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
	return (templong*0x10000/FS);
}
