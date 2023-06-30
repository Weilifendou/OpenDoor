#include "systask.h"
#include "delay.h"
#include "led.h"
#include "uart.h"
#include "oled.h"
#include "dht11.h"
#include "key.h"
#include "rc522.h"
#include "stmflash.h"


//���������ջ
OS_STK START_TASK_STK[STK_SIZE];
//�����ջ
OS_STK HANDLE_TASK_STK[STK_SIZE];
//�����ջ
OS_STK DISPLAY_TASK_STK[STK_SIZE];
//�����ջ
OS_STK LED_TASK_STK[STK_SIZE];
//�����ջ
OS_STK IWDG_TASK_STK[STK_SIZE];

//��ʼ����
void start_task(void *pdata)
{
    OS_CPU_SR cpu_sr=0;
    pdata=pdata;
    OSStatInit();  //����ͳ������
    
    OS_ENTER_CRITICAL();  //�����ٽ���(�ر��ж�)
    OSTaskCreate(handle_task,(void*)0,(OS_STK*)&HANDLE_TASK_STK[STK_SIZE-1],HANDLE_TASK_PRIO); //����HANDLE����
    OSTaskCreate(display_task,(void*)0,(OS_STK*)&DISPLAY_TASK_STK[STK_SIZE-1],DISPLAY_TASK_PRIO); //����HANDLE����
    OSTaskCreate(led_task,(void*)0,(OS_STK*)&LED_TASK_STK[STK_SIZE-1],LED_TASK_PRIO); //����LED����
    OSTaskCreate(iwdg_task,(void*)0,(OS_STK*)&IWDG_TASK_STK[STK_SIZE-1],IWDG_TASK_PRIO); //����HANDLE����
    OSTaskSuspend(START_TASK_PRIO); //����ʼ����
    OS_EXIT_CRITICAL();  //�˳��ٽ���(���ж�)
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

extern u8 ICID[20];

void handle_task(void *pdata)
{
    u8 delayer = 10;
	u8 onceFlag = 0;
	u8 cStatus = MI_ERR;
    while(1)
    {
        if (delayer >= 0) {
            delayer = 0;
            DHT11_ReadData(&Temperature, &Humidty);
            SendData();
        }
        ScanKey(0);
        cStatus = GetICID();
        ICID[0] = cStatus;
        delay_ms(1000);
        delayer++;
    }
}


void display_task(void *pdata)
{
    while(1)
    {
        DisplayInfo();
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
