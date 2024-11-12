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
    delay_init(); //����Ҫ���ã�������ʱ��׼ȷ
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    UART_Init(115200); 
    LED_Init(); //LED��ʼ��
    Key_Init(); //������ʼ��
    RC522_Init(); //NFC��ʼ��
    DHT11_Init();
    TIM3_PWM_Init(1999, 719); //PWM����ʼ��������Ϊ20ms
//    TIM2_Int_Init(5999, 7199); //��ʱ��2��ʼ����ʱ1s
    Iwdg_Init();
//    while(1) {
//        STMFLASH_Read(TRANSFER_MODE_ADDR, temp, 1);
//        PrintText("Hello world\r\n");
//        delay_ms(1000);
//    }
    OSInit();
    OSTaskCreate(start_task,(void*)0,(OS_STK*)&START_TASK_STK[STK_SIZE-1],START_TASK_PRIO); //������ʼ����
    OSStart();
} 

