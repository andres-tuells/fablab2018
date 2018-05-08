////////////////////////////////////////////////////////////////////
//Archivo de cabecera para el uso del módulo USART AVR con el ATMEL STUDIO///
///////////////////////////////////////////////////////////////////
 
#ifndef USART_H
#define	USART_H
 
void iniciar_usart();  //función para iniciar el USART AVR asíncrono, 8 bits, 9600 baudios,
                       //sin bit de paridad, 1 bit de parada
					   
unsigned char recibe_caracter_usart();     //función para la recepción de caracteres
void envia_caracter_usart(unsigned char);  //función para la transmisión de caracteres
void envia_cadena_usart(char*);            //función para la transmisión de cadenas de caracteres
 
/////////////////////////////////////////////
//inicialización del módulo USART AVR modo asíncrono
//en una función, a 8bits,a 9600 baudios, sin bit de paridad
//1 bit de parada
/////////////////////////////////////////////////////
void iniciar_usart(){
	UCSR0B=0b00011000;	//transmisión y recepción habilitados a 8 bits
	UCSR0C=0b00000110;	//asíncrono, sin bit de paridad, 1 bit de parada a 8 bits
	UBRR0=51;			//para una velocidad de 9600 baudios con un oscilador de 8Mhz
}
 
///////////////////////////////////////////////////////////
///////////////////////////////////////////////
//recepción de datos del módulo USART AVR modo asíncrono
////////////////////////////////////////////////////////////
 
unsigned char recibe_caracter_usart(){
	if(UCSR0A&(1<<7)){  //si el bit7 del registro UCSR0A se ha puesto a 1
		return UDR0;    //devuelve el dato almacenado en el registro UDR0
	}
	else//sino
	return 0 ;//retorna 0
}
 
//////////////////////////////////////////////////////
///////////////////////////////////////////////
//transmisión de datos del módulo USART AVR modo asíncrono
///////////////////////////////////////////////
 
void envia_caracter_usart(unsigned char caracter){
	while(!(UCSR0A&(1<<5)));    // mientras el registro UDR0 esté lleno espera
	UDR0 = caracter;            //cuando el el registro UDR0 está vacio se envia el caracter
}
 
//////////////////////////////////////////////////////
//////////////////////////////////////////////
//transmisión de cadenas de caracteres con el módulo USART AVR modo asíncrono
///////////////////////////////////////////////
 
void envia_cadena_usart(char* cadena){	 //cadena de caracteres de tipo char
	while(*cadena !=0x00){				//mientras el último valor de la cadena sea diferente
		//a el caracter nulo
		envia_caracter_usart(*cadena);	//transmite los caracteres de cadena
		cadena++;						//incrementa la ubicación de los caracteres en cadena
		//para enviar el siguiente caracter de cadena
	}
}
 
#endif	/* USART_H */