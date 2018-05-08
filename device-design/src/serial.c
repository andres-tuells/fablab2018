#include <avr/io.h> 
#define F_CPU 16000000 
#define BUAD 9600 
#define BUAD_RATE_CALC ((F_CPU/16/BUAD) - 1)  

//Function definitions
void Setup(void);
void Loop(void);
void serialSetup(void);
void serialSend(char* sendString);

//Global variables.
char ar[]= "hello";

void Setup(){
    //Code to be run once (At start).
    DDRA |= 1 << PA7;
    DDRB |= 1 << PB2;  
    serialSetup();
    serialSend(ar);
}

void Loop(){
    serialSend(ar);
    PORTA |= 1 << PA7; 
    PORTB &= ~(1<<PB2);        
    _delay_ms(50);                                           

    PORTA &= ~(1<<PA7); 
    PORTB |= 1 << PB2;
    _delay_ms(50);
}

void serialSetup(){
    //Register settings
    //High and low bits
    UBRR0H = (BUAD_RATE_CALC >> 8); 
    UBRR0L = BUAD_RATE_CALC; 
    //transimit and recieve enable
    UCSR0B = (1 << TXEN0)| (1 << TXCIE0) | (1 << RXEN0) | (1 << RXCIE0); 
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  //8 bit data format
}

void serialSend(char* sendString){
     for (int i = 0; i < strlen(sendString); i++){ 
         while (( UCSR0A & (1<<UDRE0))  == 0){};
         UDR0 = sendString[i]; 
     } 
}

int main(void){  
    Setup();
    while(1){
       Loop();
    }
while(1){}//If you ever return from Loop(); This while will catch you, so it won't continue doing randomness.           
}  