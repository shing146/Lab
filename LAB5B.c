#include "stm32f10x.h"                  // Device header

void delay(int t) {
	int i, j;
	for(i=0; i<t; i++)
		j++;
}

int main(void) {
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	while(1) {
		GPIO_WriteBit(GPIOD,GPIO_Pin_2,Bit_SET);
		delay(10000000);
		GPIO_WriteBit(GPIOD,GPIO_Pin_2,Bit_RESET);
		delay(10000000);
	}
}