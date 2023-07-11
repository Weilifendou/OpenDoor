#include "myiic.h"
#include "delay.h"

//��ʼ�����IIC
void SGP30_IIC_Init(void)
{                         
    GPIO_InitTypeDef GPIO_InitStructure;
    //RCC->APB2ENR|=1<<4;//��ʹ������IO PORTCʱ�� 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);    
       
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
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


//����IIC��ʼ�ź�
void SGP30_IIC_Start(void)
{
    SDA_OUT();     //sda�����
    SGP30_IIC_SDA=1;            
    SGP30_IIC_SCL=1;
    SGP30_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
    SGP30_IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}      
//����IICֹͣ�ź�
void SGP30_IIC_Stop(void)
{
    SDA_OUT();//sda�����
    SGP30_IIC_SCL=0;
    SGP30_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
    SGP30_IIC_SCL=1; 
    SGP30_IIC_SDA=1; //����I2C���߽����ź�                               
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 SGP30_IIC_Wait_Ack(void)
{
    u8 ucErrTime=0;
    SDA_IN(); //SDA����Ϊ����  
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
    SGP30_IIC_SCL=0;//ʱ�����0        
    return 0;  
} 
//����ACKӦ��
void SGP30_IIC_Ack(void)
{
    SGP30_IIC_SCL=0;
    SDA_OUT();
    SGP30_IIC_SDA=0;
    SGP30_IIC_SCL=1;
    SGP30_IIC_SCL=0;
}
//������ACKӦ��            
void SGP30_IIC_NAck(void)
{
    SGP30_IIC_SCL=0;
    SDA_OUT();
    SGP30_IIC_SDA=1;
    SGP30_IIC_SCL=1;
    SGP30_IIC_SCL=0;
}                                          
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��              
void SGP30_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
    SDA_OUT();         
    SGP30_IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        SGP30_IIC_SDA=(txd&0x80)>>7;
        txd<<=1;       
        SGP30_IIC_SCL=1;
        SGP30_IIC_SCL=0;    
    }     
}         
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 SGP30_IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++)
    {
        SGP30_IIC_SCL=0; 
        SGP30_IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
    }                     
    if (!ack)
        SGP30_IIC_NAck();//����nACK
    else
        SGP30_IIC_Ack(); //����ACK   
    return receive;
}





















