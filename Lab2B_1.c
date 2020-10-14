/*
 *(light2_RYG)(light3_RYG)
 *(light1_GR)	
 */ 


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
		Timer1_Delay_s(5);
		
		PORTC = 1<<4;
		PORTB = 0b010100;
		Timer1_Delay_s(1);
		
		PORTC = 1<<4;
		PORTB = 0b100100;
		Timer1_Delay_s(1);
		
		PORTC = 1<<4;
		PORTB = 0b100110;
		Timer1_Delay_s(1);
		
		PORTC = 1<<5;
		PORTB = 0b100001;
		Timer1_Delay_s(5);
		
		PORTB = 0b100010;
		PORTC &= 0<<5;
		
		for(i=0;i<20;i++){
			Timer0_Delay_ms(50);
			PORTC ^= 1<<5;
		}
		
		PORTC = 1<<4;
		PORTB = 0b100100;
		Timer1_Delay_s(1);
		
		PORTC = 1<<4;
		PORTB = 0b110100;
		Timer1_Delay_s(1);
    }
}