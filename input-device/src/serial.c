//
// Serials communications (TX only) with ATtiny84
//
// electronut.in
//

#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>
 
char pinTX = PA0;
volatile unsigned char currByte = 0;
volatile int sendingData = 0;

// initialize 
void init_serial()
{
  // set TX pin as output
  DDRA = (1 << pinTX);

  // set up timer1:
  cli();
  // 16 bit timer 
  // Divide by 1
  TCCR1B |= (1<<CS10);
  // Count cycles - (1/9600)*8000000 
  OCR1A = 833;   
  // Put Timer/Counter1 in CTC mode
  TCCR1B |= 1<<WGM12;
  // set interrupt flag
  TIMSK1 |= 1<<OCIE1A;
  sei();
}

// send a byte
void send_byte(char data)
{
  // set flag
  sendingData = 1;
  // set current data byte
  currByte = data;
  // wait till done
  while(sendingData);
}

// which bit was sent last? (0-10) 
// -1 implies none sent
volatile char bitNum = -1;

// 16-bit timer CTC handler - Interrupt Service Routine
ISR(TIM1_COMPA_vect)      
{
  // serial data sent as:
  //
  // 9600 8 N 1 
  //
  // start(low)-0-1-2-3-4-5-6-7-stop(high)-idle(high)-idle(high)
  // 12 bits sent per packet

  // idle => high
  if(!sendingData) {
    PORTA |= (1 << pinTX);
  }
  else {

    if(bitNum < 0) {
      // start bit - low
      PORTA &= ~(1 << pinTX);
      // set bit number
      bitNum = 0;
    }
    else if(bitNum >= 8) {      
      // stop bit - high
      PORTA |= (1 << pinTX);
      // increment
      bitNum++;

      // send 2 idle - high - bits
      // not necessary strictly speaking
      if(bitNum == 10) {
        // done 
        sendingData = 0;
        // unset bit number
        bitNum = -1;
      }
    }
    else { 
      // data bits:

      // bit num is in [0, 7]

      // extract relevant bit from data
      char dataBit = currByte & (1 << bitNum);
      if(dataBit) {
        PORTA |= (1 << pinTX);
      }
      else { 
        PORTA &= ~(1 << pinTX);
      }

      // update bit number
      bitNum++;
    }
  }
}


// write null terminated string
void send_str(const char* str)
{
  int len = strlen(str);
  int i;
  for (i = 0; i < len; i++) {
    send_byte(str[i]);
  }   
}


int main (void)
{
  DDRA |= 1 << PA7;
  DDRB |= 1 << PB2;    
  PORTA |= 1 << PA7;
  PORTB |= 1 << PB2;
  init_serial();

  int count = 10;
  // loop
  while (1) {

    // print count 
    char str[16];
    sprintf(str, "%d\n", count);
    if(count) {
      send_str(str);
      count--;
      PORTB &= ~(1 << PB2);
    }
    else {
      send_str("BOOM\n");
      count = 10;
      PORTB |= 1 << PB2;
    }

    _delay_ms(200);
  }
 
  return 1;
}