/*
 * Lab02A2.c
 *
 * Created: 3/10/2018 0:22:53
 * Author : NSK
 */ 

#include <avr/io.h>

void timer1Delay(int ms)
{
	for (int i = 0; i < ms; i++)
	{
		while (!(TIFR1&(1<<OCF1A)));
		TIFR1 = 1 << OCF1A;
	}
}

int main(void)
{
	DDRB = 0x01;
	TCCR1B = 0x0B;
	OCR1A = 250;
	while(1)
	{
		PORTB ^= 0x01;
		timer1Delay(1000);
	}
}
