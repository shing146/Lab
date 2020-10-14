/*
 * Lab2B-2.c
 *
 * Created: 9/26/2018 8:41:48 PM
 * Author : user
 */ 

 //THIS IS CTC MODE

#include <avr/io.h>

void T0Delay1Sec()
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

void T0DelayOneThirdSec()
{
	for(int i = 0; i < 3000; i++)
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
	DDRB = 0xFF;
	DDRC = 0xFF;
	unsigned char state = 0;
	while(1)
	{
		switch(state) {
			case 0:
			PORTB = 0x21;
			PORTC = 0x20;
			T0Delay1Sec();
			T0Delay1Sec();
			T0Delay1Sec();
			T0Delay1Sec();
			T0Delay1Sec();
			state = 1;
			break;

			case 1:
			PORTB = 0x11;
			PORTC = 0x20;
			T0Delay1Sec();
			state = 2;
			break;

			case 2:
			PORTB = 0x09;
			PORTC = 0x20;
			T0Delay1Sec();
			state = 3;
			break;

			case 3://
			PORTB = 0x0B;
			PORTC = 0x20;
			T0Delay1Sec();
			state = 4;
			break;

			case 4:
			PORTB = 0x0C;
			PORTC = 0x10;
			T0Delay1Sec();
			T0Delay1Sec();
			T0Delay1Sec();
			T0Delay1Sec();
			T0Delay1Sec();
			state = 5;
			break;

			case 5:
			PORTB = 0x0A;
			PORTC = 0x10;
			T0DelayOneThirdSec();
			PORTC = 0x00;
			T0DelayOneThirdSec();
			PORTC = 0x10;
			T0DelayOneThirdSec();
			PORTC = 0x00;
			T0DelayOneThirdSec();
			PORTC = 0x10;
			state = 6;
			break;

			case 6:
			PORTB = 0x09;
			PORTC = 0x20;
			T0Delay1Sec();
			state = 7;
			break;

			case 7:
			PORTB = 0x19;
			PORTC = 0x20;
			T0Delay1Sec();
			state = 0;
			break;

		}

	}

}