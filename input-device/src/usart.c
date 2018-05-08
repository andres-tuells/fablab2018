///////*********************************///////
///*** microcontroladores-mrelberni.com ***////
///////*****************************//////////
//* USART AVR ejemplos 1 código para el AVR1* //
///////********************************///////
 
#include <avr/io.h>
#include <stdio.h>
#include "usart.h"  //archivo de cabecera para utilizar el módulo USART AVR
 
int main(void)
{
	DDRB&=~((1<<0)|(1<<1));//PB0 y PB1 como entradas digitales para los pulsadores
	PORTB|=((1<<0)|(1<<1));//habilita las resitencias internas pull up de PB0 y PB1
	
	iniciar_usart();//inicia el módulo USART AVR
	
    while(1)
    {
        if(!(PINB&(1<<0))){//si se preciona el pulsador para encender el led
	        envia_caracter_usart('e');//se transmitirá el caracter 'e' hacia PIC 2
        }
		
        if(!(PINB&(1<<1))){//si se preciona el pulsador para apagar el led
	        envia_caracter_usart('a');//se transmitirá el caracter 'a' hacia PIC 2
        }
	}
}