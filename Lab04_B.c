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
	
	unsigned char toSend_1[14] = "We Are Ready! ";
	unsigned char toSend_2[5] = "Bye! ";
	
	unsigned char status = 0;
	
	for(int i=0; i<14; i++){
		sender(toSend_1[i]);
	}
	
    while(1){
		if(receiver() == 'H' && status == 0){
			status++;
		}
		
		if(receiver() == 'i' && status == 1){
			status = 0;
			for(int i=0; i<5; i++){
				sender(toSend_2[i]);
			}
		}	   
    }
}