#ifndef __KEY_H
#define __KEY_H     
#include "sys.h"

#define KEY1 PCin(15)
#define KEY2 PCin(14)


void Key_Init(void);    //IO��ʼ��
u8 ScanKey(void);          //����ɨ�躯��    

#endif
