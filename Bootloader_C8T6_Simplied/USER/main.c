#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "uart.h"
#include "string.h"
#include "oled.h"
#include "stmflash.h"

/*********************移植时务必注意修改************************/
//务必注意修改 FLASH_APP_ADDR 0x08002800 //第一个应用程序起始地址(存放在FLASH)
//务必注意修改 STM32_FLASH_SIZE 128 //所选STM32的FLASH容量大小(单位为K)
/***************************************************************/
extern u8 FunCode;

int main(void)
{
    u8 waitTime = 0;
    u8 delayer = 10;
    delay_init(); //必须要调用，否则延时不准确
    LED_Init(); //LED初始化
    UART_Init(115200); //串口初始化
    while(1)
    {
        if (FunCode == 0) {
            if (delayer >= 10) {
                delayer = 0;
                waitTime++;
                LED = ~LED;
                if (waitTime > 5) {
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

