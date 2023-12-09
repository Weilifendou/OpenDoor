#include "uart.h"
#include "md5.h"
#include "stmflash.h"
#include "delay.h"
#include "stdio.h"
#include "str.h"


//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB
//������������й����п��ܻ���������������ã�����
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
    int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
    x = x; 
}

//__use_no_semihosting was requested, but _ttywrch was 
void _ttywrch(int ch)
{
    ch = ch;
}
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
    while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
    return ch;
}
#endif


u16 DownloadMode;

void UART_Init(u32 bound){
    u16 temp[1] = {0};
  //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
     
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);    //ʹ��USART1��GPIOAʱ��

    //USART1_TX   GPIOA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9

    //USART1_RX      GPIOA.10��ʼ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

    //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3 ;//��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);    //����ָ���Ĳ�����ʼ��VIC�Ĵ���

    //USART ��ʼ������

    USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    //�շ�ģʽ

    USART_Init(USART1, &USART_InitStructure); //��ʼ������1
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
    STMFLASH_Read(TRANSFORM_RATE_ADDR, temp, 1);
    DownloadMode = temp[0];
}


u16 CRCCheckout(u8 *dat, u16 length) {
    u8 temp = 0;
    u16 i = 0;
    u16 j = 0;
    u16 crc = 0xffff;
    for (i = 0; i < length; i++) {
        temp = *(dat + i) & 0x00ff;
        crc ^= temp;
        for (j = 0; j < 8; j++) {
            if (crc & 0x0001) {
                crc >>= 1;
                crc ^= 0xa001;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}


void SendData(u8 funCode, u8* dat, u16 length) {
    u16 i = 0;
    u16 crc = 0;
    u8 headerLength = 5;
    u8 checkLength = 2;
    const u8 buffLength = 8;
    u8 sendBuff[buffLength] = {0};
    sendBuff[0] = 0x55;
    sendBuff[1] = 0xaa;
    sendBuff[2] = funCode; //������
    sendBuff[3] = length >> 8; //���ݳ���
    sendBuff[4] = length; //���ݳ���
     for (i = 0; i < length; i++)
    {
        sendBuff[i + headerLength] = *(dat + i);
    }
    crc = CRCCheckout(sendBuff, buffLength - checkLength);
    sendBuff[buffLength - 2] = crc >> 8;
    sendBuff[buffLength - 1] = crc;
    for (i = 0; i < buffLength; i++) {
        SendByte(sendBuff[i]);
    }
}

//__attribute__((at(0x20001000)));


u8 SPP_RecBuff[SPP_FRAME_SIZE*2+30];
u16 SPP_Frame[SPP_FRAME_SIZE];

u8 BLE_RecBuff[BLE_FRAME_SIZE*2+30];
u16 BLE_Frame[BLE_FRAME_SIZE];

u8 FunCode;
u16 FileLength; //ʮ��λ��ֵ���ȵ��ļ���С��֧��64KB�Ĺ̼�д��
u16 Progress;


//��ת��Ӧ�ó����
//addr:�û�������ʼ��ַ.
void JumpToAddr(u32 addr)
{
    JumpFun jumpAddr;
    if(((*(vu32*)addr)&0x2FFE0000)==0x20000000) //���ջ����ַ�Ƿ�Ϸ�.
    { 
        jumpAddr=(JumpFun)*(vu32*)(addr+4); //�û��������ڶ�����Ϊ����ʼ��ַ(��λ��ַ)
        MSR_MSP(*(vu32*)addr); //��ʼ��APP��ջָ��(�û��������ĵ�һ�������ڴ��ջ����ַ)
        jumpAddr(); //��ת��APP.
    }
}

void SPP_Download(u8 dat) {
    u16 s = 0, i = 0;
//    u16 recCRC = 0, calCRC = 0;
    u16 datLength = 0;
    u8 checkout = 0;
    static u16 buffCounter = 0;
    static u8 hash[16] = {0};
    SPP_RecBuff[buffCounter++] = USART_ReceiveData(USART1);
    if (buffCounter >= SPP_FRAME_SIZE) {
        buffCounter = 0;
        for (s = 0; s < SPP_FRAME_SIZE; s++) {
            if (SPP_RecBuff[s] == 0x55 && SPP_RecBuff[s+1] == 0xaa
               && SPP_RecBuff[s+2] == 0x55 && SPP_RecBuff[s+3] == 0xaa) {
                datLength = SPP_RecBuff[s+4];
                datLength <<= 8;
                datLength |= SPP_RecBuff[s+5];
                break;
            }
        }
        if (s+datLength < SPP_FRAME_SIZE) {
//                calCRC = CRCCheckout(SPP_RecBuff+s, datLength);
//                recCRC = SPP_RecBuff[s+datLength];
//                recCRC <<= 8;
//                recCRC |= SPP_RecBuff[s+datLength+1];
//                if (calCRC == recCRC) {
            MD5Final(hash, SPP_RecBuff+s, datLength);
            for (i = 0; i < 16; i++) {
                if (hash[i] == SPP_RecBuff[datLength+i+s]) {
                    checkout++;
                }
            }
            if (checkout >= 16) {
                s += 6;
                FunCode = SPP_RecBuff[s++];
                if (FunCode == 1) {
                    FileLength = SPP_RecBuff[s++];
                    FileLength <<= 8;
                    FileLength |= SPP_RecBuff[s++];
                }
                else if (FunCode == 2) {
                    for (i = 0; i < SPP_FRAME_SIZE; i++) {
                        SPP_Frame[i] = SPP_RecBuff[s++];
                        SPP_Frame[i] |= (u16)SPP_RecBuff[s++] << 8;
                    }
                    Progress = SPP_RecBuff[s++];
                    Progress <<= 8;
                    Progress |= SPP_RecBuff[s++];
                    STMFLASH_Write(FLASH_APP_ADDR + Progress, SPP_Frame, SPP_FRAME_SIZE);
                    SendByte(0x55);
                }
            } else {
                SendByte(0xaa);
            }
        }
    }
}

void BLE_Download(u8 dat) {
    u16 s = 0, i = 0;
//    u16 recCRC = 0, calCRC = 0;
    u16 datLength = 0;
    u8 checkout = 0;
    static u16 buffCounter = 0;
    static u8 hash[16] = {0};
    BLE_RecBuff[buffCounter++] = USART_ReceiveData(USART1);
    if (buffCounter >= BLE_FRAME_SIZE) {
        buffCounter = 0;
        for (s = 0; s < BLE_FRAME_SIZE; s++) {
            if (BLE_RecBuff[s] == 0x55 && BLE_RecBuff[s+1] == 0xaa
           && BLE_RecBuff[s+2] == 0x55 && BLE_RecBuff[s+3] == 0xaa) {
                datLength = BLE_RecBuff[s+4];
                datLength <<= 8;
                datLength |= BLE_RecBuff[s+5];
                break;
            }
        }
        if (s+datLength < BLE_FRAME_SIZE) {
//                calCRC = CRCCheckout(BLE_RecBuff+s, datLength);
//                recCRC = BLE_RecBuff[s+datLength];
//                recCRC <<= 8;
//                recCRC |= BLE_RecBuff[s+datLength+1];
//                if (calCRC == recCRC) {
//            MD5Final(hash, BLE_RecBuff+s, datLength);
            for (i = 0; i < 16; i++) {
                if (hash[i] == BLE_RecBuff[datLength+i+s]) {
                    checkout++;
                }
            }
            if (checkout >= 16) {
                s += 6;
                FunCode = BLE_RecBuff[s++];
                if (FunCode == 1) {
                    FileLength = BLE_RecBuff[s++];
                    FileLength <<= 8;
                    FileLength |= BLE_RecBuff[s++];
                    delay_ms(10);
                }
                else if (FunCode == 2) {
                    for (i = 0; i < BLE_FRAME_SIZE; i++) {
                        BLE_Frame[i] = BLE_RecBuff[s++];
                        BLE_Frame[i] |= (u16)BLE_RecBuff[s++] << 8;
                    }
                    Progress = BLE_RecBuff[s++];
                    Progress <<= 8;
                    Progress |= BLE_RecBuff[s++];
                    STMFLASH_Write(FLASH_APP_ADDR + Progress, BLE_Frame, BLE_FRAME_SIZE);
                    SendByte(0x55);
                }
            } else {
                SendByte(0xaa);
            }
        }
    }
}

void USART1_IRQHandler(void)                    //����1�жϷ������
{
    u8 buff = 0;
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 
    {
        buff = USART_ReceiveData(USART1);
        if (DownloadMode) {
            SPP_Download(buff);
        } else {
            BLE_Download(buff);
        }
    }
}

void SendByte(u8 byte)
{
    USART_SendData(USART1,byte);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);
}


void PrintFloat(double value, u8 precision) //���ڴ�ӡ������������precisionΪ��ȷλ��
{   
    u8 i = 0;
    char* text = FloatToString(value, precision);
    for(i = 0; *(text + i) != 0; i++) {
        SendByte(*(text + i));
    }
}
void PrintInt(long value)              //���ڴ�ӡ����������
{
    u8 i = 0;
    char* text = IntToString(value);
    for(i = 0; *(text + i) != 0; i++) {
        SendByte(*(text + i));
    }
}
void PrintText(char* text)           //���ڴ�ӡ�ַ���
{
    u8 i = 0;
    for(i = 0; *(text + i) != 0; i++) {
        SendByte(*(text + i));
    }
}
