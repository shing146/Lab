/*
 * Lab2A_1.c
 *
 * Created: 27/9/2019 10:13:00
 *  Author: thomas
 */ 
//15625 times = 0x3D09
//tcnt0 = 
#include <avr/io.h>

void Timer1_Delay_s(int s){
	TCCR1B = 0x05;
	for(int i=0; i<s; i++){
		TCNT1 = 0xC2F6;
		while( (TIFR1 & (1<<TOV1)) == 0);
		TIFR1 = 1<<TOV1;
	}
	TCCR1B = 0x00;
}

void Timer0_Delay_ms(int ms){
	TCCR0B = 0x03;
	for(int i=0; i<ms; i++){
		TCNT0 = 0b100;
		while( (TIFR0 & (1<<TOV0)) == 0);
		TIFR0 = 1<<TOV0;
	}
	TCCR0B = 0x00;
}

int main(void)
{
	DDRB = 0x01;
	PORTB = 0;
		
    while(1)
    {
		Timer0_Delay_ms(1000);
		//Timer1_Delay_s(1);
		PORTB ^= 1<<0;
    }
}