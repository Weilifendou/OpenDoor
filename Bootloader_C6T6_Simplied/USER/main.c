#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "uart.h"
#include "string.h"
#include "oled.h"
#include "stmflash.h"

/*********************��ֲʱ���ע���޸�************************/
//���ע���޸� FLASH_APP_ADDR 0x08002800 //��һ��Ӧ�ó�����ʼ��ַ(�����FLASH)
//���ע���޸� STM32_FLASH_SIZE 32 //��ѡSTM32��FLASH������С(��λΪK)
/***************************************************************/
extern u8 FunCode;

int main(void)
{
    u8 waitTime = 0;
    u8 delayer = 10;
    delay_init(); //����Ҫ���ã�������ʱ��׼ȷ
    UART_Init(115200); //���ڳ�ʼ��
    LED_Init(); //LED��ʼ��
    while(1)
    {
        if (FunCode == 0) {
            if (delayer >= 10) {
                delayer = 0;
                waitTime++;
                LED = ~LED;
                if (waitTime >= 5) {
                    waitTime = 0;
                    JumpToAddr(FLASH_APP_ADDR);
                }
            }
        }
        else if (FunCode == 2){
            LED = ~LED;
        }
        else if (FunCode == 3) {
            JumpToAddr(FLASH_APP_ADDR);
        }
        delayer++;
        delay_ms(100);
    }
}

