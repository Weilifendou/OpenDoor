#include "sys.h"
#include "uart.h"
#include "str.h"

u8 SendBuff[TX_LENGTH];
u8 RecBuff[RX_LENGTH];

extern u16 Temperature, Humidty;
extern u8 white, yellow, steer;


void UART_Init(u32 bound){
  //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
     
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);    //使能USART1，GPIOA时钟

    //USART1_TX   GPIOA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9

    //USART1_RX      GPIOA.10初始化
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

    //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3 ;//抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);    //根据指定的参数初始化VIC寄存器

    //USART 初始化设置

    USART_InitStructure.USART_BaudRate = bound;//串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    //收发模式

    USART_Init(USART1, &USART_InitStructure); //初始化串口1
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
    USART_Cmd(USART1, ENABLE);                    //使能串口1 

}

void SendByte(u8 byte)
{
    USART_SendData(USART1, byte);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC )==RESET);
}

void PrintFloat(double value, u8 precision) //串口打印浮点数函数，precision为精确位数
{   
    u8 i = 0;
    char* text = FloatToString(value, precision);
    for(i = 0; *(text+i) != 0; i++) {
        SendByte(*(text+i));
    }
}
void PrintInt(long value)              //串口打印整型数函数
{
    u8 i = 0;
    char* text = IntToString(value);
    for(i = 0; *(text+i) != 0; i++) {
        SendByte(*(text+i));
    }
}
void PrintText(char* text)           //串口打印字符串
{
    u8 i = 0;
    for(i = 0; *(text+i) != 0; i++) {
        SendByte(*(text+i));
    }
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


void SendData(void) {
    u8 i = 0, s = 0;
    u16 crc = 0;
    u8 datLength = 7;
    SendBuff[s++] = 0x55;
    SendBuff[s++] = 0xaa;
    SendBuff[s++] = datLength;
    SendBuff[s++] = Temperature >> 8;
    SendBuff[s++] = Temperature;
    SendBuff[s++] = Humidty >> 8;
    SendBuff[s++] = Humidty;
    
    crc = CRCCheckout(SendBuff, datLength);
    
    SendBuff[s++] = crc >> 8;
    SendBuff[s++] = crc;
    
    for (i = 0; i < TX_LENGTH; i++) {
        SendByte(SendBuff[i]);
    }
}


//跳转到应用程序段
//addr:用户代码起始地址.
//void JumpToAddr(u32 addr)
//{
//    JumpFun jumpAddr;
//    if(((*(vu32*)addr)&0x2FFE0000)==0x20000000) //检查栈顶地址是否合法.
//    { 
//        jumpAddr=(JumpFun)*(vu32*)(addr+4); //用户代码区第二个字为程序开始地址(复位地址)
//        MSR_MSP(*(vu32*)addr); //初始化APP堆栈指针(用户代码区的第一个字用于存放栈顶地址)
//        jumpAddr(); //跳转到APP.
//    }
//}
void USART1_IRQHandler(void)                    //串口1中断服务程序
{
    u8 s = 0;
    u16 recCRC = 0, calCRC = 0;
    u16 datLength = 0;
    static u8 buffCounter = 0;
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 
    {
        RecBuff[buffCounter++] = USART_ReceiveData(USART1);
        if (buffCounter >= RX_LENGTH) {
            buffCounter = 0;
            for (s = 0; s < RX_LENGTH; s++) {
                if (RecBuff[s] == 0x55 && RecBuff[s+1] == 0xaa) {
                    datLength = RecBuff[s+2];
                    break;
                }
            }
            if (s+datLength < RX_LENGTH) {
                calCRC = CRCCheckout(RecBuff+s, datLength);
                recCRC = RecBuff[s+datLength];
                recCRC <<= 8;
                recCRC |= RecBuff[s+datLength+1];
                if (calCRC == recCRC) {
                    s += 3;
                    white = RecBuff[s++];
                    yellow = RecBuff[s++];
                    steer = RecBuff[s++];
                }
            }
        }
    }
}
