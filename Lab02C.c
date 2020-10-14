/*
 * Lab02C.c
 *
 * Created: 10/3/2018 9:41:16 AM
 * Author : 17060506d
 */ 

#include <avr/io.h>

int main(void)
{
	DDRC = 0xFF;
	DDRD = 0xFF;

	TCCR1B = 0x0E;
	OCR1A = 2;

	unsigned char a = 0;

	while(1)
	{
		while (!(TIFR1&(1<<OCF1A)));
		TIFR1 = 1 << OCF1A;
		a ^= 0x01;
		
		if (a)
		PORTC = 0x01;
		else
		PORTC = 0x00;
	}
}
