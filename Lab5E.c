#include "stm32f10x.h"                  // Device header

int main(){
	//setup
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_InitTypeDef OnboardLED;
	OnboardLED.GPIO_Pin = GPIO_Pin_5;
	OnboardLED.GPIO_Mode = GPIO_Mode_Out_PP;
	OnboardLED.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &OnboardLED);

	GPIO_InitTypeDef OnboardButton;
	OnboardButton.GPIO_Pin = GPIO_Pin_13;
	OnboardButton.GPIO_Mode = GPIO_Mode_IPD;
	OnboardButton.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &OnboardButton);

	int state = 0;
	
	while(1){
		//run here
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 0){
			state = state^1;
			for(int i=0;i<2500000;i++);
		}
		
		if(state == 1){
			GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
		}else{
			GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);
		}
	}
}
