#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "uart.h"
#include "string.h"
#include "oled.h"
#include "stmflash.h"
#include "stdlib.h"
#include "stdio.h"

/*********************移植时务必注意修改************************/
//务必注意修改 FLASH_APP_ADDR 0x08006000 //第一个应用程序起始地址(存放在FLASH)
//务必注意修改 STM32_FLASH_SIZE 128 //所选STM32的FLASH容量大小(单位为K)
/***************************************************************/
extern u8 FunCode;
extern u16 FileLength;
extern u16 Progress;

int main(void)
{
    
    char* text = (char*)malloc(20 *sizeof(char));
    NVIC_SetVectorTable(STM32_FLASH_BASE, FLASH_APP_OFFSET);
    delay_init(); //必须要调用，否则延时不准确
    UART_Init(115200); //串口初始化
    LED_Init(); //LED初始化
    OLED_Init();
    OLED_Fill(0xff);
    delay_ms(1000);
    delay_ms(1000);
    OLED_Fill(0x00);
    while(1)
    {
        OLED_ClearStrBuff();
        OLED_InsertStr(0, 0, "DOWNLOAD APP!!!", 1);
        OLED_InsertStr(0, 1, text, 1);
        OLED_TwoLineCenterValidate();
        delay_ms(10);
    }
}

