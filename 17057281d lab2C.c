/*
 * Lab2C.c
 *
 * Created: 9/30/2018 5:03:03 PM
 * Author : user
 */ 

#include <avr/io.h>


int main(void)
{
	DDRD = 0x00;
	DDRC = 0x01;

	while (1)
	{	
		TCCR1A = 0x00;
		TCCR1B = 0x0F;
		TCNT1L = 0x00;
		TCNT1H = 0x00;
		OCR1AH = 0x00;
		OCR1AL = 0x02;
		while ((TIFR1&(1<<OCF1A))==0);
		TIFR1 = (1<<OCF1A);
		PORTC = PORTC^(1<<0);
	}
}

