#ifndef __DHT11_H_
#define __DHT11_H_

#include "sys.h"

#define DHT PAin(0)
#define DHT_UP GPIO_SetBits(GPIOA, GPIO_Pin_0)
#define DHT_DOWN GPIO_ResetBits(GPIOA, GPIO_Pin_0)

extern u16 Temperature;
extern u16 Humidity;

void DatLineOut(void);
void DatLineIn(void);


void DHT11_Init(void);
void DHT11_Start(void);

void DHT11_ReadData(void);


#endif



