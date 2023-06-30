#ifndef __PORT_H
#define __PORT_H 			   
#include "sys.h" 


#define KEY1 PAin(12)
#define KEY2 PAin(15)

//#define BUZZER PBout(8)

void Port_Init(void);
void BuzzerRing(u8 ringTime);
void ScanKey(void);
#endif



