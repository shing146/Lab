/*
 * Lab04_B.c
 *
 * Created: 4/11/2019 22:03:52
 *  Author: thomas
 */ 


#include <avr/io.h>

void sender(unsigned char s){
	while( !(UCSR0A & (1<<UDRE0)) );
	UDR0 = s; 
}

unsigned char receiver(){
	while( !(UCSR0A & (1<<RXC0)) );
	return UDR0;
}

int main(void)
{
	UCSR0B = 1<<RXEN0 | 1<<TXEN0;
	UCSR0C = 1<<UCSZ01 | 1<<UCSZ00;
	UBRR0 = 0xCF;
	
	unsigned char word;
	
    while(1){
		word = receiver();
		sender(word);	  
    }
}