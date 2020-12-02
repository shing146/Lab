#include "stm32f10x.h"                  // Device header

void delay(int t){
	int i;
	for(i=0; i<t; i++);
}

int main(){
	//setup
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	while(1){
	//program run here
		GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
		delay(4000000);
		GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);
		delay(4000000);
	}
}
