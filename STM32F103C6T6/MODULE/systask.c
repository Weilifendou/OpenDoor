#include "systask.h"
#include "delay.h"
#include "led.h"
#include "uart.h"
#include "str.h"
#include "oled.h"
#include "dht11.h"
#include "key.h"
#include "rc522.h"
#include "pwm.h"
#include "stmflash.h"


//任务任务堆栈
OS_STK START_TASK_STK[STK_SIZE];
//任务堆栈
OS_STK HANDLE_TASK_STK[STK_SIZE];
//任务堆栈
OS_STK DISPLAY_TASK_STK[STK_SIZE];
//任务堆栈
OS_STK LED_TASK_STK[STK_SIZE];
//任务堆栈
OS_STK IWDG_TASK_STK[STK_SIZE];

//开始任务
void start_task(void *pdata)
{
    OS_CPU_SR cpu_sr=0;
    pdata=pdata;
    OSStatInit();  //开启统计任务
    
    OS_ENTER_CRITICAL();  //进入临界区(关闭中断)
    OSTaskCreate(handle_task,(void*)0,(OS_STK*)&HANDLE_TASK_STK[STK_SIZE-1],HANDLE_TASK_PRIO); //创建HANDLE任务
    OSTaskCreate(display_task,(void*)0,(OS_STK*)&DISPLAY_TASK_STK[STK_SIZE-1],DISPLAY_TASK_PRIO); //创建HANDLE任务
    OSTaskCreate(led_task,(void*)0,(OS_STK*)&LED_TASK_STK[STK_SIZE-1],LED_TASK_PRIO); //创建LED任务
    OSTaskCreate(iwdg_task,(void*)0,(OS_STK*)&IWDG_TASK_STK[STK_SIZE-1],IWDG_TASK_PRIO); //创建HANDLE任务
    OSTaskSuspend(START_TASK_PRIO); //挂起开始任务
    OS_EXIT_CRITICAL();  //退出临界区(开中断)
}

void led_task(void *pdata)
{
    while(1) {
        LED = 0;
        delay_ms(50);
        LED = 1;
        delay_ms(1000);
    }
    
}

extern u16 Temperature, Humidty;


void handle_task(void *pdata)
{
    u8 delayer = 10;
	u8 cStatus = MI_ERR;
    char text[20];
    while(1)
    {
        if (delayer >= 10) {
            delayer = 0;
            DHT11_ReadData(&Temperature, &Humidty);
            SendData();
        }
        ScanKey(0);
        if (ReadFlag) {
            ReadFlag = 0;
            cStatus = GetICID();
            if (cStatus == MI_OK) {
                cStatus = ReadBlock(white);
                if (cStatus == MI_OK) {
                    ClearStr(text);
                    AddStr(text, "READ SUCCESS ");
                    OLED_ShowStr(30, 3, text, 2);
                    
                } else {
                    ClearStr(text);
                    AddStr(text, "READ FAIL    ");
                    OLED_ShowStr(30, 3, text, 2);
                }
            
            }
        }
        if (WriteFlag) {
            WriteFlag = 0;
            cStatus = GetICID();
            if (cStatus == MI_OK) {
                WriteBuff[0] = 0x01;
                cStatus = WriteBlock(white);
                if (cStatus == MI_OK) {
                    ClearStr(text);
                    AddStr(text, "WRITE SUCCESS ");
                    OLED_ShowStr(30, 3, text, 2);
                    
                } else {
                    ClearStr(text);
                    AddStr(text, "WRITE FAIL    ");
                    OLED_ShowStr(30, 3, text, 2);
                }
            
            }
        }
        delay_ms(100);
        delayer++;
    }
}


void display_task(void *pdata)
{
    while(1)
    {
//        DisplayInfo();
        delay_ms(200);
    }
}


void iwdg_task(void *pdata)
{
    while(1)
    {
        IWDG_ReloadCounter();
        delay_ms(1000);
    }
}
