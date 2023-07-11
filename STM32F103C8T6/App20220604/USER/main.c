#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "uart.h"
#include "OLED.h"
#include "convert.h"
#include "dht11.h"
#include "string.h"
#include "adc.h"
#include "sgp30.h"
#include "pwm.h"
#include "timer.h"
#include "stmflash.h"


/*********************��ֲʱ���ע���޸�************************/
//���ע���޸� VECT_TAB_OFFSET  0x4000 /*!< Vector Table base offset field. 
//���ע���޸� FLASH_APP_ADDR 0x08004000 //��һ��Ӧ�ó�����ʼ��ַ(�����FLASH)
//���ע���޸� STM32_FLASH_SIZE 128 //��ѡSTM32��FLASH������С(��λΪK)
/***************************************************************/

u16 Temperature;
u16 Humidty;
u16 Light;
u16 CO;
u16 CO2;
u16 Voltage;
u16 Current;
u32 ReadAddr = FLASH_BASE | 0x1ffc0;
int Sensitivity = 400;
int Index = 5;

int FlatPWMValue = 150;
int ElePWMValue = 150;

//void Track(void) {
//    int leftLight = 0;
//    int rightLight = 0;
//    int upLight = 0;
//    int downLight = 0;
////    int flatOffset = 0;
////    int eleOffset = 0;
//    u16 temp[2] = {0};
//    
//    
//    upLight = Get_Adc_Average(1, 5);
//    downLight = Get_Adc_Average(2, 5);
//    leftLight = Get_Adc_Average(3, 5);
//    rightLight = Get_Adc_Average(4, 5);
//    
//    
//    if (leftLight - rightLight > Sensitivity) {
//        FlatPWMValue += Index;
//        if (FlatPWMValue > 250) {
//            FlatPWMValue = 250;
//        }
//    }
//    if (leftLight - rightLight < -Sensitivity) {
//        FlatPWMValue -= Index;
//        if (FlatPWMValue < 50) {
//            FlatPWMValue = 50;
//        }
//    }
//    
//    
//    if (upLight - downLight > Sensitivity) {
//        ElePWMValue += Index;
//        if (ElePWMValue > 200) {
//            ElePWMValue = 200;
//        }
//    }
//    if (upLight - downLight < -Sensitivity) {
//        ElePWMValue -= Index;
//        if (ElePWMValue < 50) {
//            ElePWMValue = 50;
//        }
//    }
//    
//    TIM_SetCompare1(TIM3, ElePWMValue); //��С50���Ϊ200
//    TIM_SetCompare2(TIM3, FlatPWMValue);
//    
//    
//    temp[0] = FlatPWMValue;
//    temp[1] = ElePWMValue;
//    STMFLASH_Write(ReadAddr, temp, 2);
//    
//}

void DisplayInfo(void) {
    static u8 page = 0;
    char text[1] = {0};
    double temp = 0;
    if (page == 0) {
        page = 1;
        OLED_Fill(0x00);
        temp = 25.7;
        memset(text, 0,sizeof(text));
        strcat(text, "Tem: ");
        strcat(text, FloatToString(temp, 1));
        strcat(text, "deg");
        OLED_ShowStr(8, 1, (u8*)text, 2);
        temp = 78;
        memset(text, 0,sizeof(text));
        strcat(text, "Humidity: ");
        strcat(text, FloatToString(temp, 1));
        strcat(text, "%");
        OLED_ShowStr(8, 3, (u8*)text, 2);
    }
    else if (page == 1) {
        page = 2;
        OLED_Fill(0x00);
        temp = 524;
        memset(text, 0,sizeof(text));
        strcat(text, "Light: ");
        strcat(text, FloatToString(temp, 1));
        strcat(text, "Lux");
        OLED_ShowStr(8, 1, (u8*)text, 2);
        temp = 403;
        memset(text, 0,sizeof(text));
        strcat(text, "CO2: ");
        strcat(text, IntToString(temp));
        strcat(text, "ppm");
        OLED_ShowStr(8, 3, (u8*)text, 2);
    }
    
    else if (page == 2) {
        page = 0;
        OLED_Fill(0x00);
        temp = 56;
        memset(text, 0,sizeof(text));
        strcat(text, "CO: ");
        strcat(text, IntToString(temp));
        strcat(text, "ppm");
        OLED_ShowStr(8, 1, (u8*)text, 2);
        temp = 167;
        memset(text, 0,sizeof(text));
        strcat(text, "TVOC: ");
        strcat(text, IntToString(temp));
        strcat(text, "ppm");
        OLED_ShowStr(8, 3, (u8*)text, 2);
    }
}
int main(void)
{
    static u16 delayCounter = 10;
    //SCB->VTOR = FLASH_BASE | 0x4000; /* Vector Table Relocation in Internal FLASH. */    
    SystemInit(); //����Ҫ���ã�������ʱ��׼ȷ
    delay_init(); //����Ҫ���ã�������ʱ��׼ȷ
    UART_Init(115200); //���ڳ�ʼ��
    LED_Init(); //LED��ʼ��
    OLED_Init(); //��ʼ����Ļ
//    SGP30_Init(); //��ʼ��SGP30
//    Adc_Init(); //ADC��ʼ��
//    TIM3_PWM_Init(1999, 719); //PWM����ʼ��������Ϊ20ms
//    TIM2_Int_Init(5999, 7199);
    OLED_Fill(0xff);
    delay_ms(1000);
    delay_ms(1000);
    OLED_Fill(0x00);
    while(1)
    {
//        Track();
//            DisplayInfo();
            //PrintText("Hello word\r\n");
        if (delayCounter >= 10) {
            delayCounter = 0;
            DisplayInfo();
        }
        ExecuteCmd();
        delayCounter++;
//        LED = ~LED;
        delay_ms(100);
    }
} 



