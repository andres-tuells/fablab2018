// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */
#define F_CPU 20000000
#define DELAY 10

//bouncing problem

int main(void) {

  // -------- Inits --------- //
  DDRA |= 1 << PA7;
  DDRB |= 1 << PB2; 
  DDRA &= ~(1<<PA5);       

  // ------ Event loop ------ //
  while (1) {
    if (bit_is_clear(PINA, PA5)){
      PORTB &= ~(1<<PB2);
      PORTA &= ~(1<<PA7);        
      _delay_ms(DELAY);                                           
      PORTA |= 1 << PA7;
      _delay_ms(DELAY);      
    }else{
      PORTA &= ~(1<<PA7);
      PORTB &= ~(1<<PB2);        
      _delay_ms(DELAY);                                           
      PORTB |= 1 << PB2;
      _delay_ms(DELAY); 
    }
                                         
  }                                                  
  return 0;                            
}
