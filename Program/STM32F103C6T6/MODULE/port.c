#include "port.h"
#include "delay.h"

extern u8 ConsumeFlag, RechargeFlag;
extern int Amount;


void Port_Init(void){
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB, GPIO_Pin_8|GPIO_Pin_12);
	
	
}


void BuzzerRing(u8 times){
	times *= 2;
	while (times--) {
//		BUZZER = !BUZZER;
		delay_ms(100);
	
	}
}

void ScanKey(void) {
	if (!KEY1) {
		RechargeFlag = 1;
		Amount = 10;
	}
	if (!KEY2) {
		delay_ms(10);
		if (!KEY2) {
			ConsumeFlag = !ConsumeFlag;
			Amount = 20;
			while (!KEY2);
		}
	}
}





