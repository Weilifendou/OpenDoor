#include "uart.h"
#include "stdio.h"
#include "str.h"
#include "stmflash.h"


//���´��룬���棬ʱ����bug����������Ƕ��ʽϵͳ��ʹ��
//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB

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
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void UART_Init(u32 bound){
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

}

void SendByte(u8 byte)
{
    USART_SendData(USART1, byte);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC )==RESET);
}



u16 CRCCheckout(u8 *dat, u16 length) {
    u8 temp = 0;
    u16 i = 0;
    u16 j = 0;
    u16 crc = 0xffff;
    for (i = 0; i < length; i++) {
        temp = *(dat+i) & 0x00ff;
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

u8 SendBuff[TX_LENGTH];
u8 RecBuff[RX_LENGTH];
u8 FunCode;
u16 Progress;

void SendData(void) {
    u8 i = 0, s = 0;
    u16 crc = 0;
    u8 datLength = 23;
    SendBuff[s++] = 0x55;
    SendBuff[s++] = 0xaa;
    SendBuff[s++] = datLength;
    crc = CRCCheckout(SendBuff, datLength);
    
    SendBuff[s++] = crc >> 8;
    SendBuff[s++] = crc;
    
    for (i = 0; i < TX_LENGTH; i++) {
        SendByte(SendBuff[i]);
    }
}


//��ת��Ӧ�ó����
//addr:�û�������ʼ��ַ.
//void JumpToAddr(u32 addr)
//{
//    JumpFun jumpAddr;
//    if(((*(vu32*)addr)&0x2FFE0000)==0x20000000) //���ջ����ַ�Ƿ�Ϸ�.
//    { 
//        jumpAddr=(JumpFun)*(vu32*)(addr+4); //�û��������ڶ�����Ϊ����ʼ��ַ(��λ��ַ)
//        MSR_MSP(*(vu32*)addr); //��ʼ��APP��ջָ��(�û��������ĵ�һ�������ڴ��ջ����ַ)
//        jumpAddr(); //��ת��APP.
//    }
//}


void USART1_IRQHandler(void)                    //����1�жϷ������
{
    u16 s = 0;
    u16 recCRC = 0, calCRC = 0;
    u16 datLength = 0;
    static u16 buffCounter = 0;
    u16 temp[1] = {0};
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 
    {
        RecBuff[buffCounter++] = USART_ReceiveData(USART1);
        if (buffCounter >= BUFF_SIZE) {
            buffCounter = 0;
            for (s = 0; s < BUFF_SIZE; s++) {
                if (RecBuff[s] == 0x55 && RecBuff[s+1] == 0xaa
               && RecBuff[s+2] == 0x55 && RecBuff[s+3] == 0xaa) {
                    datLength = RecBuff[s+4];
                    datLength <<= 8;
                    datLength |= RecBuff[s+5];
                    break;
                }
            }
            if (s+datLength < BUFF_SIZE) {
                calCRC = CRCCheckout(RecBuff+s, datLength);
                recCRC = RecBuff[s+datLength];
                recCRC <<= 8;
                recCRC |= RecBuff[s+datLength+1];
                if (calCRC == recCRC) {
                    s += 6;
                    FunCode = RecBuff[s++];
                    if (FunCode == 0x55) {
                        temp[0] = 0xff;
                        STMFLASH_Write(TRANSFER_MODE_ADDR, temp, 1);
                        NVIC_SystemReset();
                    }
                    else if (FunCode == 0xaa) {
                        temp[0] = 0;
                        STMFLASH_Write(TRANSFER_MODE_ADDR, temp, 1);
                        NVIC_SystemReset();
                    }
                }
            }
        }
    }
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


