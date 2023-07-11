#ifndef __USART_H
#define __USART_H
#include "sys.h"


#define FLASH_APP_ADDR 0x08004000 //第一个应用程序起始地址(存放在FLASH)

typedef void (*JumpFun)(void); //定义一个函数类型的参数.
void JumpToAddr(u32 addr); //跳转到APP程序执行
void ExecuteCmd(void);
void UART_Init(u32 baud);
void SendByte(u8 byte);
void PrintFloat(double value, u8 precision); 
void PrintInt(long value);
void PrintText(char*text);
void SendData(u8 funCode, u8* dat, u16 length);
u16 CRCCheckout(u8 *dat, u16 length);
#endif


