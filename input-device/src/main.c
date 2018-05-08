// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */


void initADC()
{
  /* this function initialises the ADC 

        ADC Prescaler Notes:
	--------------------

	   ADC Prescaler needs to be set so that the ADC input frequency is between 50 - 200kHz.
  
           For more information, see table 17.5 "ADC Prescaler Selections" in 
           chapter 17.13.2 "ADCSRA – ADC Control and Status Register A"
          (pages 140 and 141 on the complete ATtiny25/45/85 datasheet, Rev. 2586M–AVR–07/10)

           Valid prescaler values for various clock speeds
	
	     Clock   Available prescaler values
           ---------------------------------------
             1 MHz   8 (125kHz), 16 (62.5kHz)
             4 MHz   32 (125kHz), 64 (62.5kHz)
             8 MHz   64 (125kHz), 128 (62.5kHz)
            16 MHz   128 (125kHz)

           Below example set prescaler to 128 for mcu running at 8MHz
           (check the datasheet for the proper bit values to set the prescaler)
  */

  // 8-bit resolution
  // set ADLAR to 1 to enable the Left-shift result (only bits ADC9..ADC2 are available)
  // then, only reading ADCH is sufficient for 8-bit results (256 values)
  ADMUX = 0b00000110;

  ADCSRA = 
            (1 << ADEN)  |     // Enable ADC 
            (1 << ADPS2) |     // set        prescaler to 64, bit 2 
            (1 << ADPS1) |     // set prescaler to 64, bit 1 
            (0 << ADPS0);      // set prescaler to 64, bit 0  
}


int main(void) {

  // -------- Inits --------- //
  DDRA |= 1 << PA7;
  DDRB |= 1 << PB2;    
  PORTA |= 1 << PA7; 
  initADC();       

  // ------ Event loop ------ //
  while (1) {

    ADCSRA |= (1 << ADSC);         // start ADC measurement
    while (ADCSRA & (1 << ADSC) ); // wait till conversion complete 

    if (ADCH > 128){
      PORTB &= ~(1<<PB2);
    } else { 
      PORTB |= 1 << PB2;
    }                                        
  }                                                  
  return 0;                            
}
