#ifndef __OLED_H
#define __OLED_H

#include "sys.h"


//IO�������� 
#define OLED_IIC_SCL    PBout(6) //SCL
#define OLED_IIC_SDA    PBout(7) //SDA
#define READ_SDA   PBin(7)  //����SDA 


extern char StrBuff[4][17];

//IIC���в�������
void OLED_SDA_OUT(void);
void OLED_SDA_IN(void);
void OLED_IIC_Init(void);                //��ʼ��IIC��IO�� 
void OLED_IIC_Start(void);//����IIC��ʼ�ź�
void OLED_IIC_Stop(void);  //����IICֹͣ�ź�
void OLED_IIC_Send_Byte(u8 txd);//IIC����һ���ֽ�
u8 OLED_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 OLED_IIC_Wait_Ack(void); //IIC�ȴ�ACK�ź�
void OLED_IIC_Ack(void);//IIC����ACK�ź�
void OLED_IIC_NAck(void);//IIC������ACK�ź�


void OLED_Init(void);
void OLED_Write(u8 addr, u8 data);

#define OLED_ADDRESS 0x78 //ͨ������0R����,������0x78��0x7A������ַ -- Ĭ��0x78

void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_Fill(unsigned char fill_Data);
void OLED_ClearContent(unsigned char fill_Data);
void OLED_ClearLine(unsigned char line);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_ShowStr(unsigned char x, unsigned char y, char* ch, unsigned char TextSize);
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
void OLED_ShowCNS(u8 x, u8 y, u8 cns[], u8 num);
void OLED_CenterShowStr(u8 y, char* ch);
void OLED_InsertStr(u8 start, u8 line, char* ch, u8 mode);
void OLED_CenterValidate(void);
void OLED_Validate(void);
void ClearStrBuff(void);
#endif


