#ifndef __KEY_H
#define __KEY_H     
#include "sys.h"

#define KEY1 PBin(8)
#define KEY2 PBin(9)


void Key_Init(void);    //IO��ʼ��
u8 ScanKey(u8);          //����ɨ�躯��    

#endif
