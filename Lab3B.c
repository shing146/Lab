/*
 * Lab3A.c
 *
 * Created: 22/10/2019 21:46:10
 *  Author: thomas
 */ 
//0.1s = 6250 cycle (prescaler = 256)

#include <avr/io.h>
#include <avr/interrupt.h>

int isBetween(unsigned char stage,unsigned char a,unsigned char b){
	if(stage>=a && stage<b){return 1;}
		else{return 0;}
}

unsigned char time = 0;
unsigned char press_time = 0;

int main(void)
{
	DDRB = 0b00111111;
	DDRC = 0b00110001;
	DDRD = 1<<INT0;
	PORTC = 0x00;
	PORTB = 0x00;
	PORTD = 0x00;

	TCCR1A = 0b00000000;
	TCCR1B = 0b00001100;
	OCR1A = 6250;
	TIMSK1 = 1<<OCIE1A;
	
	EICRA = 0b00000010;
	EIMSK = 1<<INT0;
	
	sei();
    while(1)
    {
        if(isBetween(time,0,50)){
			PORTC |= 1<<4;
			PORTC &= ~(1<<5);
			PORTB = 0b001100;
		} else if (isBetween(time,50,60)){
			PORTC |= 1<<4;
			PORTC &= ~(1<<5);
			PORTB = 0b010100;
		} else if (isBetween(time,60,70)){
			PORTC |= 1<<4;
			PORTC &= ~(1<<5);
			PORTB = 0b100100;
		} else if (isBetween(time,70,80)){
			PORTC |= 1<<4;
			PORTC &= ~(1<<5);
			PORTB = 0b010100;
		} else if (isBetween(time,80,130)){
			PORTC |= 1<<5;
			PORTC &= ~(1<<4);
			PORTB = 0b100001;
		} else if (isBetween(time,130,140)){
			//Flashing
			PORTB = 0b100010;
		} else if (isBetween(time,140,150)){
			PORTC |= 1<<4;
			PORTC &= ~(1<<5);
			PORTB = 0b100100;
		}else if (isBetween(time,150,160)){
			PORTC |= 1<<4;
			PORTC &= ~(1<<5);
			PORTB = 0b110100;
		}
    }
}

ISR(TIMER1_COMPA_vect){
	if(time == 161){
		time = 0;
		}else{
		time++;
	}

	if(isBetween(time,130,140)){
		PORTC ^= 1<<5;
	}
}

ISR(INT0_vect){
	press_time++;
	if(press_time == 3){
		PORTC ^= 1<<0;
		press_time = 0;
	}
}