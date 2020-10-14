/*
 * Lab02A1.c
 *
 * Created: 3/10/2018 0:16:01
 * Author : NSK
 */ 
#include <avr/io.h>

void timer1Delay(int ms)
{
	for (int i = 0; i < ms; i++)
	{
		TCNT1 = 0xFF06;
		while (!(TIFR1&(1<<TOV1)));
		TIFR1 = 1 << TOV1;
	}
}

int main(void)
{
	DDRB = 0x01;
	TCCR1B = 0x03;
	while(1)
	{
		PORTB ^= 0x01;
		timer1Delay(1000);
	}
}