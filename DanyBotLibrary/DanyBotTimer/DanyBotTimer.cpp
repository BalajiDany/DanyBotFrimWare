#include <avr/interrupt.h>

#include "../Constant.h"
#include "DanyBotTimer.h"

volatile uint32_t timer0_overflow_count = 0;
volatile uint32_t timer0_millis = 0;
static uint8_t timer0_fract = 0;

void DanyBotTimer::setUp() {
	sei();
	
	TCCR0A |= (1 << WGM01) | (1 << WGM00);
	TCCR0B |= (1 << CS01) | (1 << CS00);
	
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADCSRA |= (1 << ADEN);
	UCSR0B = 0;
}

uint32_t DanyBotTimer::millis() {
	uint32_t m;
	uint8_t oldSREG = SERG;

	cli();
	m = timer0_millis;
	SERG = oldSREG;

	return m;
}

uint32_t DanyBotTimer::micros() {
	uint32_t m;
	uint8_t oldSREG = SERG;
	uint8_t t;

	cli();
	m = timer0_overflow_count;
	t = TCNT0;

	if((TIFR0 & (1 << TOV0)) && (t  < 255)){
		m++;
	}
	SERG = oldSREG;

	return ((m << 8) + t) * (64 / clockCyclesPerMicrosecond());
}

void DanyBotTimer::start() {
	timer0_overflow_count = 0;
	timer0_millis = 0;
	timer0_fract = 0;
	TIMSK0 |= (1 << TOIE0);
}

void DanyBotTimer::stop() {
	TIMSK0 &= ~(1 << TOIE0);
}

ISR(TIMER0_OVF_vect){
	uint32_t m = timer0_millis;
	uint8_t f = timer0_fract;

	m += MILLIS_INC;
	f += FRACT_INC;
	if(f >= FRACT_MAX) {
		f -= FRACT_MAX;
		m += 1;
	}

	timer0_fract = f;
	timer0_millis = m;
	timer0_overflow_count++;
}