#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "uart.h"
#include "string.h"
#include "oled.h"
#include "stmflash.h"
#include "stdlib.h"
#include "stdio.h"

/*********************��ֲʱ���ע���޸�************************/
//���ע���޸� FLASH_APP_ADDR 0x08006000 //��һ��Ӧ�ó�����ʼ��ַ(�����FLASH)
//���ע���޸� STM32_FLASH_SIZE 128 //��ѡSTM32��FLASH������С(��λΪK)
/***************************************************************/
extern u8 FunCode;
extern u16 FileLength;
extern u16 Progress;

int main(void)
{
    
    char* text = (char*)malloc(20 *sizeof(char));
    NVIC_SetVectorTable(STM32_FLASH_BASE, FLASH_APP_OFFSET);
    delay_init(); //����Ҫ���ã�������ʱ��׼ȷ
    UART_Init(115200); //���ڳ�ʼ��
    LED_Init(); //LED��ʼ��
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

