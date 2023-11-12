#ifndef __USART_H
#define __USART_H
#include "sys.h"

#define RX_LENGTH 128
#define TX_LENGTH 128

typedef void (*JumpFun)(void); //定义一个函数类型的参数.

void ExecuteCmd(void);
void JumpToAddr(u32 addr); //跳转到APP程序执行
void UART_Init(u32 baud);
void SendByte(u8 byte);
void SendData(void);
u16 CRCCheckout(u8 *dat, u16 length);
#endif


