#include "Ventilation.h"
volatile uint32_t millis_timer;
uint32_t tmr_millis() {
	uint32_t m;
	cli();
	m = millis_timer;
	sei();
	return m;
}

void timer0_initialization()
{
	DDRD |= (1 << PORTD6);

	TCCR0A = 0x00;
	TCCR0B = 0x00;
	TCNT0 = 0x00;

	TCCR0A |= (1 << COM0A1) | (1 << WGM00);
	TCCR0B |= (1 << CS00);
}

void timer1_initialization()
{
	TCNT1 = 0x00;
	TCCR1A = 0x00;
	TCCR1B = 0x00;

	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS11) | (1 << CS10);
	OCR1A = 0xFA;
	TIMSK1 = 0x00;
	TIMSK1 |= 1 << OCIE1A;
	//blabla();
}

ISR(TIMER1_COMPA_vect) {
	millis_timer++;
}

void blabla(){int b;}