

/*
IC卡引脚：A4->SDA A5->SCK A6->MOSI A7->MISO B0->RST
OLED引脚：PB6->SCL; PB7->SDA
BUZZER：PA1
LED：PB4 PB5
KEY：PB12 PB13 PB14 PB15
*/

//u8 IDRegister[50][4] = {
//	{0x62,0xBA,0xF0,0x1C},
//	{0x19,0xD4,0xBF,0x63},
//	{0xDE,0xFB,0x5C,0xDD},
//	{0x0D,0x0D,0xB3,0xAA},
//};

//extern u8 ICID[4];
//extern int Balance;
//extern int Amount;
//extern u8 ConsumeFlag, RechargeFlag;
//extern u8 CardOrder;


//void ShowInfo(void){
//	u8 i = 0;
//	u8 lineStart = 0;
//	char cStatus = MI_ERR;
//	for (i = 0; i < 50; i++) {
//		if (ICID[0]==IDRegister[i][0] && ICID[1]==IDRegister[i][1]
//		&& ICID[2]==IDRegister[i][2] && ICID[3]==IDRegister[i][3]) {
//			OLED_ClearLine(2);
//			OLED_ClearLine(3);
//			CardOrder = i + 1;
//			switch (i) {
//				case 0: OLED_ShowCNS(48, 2, SK, 2); break;
//				case 1: OLED_ShowCNS(48, 2, ZS, 2); break;
//			}
//			cStatus = ReadBalance();
//			if (cStatus == MI_OK) {
//				lineStart = 12;
//				OLED_ClearLine(4);
//				OLED_ClearLine(5);
//				OLED_ShowCNS(lineStart, 5, DQYE, 4);
//				lineStart += 8 * 8 + 4;
//				OLED_ShowStr(lineStart, 5, IntToString(Balance), 2);
//				if (!ConsumeFlag){
//					BuzzerRing(3);
//				}
//			}
//			else {
//				lineStart = 32;
//				OLED_Fill(0x00);
//				OLED_ShowCNS(lineStart, 4, DKCW, 4);
//			}
//			break;
//		}
//	}
//	if (i >= 50) {
//		lineStart = 16;
//		CardOrder = 50;
//		OLED_Fill(0x00);
//		OLED_ShowCNS(lineStart, 4, WZCGKP, 6);
//	}
//}

//lineStart = 4;
//OLED_ClearLine(4);
//OLED_ClearLine(5);
//OLED_ShowStr(lineStart, 5, IntToText(ICID[0]),2);
//lineStart += 8 * 4;
//OLED_ShowStr(lineStart, 5, IntToText(ICID[1]),2);
//lineStart += 8 * 4;
//OLED_ShowStr(lineStart, 5, IntToText(ICID[2]),2);
//lineStart += 8 * 4;
//OLED_ShowStr(lineStart, 5, IntToText(ICID[3]),2);

//int main(void)
//{
//	u8 lineStart = 0;
//	u8 onceFlag = 0;
//	u8 delayer = 100;
//	char cStatus = MI_ERR;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
//	UART_Init(115200);
//    delay_init();
//	Port_Init();
////	RC522_Init();
//	OLED_Init();
//	OLED_Fill(0x00);
//	OLED_ShowCNS(7, 0, Title, 7);
//	OLED_ShowCNS(30, 4, QFKP, 4);
////	OLED_ShowCNS(16, 0, Connection, 6);
//	while(1)
//	{
//		ScanKey();
//		if (delayer >= 100) {
//			delayer = 0;
//			cStatus = GetICID();
//			if (cStatus == MI_OK) {
//				if (!onceFlag) {
//					onceFlag = 1;
//					ShowInfo();
//				}
//			} else {
//				onceFlag = 0;
//				lineStart = 32;
//				CardOrder = 0;
//				Balance = 0;
//				OLED_Fill(0x00);
//				OLED_ShowCNS(lineStart, 4, QFKP, 4);
//			}
//			if (RechargeFlag) {
//				RechargeFlag = 0;
//				cStatus = Recharge(Amount);
//				if (cStatus == MI_OK) {
//					lineStart = 32;
//					OLED_Fill(0x00);
//					OLED_ShowCNS(lineStart, 4, CZCG, 4);
//					delay_ms(500);
//					ShowInfo();
//				} else {
//					lineStart = 32;
//					OLED_ClearLine(4);
//					OLED_ClearLine(5);
//					OLED_ShowCNS(lineStart, 4, DKCW, 4);
//				}
//			}
//			if (ConsumeFlag) {
//				cStatus = Consume(Amount);
//				if (cStatus == MI_OK) {
//					lineStart = 32;
//                    OLED_Fill(0x00);
//					ShowInfo();
//					if (Balance <= 0) {
//						ConsumeFlag = 0;
//						while (!RechargeFlag) {
//							BuzzerRing(1);
//						}
//					}
//				} else {
//					ConsumeFlag = 0;
//					Amount = 0;
//					lineStart = 32;
//					OLED_ClearLine(4);
//					OLED_ClearLine(5);
//					OLED_ShowCNS(lineStart, 4, DKCW, 4);
//				}
//			}
//		}
//		delay_ms(10);
//		delayer++;
//	}
//}
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


u16 Temperature, Humidty;
u8 white, yellow, steer;

int main(void)
{
    char text[20];
    delay_init(); //必须要调用，否则延时不准确
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    UART_Init(115200); 
    LED_Init(); //LED初始化
    Key_Init(); //按键初始化
    DHT11_Init(); //温湿度传感器初始化
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

