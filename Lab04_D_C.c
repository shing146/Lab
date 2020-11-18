/*
 * Lab04_D_B.c
 *
 * Created: 6/11/2019 17:13:24
 *  Author: thomas
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char mode=1;
unsigned char dummy;
unsigned char counter=0;

int main(void)
{
	UCSR0B = 1<<RXEN0 | 1<<TXEN0 | 1<<RXCIE0 | 1<<UDRIE0;
	UCSR0C = 1<<UCSZ01 | 1<<UCSZ00;
	UBRR0 = 103;

	sei();
	
    while(1)
    {

    }
}

ISR(USART_UDRE_vect){
	if(mode == 1){
		UDR0='a';
	}
	if(mode == 2){
		if(counter == 10){
			mode=3;
			counter=0;
		}else{
			counter = counter+1;
			UDR0=dummy;
		}
	}
}

ISR(USART_RX_vect){
	if(mode == 1){
		dummy=UDR0;
		mode=2;
	}
	if(mode == 3){
		if(UDR0 == dummy){ mode=1; }
	}
}