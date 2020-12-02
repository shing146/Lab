#include "stm32f10x.h"                  // Device header
#include "string.h"

unsigned char flag;
int mode=0;
int time=0;

int main(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//Enable A2 as Tx

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	//Enable A3 as Rx
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
	USART_Init(USART2, &USART_InitStructure);
	USART_Cmd(USART2, ENABLE);
	
	
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART2,USART_IT_TC,ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//enable interrputer
		
	while(1){}
}

void USART2_IRQHandler() {
	if(USART_GetITStatus(USART2, USART_IT_TC) != RESET) {
		if(mode == 0){ USART_SendData(USART2, 'a'); }
		
		if(mode == 1 && time < 10){
			USART_SendData(USART2, flag);
			time++;
		}
		
		if(mode == 1 && time >= 10){
			mode++;
		}
	}
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
		if(mode == 0){
			time = 0;
			flag = (unsigned char)USART_ReceiveData(USART2);
			mode = 1;
		}
		
		if(mode == 2){
			if(USART_ReceiveData(USART2) == flag){ mode = 0; }
		}
	}	
}