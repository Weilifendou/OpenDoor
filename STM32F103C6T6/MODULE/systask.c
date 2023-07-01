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
typedef enum {
    WRITE_SUCCESS,
    WRITE_FAIL,
    USER_EXISTED,
    READ_SUCCESS,
    READ_FAIL,
    NORMAL,
    VALIDATION,
    VALIDATION_FAIL,
    OLED_DEBUG,
} State;

State CurrentState = NORMAL;
u16 StoredUser[16] = {0};
u16 CurrentUser[2] = {0};

void handle_task(void *pdata)
{
    u8 i = 0;
    u8 delayer = 10;
	u8 cStatus = MI_ERR;
    while(1)
    {
        ScanKey();
        cStatus = GetICID();
        if (cStatus == MI_OK) {
            CurrentUser[0] = ICID[0];
            CurrentUser[0] <<= 8;
            CurrentUser[0] |= ICID[1];
            CurrentUser[1] = ICID[2];
            CurrentUser[1] <<= 8;
            CurrentUser[1] |= ICID[3];
            STMFLASH_Read(STM32_FLASH_BASE | DATA_START_ADDR, StoredUser, 16);
            for (i = 0; i < 16; i+=2) {
                if (StoredUser[i] == CurrentUser[0] && StoredUser[i+1] == CurrentUser[1]){
                    CurrentState = VALIDATION;
                    LED_GREEN = 0;
//                    BUZZER = !BUZZER;
                    TIM_SetCompare4(TIM3, 250);
                    break;
                }
                else if (StoredUser[i] == 0xffff && StoredUser[i+1] == 0xffff) break;
            }
            if (WriteFlag) {
                WriteFlag = 0;
                if (CurrentState != VALIDATION) {
                    CurrentState = WRITE_SUCCESS;
                    STMFLASH_Write(STM32_FLASH_BASE | DATA_START_ADDR + i*2, CurrentUser, 2);
                } else {
                    CurrentState = USER_EXISTED;
                }
            } else if (CurrentState != VALIDATION) {
                LED_RED = 0;
//                BUZZER = 1;
                CurrentState = VALIDATION_FAIL;
            }
        } else {
            CurrentState = NORMAL;
            LED_RED = 1;
            LED_GREEN = 1;
            BUZZER = 0;
            TIM_SetCompare4(TIM3, 50);
        }
        if (delayer >= 10) {
            delayer = 0;
            DHT11_ReadData(&Temperature, &Humidty);
            SendData();
        }
        delay_ms(100);
        delayer++;
    }
}


void display_task(void *pdata)
{
    char text[20] = {0};
    while(1)
    {
        ClearStrBuff();
        if (CurrentState == NORMAL) {
            LED_GREEN = LED_RED = 1;
            //显示当前温度
            ClearStr(text);
            AddStr(text, "T: ");
            AddStr(text, FloatToString(Temperature / 10.0, 1));
            AddStr(text, "deg     ");
            OLED_InsertStr(2, 0, text, 0);
            
            //显示当前湿度
            ClearStr(text);
            AddStr(text, "H: ");
            AddStr(text, FloatToString(Humidty / 10.0, 1));
            AddStr(text, "%     ");
            OLED_InsertStr(2, 1, text, 0);
            
            //显示当前角度
            ClearStr(text);
            AddStr(text, IntToString(white));
            AddStr(text, " ");
            AddStr(text, IntToString(yellow));
            AddStr(text, " ");
            AddStr(text, IntToString(steer));
            AddStr(text, "      ");
            OLED_InsertStr(2, 2, text, 0);
            
            OLED_CenterValidate();
        
        }
        else if (CurrentState == WRITE_SUCCESS) {
            ClearStr(text);
            AddStr(text, IntToHex(CurrentUser[0]));
            AddStr(text, IntToHex(CurrentUser[1]));
            OLED_InsertStr(0, 1, text, 1);
            ClearStr(text);
            AddStr(text, " WRITE SUCCESS ");
            OLED_InsertStr(0, 2, text, 1);
            OLED_Validate();
        }
        else if (CurrentState == USER_EXISTED) {
            ClearStr(text);
            AddStr(text, IntToHex(CurrentUser[0]));
            AddStr(text, IntToHex(CurrentUser[1]));
            OLED_InsertStr(0, 1, text, 1);
            ClearStr(text);
            AddStr(text, " USER EXISTED ");
            OLED_InsertStr(0, 2, text, 1);
            OLED_Validate();
        }
        else if (CurrentState == VALIDATION) {
            ClearStr(text);
            AddStr(text, IntToHex(CurrentUser[0]));
            AddStr(text, IntToHex(CurrentUser[1]));
            OLED_InsertStr(0, 1, text, 1);
            ClearStr(text);
            AddStr(text, "VALIDATION");
            OLED_InsertStr(0, 2, text, 1);
            OLED_Validate();
            
        }
        else if (CurrentState == VALIDATION_FAIL) {
            ClearStr(text);
            AddStr(text, IntToHex(CurrentUser[0]));
            AddStr(text, IntToHex(CurrentUser[1]));
            OLED_InsertStr(0, 1, text, 1);
            ClearStr(text);
            AddStr(text, "VALIDATION FAIL");
            OLED_InsertStr(0, 2, text, 1);
            OLED_Validate();
        }
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
