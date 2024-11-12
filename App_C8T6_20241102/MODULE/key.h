#ifndef __KEY_H
#define __KEY_H     
#include "sys.h"

#define KEY1 PCin(15)
#define KEY2 PCin(14)

#define A4 PAin(15)
#define A3 PBin(3)
#define A2 PBin(4)
#define A1 PBin(5)

#define K4 PBout(6)
#define K3 PBout(7)
#define K2 PBout(8)
#define K1 PBout(9)


void Key_Init(void);    //IO初始化
u8 ScanKey(void);          //按键扫描函数    

#endif
