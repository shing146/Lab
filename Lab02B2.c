/*
 * Lab02B2.c
 *
 * Created: 3/10/2018 0:53:59
 * Author : NSK
 */ 

 #include <avr/io.h>

void Delay(int ms)
{
	for (int i = 0; i < ms; i++)
	{
		while (!(TIFR1&(1<<OCF1A)));
		TIFR1 = 1 << OCF1A;
	}
}

int main(void)
{
	DDRB = 0xFF;
	DDRC = 0xFF;
	TCCR1B = 0x0B;
	OCR1A = 250;

	while(1)
	{
		PORTB = 0x0C;
		PORTC = 0x20;
		Delay(5000);

		PORTB = 0x14;
		Delay(1000);

		PORTB = 0x24;
		Delay(1000);

		PORTB = 0x26;
		Delay(1000);

		PORTB = 0x21;
		PORTC = 0x10;
		Delay(5000);

		PORTB = 0x22;
		for (int i = 0; i < 10; i++)
		{
			PORTC ^= 0x10;
			Delay(100);
		}

		PORTB = 0x24;
		PORTC = 0x20;
		Delay(1000);

		PORTB = 0x34;
		Delay(1000);
	}
}
