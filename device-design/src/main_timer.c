#define F_CPU 20000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define DELAY 10
//These are for Timer1
#define PRESCALE0_1 _BV(CS10)
#define PRESCALE0_8 _BV(CS11)
#define PRESCALE0_64 (_BV(CS10) | _BV(CS11))
#define PRESCALE0_256 _BV(CS12)
#define PRESCALE0_1024 (_BV(CS12) | _BV(CS10))

ISR(TIM1_COMPA_vect) { // this function is called every time the timer reaches the threshold we set
 PORTB ^= (1 << PB2); // toggle the LED
 PORTA ^= (1 << PA7); // toggle the LED
}



static inline void initTimer1(void) {
  TCCR1B |= (1 << WGM12); // configure timer1 for CTC mode
  TIMSK1 |= (1 << OCIE1A); // enable the CTC interrupt
  sei(); // enable global interrupts
  OCR1A = 100; // Should return frequency ~1000hz
  TCCR1B |= PRESCALE0_1024;
}

int main(void) {
  // -------- Inits --------- //
  DDRA |= 1 << PA7;
  DDRB |= 1 << PB2; 
  DDRA &= ~(1<<PA5); 
  //PORTA |= 1<<PA7;

	initTimer1();        // initialize timer registers
	sei();               // enable interrupts
	
	while(1)
	{
	}
	
	return 0;
}
