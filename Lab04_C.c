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
	UBRR0 = 103;
	
	unsigned char dummy;
	
	while(1){
		
		if( !(UCSR0A & (1<<RXC0)) ){
			sender('a');
		}else{
			dummy = UDR0;
			for(int i=0; i<10; i++){ sender(dummy); }
			while(receiver() != dummy);
		}

    }
}