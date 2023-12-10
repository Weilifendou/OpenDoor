#include "systask.h"
#include "delay.h"
#include "led.h"
#include "uart.h"
#include "key.h"
#include "rc522.h"
#include "dht11.h"
#include "pwm.h"
#include "stmflash.h"
#include "stdio.h"


//���������ջ
OS_STK START_TASK_STK[STK_SIZE];
//�����ջ
OS_STK HANDLE_TASK_STK[STK_SIZE];
//�����ջ
OS_STK DISPLAY_TASK_STK[STK_SIZE];
//�����ջ
OS_STK WATCH_TASK_STK[STK_SIZE];
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
    OSTaskCreate(watch_task,(void*)0,(OS_STK*)&WATCH_TASK_STK[STK_SIZE-1],WATCH_TASK_PRIO); //����WATCH����
    OSTaskCreate(led_task,(void*)0,(OS_STK*)&LED_TASK_STK[STK_SIZE-1],LED_TASK_PRIO); //����LED����
    OSTaskCreate(iwdg_task,(void*)0,(OS_STK*)&IWDG_TASK_STK[STK_SIZE-1],IWDG_TASK_PRIO); //����HANDLE����
    OSTaskSuspend(START_TASK_PRIO); //����ʼ����
    OS_EXIT_CRITICAL();  //�˳��ٽ���(���ж�)
}


#define STORED_NUMBER (3*2) //ֻ�ܴ洢���ſ�Ƭ
State CurrentState = NORMAL;
u16 StoredUser[STORED_NUMBER] = {0};
u16 CurrentUser[2] = {0};

void OpenDoor(void) {
    TIM_SetCompare4(TIM3, 230);
    LED = 0;
    delay_ms(1000);
    delay_ms(1000);
    delay_ms(1000);
    K2 = 0;
    K3 = 0;
    delay_ms(50);
    K2 = 1;
    K3 = 1;
}

void handle_task(void *pdata)
{
    u8 i = 0;
    u8 delayer = 30;
	u8 cStatus = MI_ERR;
    while(1)
    {
        ScanKey();
        if (CurrentState == VALIDATION_REMOTE) {
            OpenDoor();
            CurrentState = NORMAL;
        } else if (CurrentState == CARD_DISABLE);
        else if (CurrentState == NORMAL){
            cStatus = GetICID();
            if (cStatus == MI_OK) {
                CurrentState = VALIDATION_FAIL;
                CurrentUser[0] = ICID[0];
                CurrentUser[0] <<= 8;
                CurrentUser[0] |= ICID[1];
                CurrentUser[1] = ICID[2];
                CurrentUser[1] <<= 8;
                CurrentUser[1] |= ICID[3];
                STMFLASH_Read(STM32_FLASH_BASE | DATA_START_ADDR, StoredUser, STORED_NUMBER);
                if (WriteFlag) {
                    WriteFlag = 0;
                    for (i = 0; i < STORED_NUMBER; i+=2) {
                        if (StoredUser[i] == 0xffff && StoredUser[i+1] == 0xffff) break;
                    }
                    if (i < STORED_NUMBER) {
                        STMFLASH_Write(STM32_FLASH_BASE | DATA_START_ADDR + i*2, CurrentUser, 2);
                    } else {
                        for (i = 0; i < STORED_NUMBER-2; i+=2) {
                            StoredUser[i] = StoredUser[i+2];
                            StoredUser[i+1] = StoredUser[i+3];
                        }
                        StoredUser[i] = CurrentUser[0];
                        StoredUser[i+1] = CurrentUser[1];
                        STMFLASH_Write(STM32_FLASH_BASE | DATA_START_ADDR, StoredUser, STORED_NUMBER);
                    }
                    CurrentState = WRITE_SUCCESS;
                    LED = 0;
                    delay_ms(1000);
                    delay_ms(1000);
                } else {
                    for (i = 0; i < STORED_NUMBER; i+=2) {
                        if (StoredUser[i] == CurrentUser[0] && StoredUser[i+1] == CurrentUser[1]){
                            CurrentState = VALIDATION;
                            K2 = 0;
                            K3 = 0;
                            delay_ms(50);
                            K2 = 1;
                            K3 = 1;
                            OpenDoor();
                            break;
                        }
                    }
                }
            } else {
                CurrentState = NORMAL;
                LED = 1;
                TIM_SetCompare4(TIM3, 80);
            }
        }
        if (delayer >= 30) {
            delayer = 0;
//            DHT11_ReadData(&Temperature, &Humidity);
//            SendData();
        }
        delay_ms(100);
        delayer++;
    }
}


void display_task(void *pdata)
{
    while(1)
    {
        if (CurrentState == NORMAL) {
            LED = 1;
        }
        
        if (CurrentState == NORMAL) {
            printf("�ȴ���֤\r\n");
        }
        else if (CurrentState == WRITE_SUCCESS) {
            printf("%X%X\r\n¼��ɹ�\r\n", CurrentUser[0], CurrentUser[1]);
        }
        else if (CurrentState == VALIDATION) {
            printf("%X%X\r\n��֤�ɹ�\r\n", CurrentUser[0], CurrentUser[1]);
            
        }
        else if (CurrentState == VALIDATION_REMOTE) {
            printf("Զ����֤\r\n");
        
        }
        else if (CurrentState == VALIDATION_FAIL) {
            printf("%X%X\r\n��֤ʧ��\r\n", CurrentUser[0], CurrentUser[1]);
        } else if (CurrentState == CARD_DISABLE) {
            printf("IC���ѽ��ã�����ϵ����Ա\r\n");
        }
        delay_ms(1000);
    }
}



void watch_task(void *pdata)
{
    double tem = 0.0f;
    double hum = 0.0f;
    while(1) {
        DHT11_ReadData();
        tem = Temperature / 10.0;
        hum = Humidity / 10.0;
        PrintText("  ");
        PrintFloat(tem, 2);
        PrintText("  ");
        PrintFloat(hum, 2);
        PrintText("\r\n");
        SendData();
        delay_ms(1000);
        delay_ms(1000);
        delay_ms(1000);
    }
    
}
void led_task(void *pdata)
{
    while(1) {
//        LED = 0;
//        delay_ms(50);
//        LED = 1;
        delay_ms(1000);
    }
    
}
void iwdg_task(void *pdata)
{
    while(1)
    {
        IWDG_ReloadCounter();
        delay_ms(1000);
        delay_ms(1000);
        delay_ms(1000);
    }
}
