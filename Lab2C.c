/*
* Lab2C.c
*
* Created: 6/10/2019 15:13:08
*  Author: thomas
*/


#include <avr/io.h>

int main(void)
{
	DDRC = 0x01;
	PORTC = 0x01;
	DDRD = 1<<5;
	
	TCCR0A = 0b00000010;
	TCCR0B = 0b00000110;
	while(1)
	{
		TCNT0 = 0x00;
		OCR0A = 0x02;
		while ((TIFR0 & (1<<OCF0A)) == 0);
		TIFR0 |= 1<<OCF0A;
		PORTC ^= 1<<0;
	}
}