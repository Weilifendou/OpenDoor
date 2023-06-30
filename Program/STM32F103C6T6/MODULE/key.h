#ifndef __KEY_H
#define __KEY_H     
#include "sys.h"

#define KEY1 PBin(8)
#define KEY2 PBin(9)


void Key_Init(void);    //IO初始化
u8 ScanKey(u8);          //按键扫描函数    

#endif
