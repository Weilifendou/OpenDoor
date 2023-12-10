#ifndef __USART_H
#define __USART_H
#include "sys.h"


#define SPP_FRAME_SIZE 512
#define BLE_FRAME_SIZE 64


typedef void (*JumpFun)(void); //����һ���������͵Ĳ���.
void JumpToAddr(u32 addr); //��ת��APP����ִ��


void UART_Init(u32 baud);
void SendByte(u8 byte);
void SendData(u8 funCode, u8* dat, u16 length);
u16 CRCCheckout(u8 *dat, u16 length);
void PrintFloat(double value, u8 precision);
void PrintInt(long value);
void PrintText(char* text);


#endif


