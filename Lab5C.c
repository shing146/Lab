#include "stm32f10x.h"                  // Device header

static __IO uint32_t msTicks;

void delayms(uint32_t ms){
	msTicks = ms;
	while(msTicks);
}

void SysTick_Handler(){
	if(msTicks != 0)
		msTicks--;
}

int main(){
	//setup
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);	//Ticks per 1 ms
	
	while(1){
		//program run here
		GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
		delayms(500);
		GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);
		delayms(500);
	}
}
