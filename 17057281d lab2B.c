/*
 * Lab2B-1.c
 *
 * Created: 9/26/2018 9:55:04 AM
 * Author : 17057281d
 */ 

 //THIS IS NORMAL MODE

#include <avr/io.h>

void T0Delay1Sec(int times)
{
	for(int i = 0; i < (1000*times); i++)
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

void T0DelayOneThirdSec()
{
	for(int i = 0; i < 300; i++)
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
			T0Delay1Sec(5);
			state = 1;
			break;

			case 1:
			PORTB = 0x11;
			PORTC = 0x20;
			T0Delay1Sec(2);
			state = 2;
			break;

			case 2:
			PORTB = 0x09;
			PORTC = 0x20;
			T0Delay1Sec(2);
			state = 3;
			break;

			case 3://
			PORTB = 0x0B;
			PORTC = 0x20;
			T0Delay1Sec(2);
			state = 4;
			break;

			case 4:
			PORTB = 0x0C;
			PORTC = 0x10;
			T0Delay1Sec(5);
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
			T0DelayOneThirdSec();
			PORTC = 0x00;
			state = 6;
			break;

			case 6:
			PORTB = 0x09;
			PORTC = 0x20;
			T0Delay1Sec(2);
			state = 7;
			break;

			case 7:
			PORTB = 0x19;
			PORTC = 0x20;
			T0Delay1Sec(2);
			state = 0;
			break;

			}

	}

}

