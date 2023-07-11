#include "myiic.h"
#include "delay.h"

//初始化软件IIC
void SGP30_IIC_Init(void)
{                         
    GPIO_InitTypeDef GPIO_InitStructure;
    //RCC->APB2ENR|=1<<4;//先使能外设IO PORTC时钟 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);    
       
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
 
    SGP30_IIC_SCL=1;
    SGP30_IIC_SDA=1;

}

void SGP30_SDA_OUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void SGP30_SDA_IN(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}


//产生IIC起始信号
void SGP30_IIC_Start(void)
{
    SDA_OUT();     //sda线输出
    SGP30_IIC_SDA=1;            
    SGP30_IIC_SCL=1;
    SGP30_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
    SGP30_IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}      
//产生IIC停止信号
void SGP30_IIC_Stop(void)
{
    SDA_OUT();//sda线输出
    SGP30_IIC_SCL=0;
    SGP30_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
    SGP30_IIC_SCL=1; 
    SGP30_IIC_SDA=1; //发送I2C总线结束信号                               
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 SGP30_IIC_Wait_Ack(void)
{
    u8 ucErrTime=0;
    SDA_IN(); //SDA设置为输入  
    SGP30_IIC_SDA=1;
    SGP30_IIC_SCL=1;
    while(READ_SDA)
    {
        ucErrTime++;
        if(ucErrTime>250)
        {
            SGP30_IIC_Stop();
            return 1;
        }
    }
    SGP30_IIC_SCL=0;//时钟输出0        
    return 0;  
} 
//产生ACK应答
void SGP30_IIC_Ack(void)
{
    SGP30_IIC_SCL=0;
    SDA_OUT();
    SGP30_IIC_SDA=0;
    SGP30_IIC_SCL=1;
    SGP30_IIC_SCL=0;
}
//不产生ACK应答            
void SGP30_IIC_NAck(void)
{
    SGP30_IIC_SCL=0;
    SDA_OUT();
    SGP30_IIC_SDA=1;
    SGP30_IIC_SCL=1;
    SGP30_IIC_SCL=0;
}                                          
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答              
void SGP30_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
    SDA_OUT();         
    SGP30_IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        SGP30_IIC_SDA=(txd&0x80)>>7;
        txd<<=1;       
        SGP30_IIC_SCL=1;
        SGP30_IIC_SCL=0;    
    }     
}         
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 SGP30_IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++)
    {
        SGP30_IIC_SCL=0; 
        SGP30_IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
    }                     
    if (!ack)
        SGP30_IIC_NAck();//发送nACK
    else
        SGP30_IIC_Ack(); //发送ACK   
    return receive;
}





















