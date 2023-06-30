#include "key.h"
#include "delay.h"
#include "led.h"
#include "uart.h"

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

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
 
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
u8 ScanKey(u8 mode)
{
    if (!KEY1) {
        LED_RED = 0;
    } else {
        LED_RED = 1;
    }
    if (!KEY2) {
        LED_GREEN = 0;
    } else {
        LED_GREEN = 1;
    }
    return 0;
}




