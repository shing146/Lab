/*
 * Lab04_D_B.c
 *
 * Created: 6/11/2019 17:13:24
 *  Author: thomas
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char status=0;
unsigned char mode=1;

unsigned char toSend_1[14] = "We Are Ready! ";
unsigned char toSend_2[5] = "Bye! ";

int main(void)
{
	UCSR0B = 1<<RXEN0 | 1<<TXEN0 | 1<<RXCIE0 | 1<<UDRIE0;
	UCSR0C = 1<<UCSZ01 | 1<<UCSZ00;
	UBRR0 = 0xCF;

	sei();
	
    while(1)
    {

    }
}

ISR(USART_UDRE_vect){
	if(mode == 1){
		UDR0=toSend_1[status];
		if(status != 13){ status++; }
			else{
				status=0;
				mode=2;
			}
	}
	
	if(mode == 3){
		UDR0=toSend_2[status];
		if(status != 4){ status++; }
		else{
			status=0;
			mode=2;
		}
	}
}

ISR(USART_RX_vect){
	unsigned char dummy = UDR0;
	if(mode == 2){
		if(dummy == 'H' && status == 0){ status++; }
		if(dummy == 'i' && status == 1){
			status=0;
			mode=3;
		}
	}
}