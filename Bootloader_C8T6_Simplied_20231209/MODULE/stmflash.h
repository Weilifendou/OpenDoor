#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include "sys.h"  

//////////////////////////////////////////////////////////////////////////////////////////////////////
//�û������Լ�����Ҫ����
#define STM32_FLASH_SIZE 128              //��ѡSTM32��FLASH������С(��λΪK)
#define STM32_FLASH_WREN 1              //ʹ��FLASHд��(0����ʹ��;1��ʹ��)
//////////////////////////////////////////////////////////////////////////////////////////////////////

//FLASH��ʼ��ַ
#define STM32_FLASH_BASE 0x08000000     //STM32 FLASH����ʼ��ַ
//FLASH������ֵ

#define FLASH_APP_OFFSET 0x4000
//                   0x08000000

#define FLASH_APP_ADDR 0x08004000 //��һ��Ӧ�ó�����ʼ��ַ(�����FLASH)
//                     0x08000000
#define TRANSFER_MODE_ADDR  0x08003FF0

u16 STMFLASH_ReadHalfWord(u32 faddr);          //��������  
void STMFLASH_WriteLenByte(u32 WriteAddr,u32 DataToWrite,u16 Len);    //ָ����ַ��ʼд��ָ�����ȵ�����
u32 STMFLASH_ReadLenByte(u32 ReadAddr,u16 Len);                        //ָ����ַ��ʼ��ȡָ����������
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);        //��ָ����ַ��ʼд��ָ�����ȵ�����
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);           //��ָ����ַ��ʼ����ָ�����ȵ�����

//����д��
void Test_Write(u32 WriteAddr,u16 WriteData);                                   
#endif
















