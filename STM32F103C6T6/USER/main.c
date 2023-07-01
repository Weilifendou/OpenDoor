

/*
IC卡引脚：A4->SDA A5->SCK A7->MOSI A6->MISO B0->RST
OLED引脚：PB6->SCL; PB7->SDA
*/

#include "led.h"
#include "delay.h"
#include "sys.h"
#include "uart.h"
#include "str.h"
#include "OLED.h"
#include "cncode.h"
#include "dht11.h"
#include "pwm.h"
#include "timer.h"
#include "stmflash.h"
#include "rc522.h"
#include "key.h"
#include "iwdg.h"

#include "includes.h"
#include "systask.h"



int main(void)
{
    char text[20];
    delay_init(); //必须要调用，否则延时不准确
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    UART_Init(115200); 
    LED_Init(); //LED初始化
    Key_Init(); //按键初始化
    DHT11_Init(); //温湿度传感器初始化
    RC522_Init(); //NFC初始化
    OLED_Init(); //屏幕初始化
    OLED_Fill(0x00);
    ClearStr(text);
    AddStr(text, "OPEN DOOR");
    OLED_ShowStr(30, 3, text, 2);
    delay_ms(1000);
    delay_ms(1000);
    delay_ms(1000);
    OLED_Fill(0x00);
    TIM3_PWM_Init(1999, 719); //PWM波初始化，周期为20ms
    TIM2_Int_Init(5999, 7199); //定时器2初始化定时1s
    Iwdg_Init();
    
    OSInit();
    OSTaskCreate(start_task,(void*)0,(OS_STK*)&START_TASK_STK[STK_SIZE-1],START_TASK_PRIO); //创建开始任务
    OSStart();
} 

