// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */


int main(void) {

  // -------- Inits --------- //
  DDRA |= 1 << PA7;            

  // ------ Event loop ------ //
  while (1) {

    PORTA |= 1 << PA7;         
    _delay_ms(1000);                                           

    PORTA &= ~(1<<PA7); 
    _delay_ms(1000);                                          
  }                                                  
  return 0;                            
}
