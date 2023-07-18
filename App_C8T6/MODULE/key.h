#ifndef __KEY_H
#define __KEY_H     
#include "sys.h"

#define KEY1 PCin(15)
#define KEY2 PCin(14)


void Key_Init(void);    //IO初始化
u8 ScanKey(void);          //按键扫描函数    

#endif
