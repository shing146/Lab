#include "stm32f10x.h"                  // Device header

int state=0;

int main(){
	//setup
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef LED_Init;
	LED_Init.GPIO_Pin = GPIO_Pin_8;
	LED_Init.GPIO_Speed = GPIO_Speed_2MHz;
	LED_Init.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &LED_Init);
	//defind the GPIO pin
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseInitTypeDef TIM2_Init;
	TIM2_Init.TIM_Prescaler	= 0;
	TIM2_Init.TIM_Period = 3-1;
	TIM2_Init.TIM_CounterMode = TIM_CounterMode_Up;
	TIM2_Init.TIM_ClockDivision = 0;
	TIM2_Init.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM2_Init);
	TIM_Cmd(TIM2, ENABLE);
	//defind the Timer 2
	
	TIM_TIxExternalClockConfig(TIM2, TIM_TIxExternalCLK1Source_TI2, TIM_ICPolarity_Rising, 0);	//
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);	//Enable update Timer 2
	NVIC_EnableIRQ(TIM2_IRQn);	//Enable Interrupt
	
	while(1){}
}

void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET){
		
		if(state == 0){
			GPIO_WriteBit(GPIOB, GPIO_Pin_8, RESET);
			state = 1;
		}else{
			GPIO_WriteBit(GPIOB, GPIO_Pin_8, SET);
			state = 0;
		}

		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}