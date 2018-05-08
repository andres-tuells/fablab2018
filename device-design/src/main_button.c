// ------- Preamble -------- //
#define F_CPU 20000000
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */
#define DELAY 10
#define READ_BUTTON bit_is_clear(PINA, PA5)
#define TRUE 1
#define FALSE 0

//NEED of a pullup resistor for button

int main(void) {

  // -------- Inits --------- //
  DDRA |= 1 << PA7;
  DDRB |= 1 << PB2; 
  DDRA &= ~(1<<PA5);       

  int buttonOn = FALSE;
  int counter = 0;
  int i = 0;
  // ------ Event loop ------ //
  while (1) {
    buttonOn = FALSE;

    if (READ_BUTTON){
      _delay_ms(3);
      if(READ_BUTTON)buttonOn=TRUE;
    }

    if (buttonOn){
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
