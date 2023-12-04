#ifndef __USART_H
#define __USART_H
#include "sys.h"

#define BUFF_SIZE 1050
#define FRAME_SIZE 512

#define RX_LENGTH 128
#define TX_LENGTH 128
extern u8 FunCode;

typedef void (*JumpFun)(void); //����һ���������͵Ĳ���.

void ExecuteCmd(void);
void JumpToAddr(u32 addr); //��ת��APP����ִ��
void UART_Init(u32 baud);
void SendByte(u8 byte);
void SendData(void);
u16 CRCCheckout(u8 *dat, u16 length);
#endif


