#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define DELAY 10
#define READ_BUTTON !bit_is_clear(PINA, PA5)
#define TRUE 1
#define FALSE 0

static int interrupted;

ISR(PCINT0_vect) { interrupted = TRUE; }

void handleInterrupt0(void) { 
  int i=0;
 if (READ_BUTTON) {
  //  for(i=0;i<3;i++){
  //     _delay_ms(1);
  //     if(! READ_BUTTON)return;
  //  }
  PORTB |= 1<<PB2; 
  _delay_ms(DELAY);
  PORTB &= ~(1<<PB2);  
 } else {
   //PORTB &= ~(1<<PB2); 
 }
 
}

void initInterrupt0(void) {
  GIMSK |= _BV(PCIE0);   // Enable Pin Change Interrupts
  PCMSK0 |= _BV(PCINT5); // Use PA5 as interrupt pin
	sei(); 
}

int main(void) {
  // -------- Inits --------- //
  DDRA |= 1 << PA7;
  DDRB |= 1 << PB2; 
  DDRA &= ~(1<<PA5); 
  PORTA |= 1<<PA7;
  initInterrupt0();
  // ------ Event loop ------ //
  while (1) {
    if(interrupted){
      handleInterrupt0();
      interrupted = FALSE;
    }
    _delay_ms(DELAY);
  } /* End event loop */

 return (0); /* This line is never reached */
}
