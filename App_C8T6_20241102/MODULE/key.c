#include "key.h"
#include "delay.h"
#include "led.h"
#include "uart.h"
#include "rc522.h"
#include "systask.h"

/*****************************************************************************
 * @name       :void KEY_Init(void)
 * @date       :2018-08-09 
 * @function   :Initialization key GPIO
 * @parameters :None
 * @retvalue   :None
******************************************************************************/ 
void Key_Init(void)
{
    
    GPIO_InitTypeDef  GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
    
     //打开GPIO口时钟，先打开复用才能修改是否停用复用功能
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
    //关闭JTAG，使能SWD
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
    

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15|GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);
 
} 

/*****************************************************************************
 * @name       :u8 KEY_Scan(void)
 * @date       :2018-08-09 
 * @function   :Key processing,Response priority:KEY0>KEY1>WK_UP!!
 * @parameters :None
 * @retvalue   :0-No buttons were pressed.
                                1-The KEY0 button is pressed
                                2-The KEY1 button is pressed
                                3-The KEY2 button is pressed
                                4-The WK_UP button is pressed
******************************************************************************/ 
u8 ScanKey(void)
{
    K1 = KEY1;
    if (!KEY1) {
        delay_ms(10);
        CurrentState = VALIDATION_LOCAL;
        while(!KEY1);
    }
	else if (!KEY2) {
        delay_ms(10);
        WriteFlag = 1;
        while(!KEY2);
    }
	else if (A1&&!A2&&!A3&&A4) {
        WriteFlag = 1;
        K1 = 0;
        K4 = 0;
        delay_ms(50);
        K1 = 1;
        K4 = 1;
    }
    else if (!A1&&A2&&A3&&!A4) {
        CurrentState = VALIDATION_REMOTE;
    }
    else if (A1&&A2&&A3&&A4) {
        CurrentState = CARD_DISABLE;
    } else {
        CurrentState = NORMAL;
    }
    return 0;
}




