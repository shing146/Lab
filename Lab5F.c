#include "stm32f10x.h"                  // Device header

#define Light3_R GPIOA,GPIO_Pin_5
#define Light3_Y GPIOA,GPIO_Pin_6
#define Light3_G GPIOA,GPIO_Pin_7

#define Light2_R GPIOB,GPIO_Pin_6
#define Light2_Y GPIOA,GPIO_Pin_9
#define Light2_G GPIOA,GPIO_Pin_8

#define Light1_R GPIOB,GPIO_Pin_5
#define Light1_G GPIOA,GPIO_Pin_10

	
int time = 0;
int state = 0;

void ClearAllLED(){
	
	GPIO_WriteBit(Light3_R,Bit_RESET);
	GPIO_WriteBit(Light3_Y,Bit_RESET);
	GPIO_WriteBit(Light3_G,Bit_RESET);
	GPIO_WriteBit(Light2_R,Bit_RESET);
	GPIO_WriteBit(Light2_Y,Bit_RESET);
	GPIO_WriteBit(Light2_G,Bit_RESET);
	GPIO_WriteBit(Light1_R,Bit_RESET);
	GPIO_WriteBit(Light1_G,Bit_RESET);
	
}

void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET){
		
		if(time == 160){	time = 0; }
		else{	time++; }
		
		if(130<=time && time<140){
			if(state == 1) { state = 0; }
			else{ state = 1; }
			GPIO_WriteBit(Light1_G,state);
		}
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

int main(){
	//setup
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef LED_Init;
	LED_Init.GPIO_Pin = GPIO_Pin_All;
	LED_Init.GPIO_Speed = GPIO_Speed_2MHz;
	LED_Init.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &LED_Init);
	GPIO_Init(GPIOB, &LED_Init);
	//defind the GPIO pin
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseInitTypeDef TIM2_Init;
	TIM2_Init.TIM_Prescaler	= 18000-1; // 72Mhz*0.25ms = 18000
	TIM2_Init.TIM_Period = 400-1;	// 100ms/0.25ms = 400
	TIM2_Init.TIM_CounterMode = TIM_CounterMode_Up;
	TIM2_Init.TIM_ClockDivision = 0;
	TIM2_Init.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM2_Init);
	TIM_Cmd(TIM2, ENABLE);
	//defind the Timer 2

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);	//Enable update Timer 2
	NVIC_EnableIRQ(TIM2_IRQn);
	
	while(1){
		//run here
		if(0<=time && time<50){
			GPIO_WriteBit(Light2_R,0);
			GPIO_WriteBit(Light2_Y,0);
			
			GPIO_WriteBit(Light1_R,1);
			GPIO_WriteBit(Light2_G,1);
			GPIO_WriteBit(Light3_R,1);
		}
		
		if(50<=time && time<60){
			GPIO_WriteBit(Light2_G,0);
			
			GPIO_WriteBit(Light1_R,1);
			GPIO_WriteBit(Light2_Y,1);
			GPIO_WriteBit(Light3_R,1);
		}
		
		if(60<=time && time<70){
			GPIO_WriteBit(Light2_Y,0);
			
			GPIO_WriteBit(Light1_R,1);
			GPIO_WriteBit(Light2_R,1);
			GPIO_WriteBit(Light3_R,1);
		}
		
		if(70<=time && time<80){
			GPIO_WriteBit(Light1_R,1);
			GPIO_WriteBit(Light2_R,1);
			GPIO_WriteBit(Light3_R,1);
			GPIO_WriteBit(Light3_Y,1);
		}
		
		if(80<=time && time<130){
			GPIO_WriteBit(Light1_R,0);
			GPIO_WriteBit(Light3_R,0);
			GPIO_WriteBit(Light3_Y,0);
			
			GPIO_WriteBit(Light1_G,1);
			GPIO_WriteBit(Light2_R,1);
			GPIO_WriteBit(Light3_G,1);
		}
		
		if(130<=time && time<140){
			GPIO_WriteBit(Light3_G,0);
			
			//Light1_G is blinking
			GPIO_WriteBit(Light2_R,1);
			GPIO_WriteBit(Light3_Y,1);
		}
		
		if(140<=time && time<150){
			GPIO_WriteBit(Light1_G,0);
			GPIO_WriteBit(Light3_Y,0);
			
			GPIO_WriteBit(Light1_R,1);
			GPIO_WriteBit(Light2_R,1);
			GPIO_WriteBit(Light3_R,1);
		}
		
		if(150<=time && time<160){
			GPIO_WriteBit(Light1_R,1);
			GPIO_WriteBit(Light2_R,1);
			GPIO_WriteBit(Light2_Y,1);
			GPIO_WriteBit(Light3_R,1);
		}
	}
}