

/*
IC�����ţ�A4->SDA A5->SCK A7->MOSI A6->MISO B0->RST
OLED���ţ�PB6->SCL; PB7->SDA
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
    delay_init(); //����Ҫ���ã�������ʱ��׼ȷ
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    UART_Init(115200); 
    LED_Init(); //LED��ʼ��
    Key_Init(); //������ʼ��
    DHT11_Init(); //��ʪ�ȴ�������ʼ��
    RC522_Init(); //NFC��ʼ��
    OLED_Init(); //��Ļ��ʼ��
    OLED_Fill(0x00);
    ClearStr(text);
    AddStr(text, "OPEN DOOR");
    OLED_ShowStr(30, 3, text, 2);
    delay_ms(1000);
    delay_ms(1000);
    delay_ms(1000);
    OLED_Fill(0x00);
    TIM3_PWM_Init(1999, 719); //PWM����ʼ��������Ϊ20ms
    TIM2_Int_Init(5999, 7199); //��ʱ��2��ʼ����ʱ1s
    Iwdg_Init();
    
    OSInit();
    OSTaskCreate(start_task,(void*)0,(OS_STK*)&START_TASK_STK[STK_SIZE-1],START_TASK_PRIO); //������ʼ����
    OSStart();
} 

