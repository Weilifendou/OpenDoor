#include "led.h"
#include "delay.h"
#include "sys.h"
#include "uart.h"
#include "pwm.h"
#include "timer.h"
#include "stmflash.h"
#include "rc522.h"
#include "key.h"
#include "dht11.h"
#include "iwdg.h"

#include "includes.h"
#include "systask.h"



int main(void)
{
//    u16 temp[1] = {0};
    NVIC_SetVectorTable(STM32_FLASH_BASE, FLASH_APP_OFFSET);
    delay_init(); //必须要调用，否则延时不准确
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    UART_Init(115200); 
    LED_Init(); //LED初始化
    Key_Init(); //按键初始化
    RC522_Init(); //NFC初始化
    DHT11_Init();
    TIM3_PWM_Init(1999, 719); //PWM波初始化，周期为20ms
//    TIM2_Int_Init(5999, 7199); //定时器2初始化定时1s
    Iwdg_Init();
//    while(1) {
//        STMFLASH_Read(TRANSFER_MODE_ADDR, temp, 1);
//        PrintText("Hello world\r\n");
//        delay_ms(1000);
//    }
    OSInit();
    OSTaskCreate(start_task,(void*)0,(OS_STK*)&START_TASK_STK[STK_SIZE-1],START_TASK_PRIO); //创建开始任务
    OSStart();
} 

