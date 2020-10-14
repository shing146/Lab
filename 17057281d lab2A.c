/*
 * Lab2A.c
 *
 * Created: 9/25/2018 8:38:51 PM
 * Author : user
 */ 

#include <avr/io.h>

void T0DelayNormal()
{
	for(int i = 0; i < 1000; i++)
	{
		TCNT0 = 0xF0;
		TCCR0A = 0x00;
		TCCR0B = 0x05;
		while((TIFR0&(1<<TOV0))==0);
		TCCR0A = 0x00;
		TCCR0B = 0x00;
		TIFR0 = 0x1;
	}
}

void T0DelayCTC()
{
	for(int i = 0; i < 10000; i++)
	{
		OCR0A = 0xFF;
		OCR0B = 0xFF;
		TCCR0A = 0x01;
		TCCR0B = 0x05;
		while((TIFR0&(1<<OCF0A))==0);
		TCCR0A = 0x00;
		TCCR0B = 0x00;
		TIFR0 = 0x02;
	}
}

int main(void)
{
	DDRB = 0x01;
	unsigned char state = 0;
	while(1)
	{

		if(state == 0)
		{
			PORTB = 0x01;
			state = 1;
			T0DelayCTC();
			// T0DelayNormal();
		}
		else
		{
			PORTB = 0x00;
			state = 0;
			T0DelayCTC();
			// T0DelayNormal();
		}
	}

}



/* Timer 0 and CTC mode

void T0DelayCTC()
{
	for(int i = 0; i < 10000; i++)
	{
		OCR0A = 0xFF;
		OCR0B = 0xFF;
		TCCR0A = 0x01;
		TCCR0B = 0x05;
		while((TIFR0&(1<<OCF0A))==0);
		TCCR0A = 0x00;
		TCCR0B = 0x00;
		TIFR0 = 0x02;
	}
}

int main(void)
{
	DDRB = 0x01;
	unsigned char state = 0;
	while(1)
	{

		if(state == 0)
		{
			PORTB = 0xFF;
			state = 1;
			T0DelayCTC();
		}
		else
		{
			PORTB = 0x00;
			state = 0;
			T0DelayCTC();
		}
	}

}
 */ 