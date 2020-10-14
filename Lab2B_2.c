/*
* Lab2B_2.c
*
* Created: 6/10/2019 13:55:26
*  Author: thomas
*/


#include <avr/io.h>
unsigned char time;

void Timer1_Delay_CTC_s(unsigned char s){
	//in CTC mode
	TCCR1A = 0b00000000;	//setup Timer1
	TCCR1B = 0b00001101;	//setup Timer1
	for(time=0; time<s; time++){
		TCNT1 = 0x00;
		OCR1A = 0x3D09;
		while( (TIFR1 & (1<<OCF1A)) == 0);
		TIFR1 = 1<<OCF1A;
	}
	TCCR1A=0x00;	//close Timer1
	TCCR1B=0x00;	//close Timer1
}

void Timer0_Delay_CTC_ms(unsigned char ms){
	TCCR0A = 0b00000010;
	TCCR0B = 0b00000011;
	for(time=0; time<ms; time++){
		TCNT0 = 0x00;
		OCR0A = 0xFA;
		while( (TIFR0 & (1<<OCF0A)) == 0);
		TIFR0 = 1<<OCF0A;
	}
	TCCR0A = 0x00;
	TCCR0B = 0x00;
}

int main(void)
{

	unsigned char i;
	
	DDRB = 0b00111111;
	PORTB = 0x00;
	
	DDRC = 0b00110000;
	PORTC = 0x00;
	
	while(1)
	{
		//(light2_RYG)(light3_RYG)
		//(light1_GR)
		PORTC = 1<<4;
		PORTB = 0b001100;
		Timer1_Delay_CTC_s(5);
		
		PORTC = 1<<4;
		PORTB = 0b010100;
		Timer1_Delay_CTC_s(1);
		
		PORTC = 1<<4;
		PORTB = 0b100100;
		Timer1_Delay_CTC_s(1);
		
		PORTC = 1<<4;
		PORTB = 0b100110;
		Timer1_Delay_CTC_s(1);
		
		PORTC = 1<<5;
		PORTB = 0b100001;
		Timer1_Delay_CTC_s(5);
		
		PORTB = 0b100010;
		PORTC &= 0<<5;
		
		for(i=0;i<20;i++){
			Timer0_Delay_CTC_ms(50);
			PORTC ^= 1<<5;
		}
		
		PORTC = 1<<4;
		PORTB = 0b100100;
		Timer1_Delay_CTC_s(1);
		
		PORTC = 1<<4;
		PORTB = 0b110100;
		Timer1_Delay_CTC_s(1);
	}
}