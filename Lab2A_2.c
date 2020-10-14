/*
 * Lab2A_1.c
 *
 * Created: 27/9/2019 10:13:00
 *  Author: thomas
 */ 
//15625 times = 0x3D09

#include <avr/io.h>

void Timer1_CTC_Delay_s(int s){
	//in CTC mode
	for(int i=0; i<s; i++){
		TCNT1 = 0x00;
		OCR1A = 0x3D09;
		while( (TIFR1 & (1<<OCF1A)) == 0);
		TIFR1 = 1<<OCF1A;
	}
	
}

int main(void)
{
	DDRB = 0x01;
	PORTB = 0;
	
	TCCR1A = 0b00000000;	//setup Timer1
	TCCR1B = 0b00001101;	//setup Timer1
	
    while(1)
    {
		Timer1_CTC_Delay_s(1);
		PORTB ^= 1<<0;
    }
}