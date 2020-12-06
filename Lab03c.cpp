/*
 * Lab03c.cpp
 *
 * Created: 10/24/2018 9:58:05 AM
 * Author : 17060506d
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char state = 0;
unsigned int i = 0;

ISR(INT1_vect)
{
	if (state == 25)
	{
		state = 0;
		TCCR1B = 0x0C;
		OCR1A = 62500;
		TIMSK1 = (1<<OCIE1A);
	}
	else
	{
		state = 25;
		TCCR1B = 0x00;
		PORTB = 0x00;
		PORTC = 0x00;
	}
}

ISR(TIMER1_COMPA_vect)
{
	if (state < 24)
		state++;
	else
		state = 0;
	
	if (state >= 13 && state <	23)
		PORTC ^= 0x10;
}

int main(void)
{
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;

	TCCR1B = 0x0C;						
	OCR1A = 62500;
	TIMSK1 = (1<<OCIE1A);

	EIMSK = (1<<INT1);
	EICRA = 0x08;

	sei();
	while(1)
	{
		if (state == 0)
		{
			PORTB = 0x0C;
			PORTC = 0x20;
		}
		else if (state == 5)
		{
			PORTB = 0x14;
		}
		else if (state == 6)
		{
			PORTB = 0x24;
		}
		else if (state == 7)
		{
			PORTB = 0x26;
		}
		else if (state == 8)
		{
			PORTB = 0x21;
			PORTC = 0x10 | (PINC & 0x01);
		}
		else if (state == 13)
		{
			OCR1A = 6250;
			PORTB = 0x22;
		}
		else if (state == 23)
		{
			OCR1A = 62500;
			PORTB = 0x24;
			PORTC = 0x20 | (PINC & 0x01);
		}
		else if (state == 24)
		{
			PORTB = 0x34;
		}
	}
}



