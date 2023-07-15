#ifndef __OLED_H
#define __OLED_H

#include "sys.h"


//IO�������� 
#define OLED_IIC_SCL    PBout(6) //SCL
#define OLED_IIC_SDA    PBout(7) //SDA
#define READ_SDA   PBin(7)  //����SDA

//IIC���в�������
void OLED_SDA_OUT(void);
void OLED_SDA_IN(void);
void OLED_IIC_Init(void);                //��ʼ��IIC��IO�� 
void OLED_IIC_Start(void);//����IIC��ʼ�ź�
void OLED_IIC_Stop(void);  //����IICֹͣ�ź�
void OLED_IIC_Send_Byte(u8 txd);//IIC����һ���ֽ�
u8 OLED_IIC_Read_Byte(u8 ack);//IIC��ȡһ���ֽ�
u8 OLED_IIC_Wait_Ack(void); //IIC�ȴ�ACK�ź�
void OLED_IIC_Ack(void);//IIC����ACK�ź�
void OLED_IIC_NAck(void);//IIC������ACK�ź�


void OLED_Init(void);
void OLED_Write(u8 addr, u8 data);

#define OLED_ADDRESS 0x78 //ͨ������0R����,������0x78��0x7A������ַ -- Ĭ��0x78

void OLED_SetPos(u8 x, u8 y);
void OLED_Fill(u8 fill_Data);
void OLED_ClearContent(u8 fill_Data);
void OLED_ClearLine(u8 line);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_ShowStr(u8 x, u8 y, char* ch, u8 TextSize);
void OLED_ShowCN(u8 x, u8 y, u8 N);
void OLED_DrawBMP(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[]);
void OLED_ShowCNS(u8 x, u8 y, u8 cns[], u8 num);
void OLED_CenterShowStr(u8 y, char* ch);
void OLED_InsertStr(u8 start, u8 line, char* ch, u8 mode);
void OLED_ThreeLineCenterValidate(void);
void OLED_TwoLineCenterValidate(void);
void OLED_Validate(void);
void OLED_ClearStrBuff(void);
#endif


