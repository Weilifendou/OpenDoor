/************************************************************************************

* Function List:
*    1. void I2C_Configuration(void) -- ����CPU��Ӳ��I2C
* 2. void I2C_WriteByte(uint8_t addr,uint8_t data) -- ��Ĵ�����ַдһ��byte������
* 3. void WriteCmd(u8 I2C_Command) -- д����
* 4. void WriteDat(u8 I2C_Data) -- д����
* 5. void OLED_Init(void) -- OLED����ʼ��
* 6. void OLED_SetPos(u8 x, u8 y) -- ������ʼ������
* 7. void OLED_Fill(u8 fill_Data) -- ȫ�����
* 8. void OLED_CLS(void) -- ����
* 9. void OLED_ON(void) -- ����
* 10. void OLED_OFF(void) -- ˯��
* 11. void OLED_ShowStr(u8 x, u8 y, u8 ch[], u8 TextSize) -- ��ʾ�ַ���(�����С��6*8��8*16����)
* 12. void OLED_ShowCN(u8 x, u8 y, u8 N) -- ��ʾ����(������Ҫ��ȡģ��Ȼ��ŵ�codetab.h��)
* 13. void OLED_DrawBMP(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[]) -- BMPͼƬ
*
* History: none;
*
*************************************************************************************/

#include "oled.h"
#include "delay.h"
#include "codetab.h"

static char StrBuff[4][17] = {0};

//��ʼ��IIC
void OLED_IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //RCC->APB2ENR|=1<<4;//��ʹ������IO PORTCʱ�� 
    RCC_APB2PeriphClockCmd(    RCC_APB2Periph_GPIOB, ENABLE );    
       
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
 
    OLED_IIC_SCL=1;
    OLED_IIC_SDA=1;
}

void OLED_SDA_OUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void OLED_SDA_IN(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}


//����IIC��ʼ�ź�
void OLED_IIC_Start(void)
{
    OLED_SDA_OUT();     //sda�����
    OLED_IIC_SDA=1;            
    OLED_IIC_SCL=1;
    OLED_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
    OLED_IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}      
//����IICֹͣ�ź�
void OLED_IIC_Stop(void)
{
    OLED_SDA_OUT();//sda�����
    OLED_IIC_SCL=0;
    OLED_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
    OLED_IIC_SCL=1; 
    OLED_IIC_SDA=1;//����I2C���߽����ź�                               
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 OLED_IIC_Wait_Ack(void)
{
    u8 ucErrTime=0;
    OLED_SDA_IN();      //SDA����Ϊ����  
    OLED_IIC_SDA=1;   
    OLED_IIC_SCL=1;     
    while(READ_SDA)
    {
        ucErrTime++;
        if(ucErrTime>250)
        {
            OLED_IIC_Stop();
            return 1;
        }
    }
    OLED_IIC_SCL=0;//ʱ�����0        
    return 0;  
} 
//����ACKӦ��
void OLED_IIC_Ack(void)
{
    OLED_IIC_SCL=0;
    OLED_SDA_OUT();
    OLED_IIC_SDA=0;
    OLED_IIC_SCL=1;
    OLED_IIC_SCL=0;
}
//������ACKӦ��            
void OLED_IIC_NAck(void)
{
    OLED_IIC_SCL=0;
    OLED_SDA_OUT();
    OLED_IIC_SDA=1;
    OLED_IIC_SCL=1;
    OLED_IIC_SCL=0;
}                                          
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��              
void OLED_IIC_Send_Byte(u8 txd)
{                        
    u8 t;
    OLED_SDA_OUT();
    OLED_IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        OLED_IIC_SDA=(txd&0x80)>>7;
        txd<<=1;       
        OLED_IIC_SCL=1;
        OLED_IIC_SCL=0;    
    }
    
}         
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 OLED_IIC_Read_Byte(u8 ack)
{
    u8 i,receive=0;
    OLED_SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
    {
        OLED_IIC_SCL=0; 
        OLED_IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
    }                     
    if (!ack)
        OLED_IIC_NAck();//����nACK
    else
        OLED_IIC_Ack(); //����ACK   
    return receive;
}


void OLED_Write(u8 a, u8 b)
{
//    __disable_irq();   // �ر����ж�
    OLED_IIC_Start();
    OLED_IIC_Send_Byte(OLED_ADDRESS); //����������ַ+дָ��
    OLED_IIC_Wait_Ack();
    OLED_IIC_Send_Byte(a);        //���Ϳ����ֽ�
    OLED_IIC_Wait_Ack();
    OLED_IIC_Send_Byte(b);
    OLED_IIC_Wait_Ack();
    OLED_IIC_Stop();
//    __enable_irq();   // �����ж�
}


void WriteCmd(u8 I2C_Command)//д����
{
    OLED_Write(0x00, I2C_Command);
}

void WriteDat(u8 I2C_Data)//д����
{
    OLED_Write(0x40, I2C_Data);
}

void OLED_Init(void)
{
    OLED_IIC_Init();
    delay_ms(100); //�������ʱ����Ҫ
    WriteCmd(0xAE); //display off
    WriteCmd(0x20);    //Set Memory Addressing Mode    
    WriteCmd(0x10);    //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
    WriteCmd(0xb0);    //Set Page Start Address for Page Addressing Mode,0-7
    WriteCmd(0xc8);    //Set COM Output Scan Direction
    WriteCmd(0x00); //---set low column address
    WriteCmd(0x10); //---set high column address
    WriteCmd(0x40); //--set start line address
    WriteCmd(0x81); //--set contrast control register
    WriteCmd(0xff); //���ȵ��� 0x00~0xff
    WriteCmd(0xa1); //--set segment re-map 0 to 127
    WriteCmd(0xa6); //--set normal display
    WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
    WriteCmd(0x3F); //
    WriteCmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
    WriteCmd(0xd3); //-set display offset
    WriteCmd(0x00); //-not offset
    WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
    WriteCmd(0xf0); //--set divide ratio
    WriteCmd(0xd9); //--set pre-charge period
    WriteCmd(0x22); //
    WriteCmd(0xda); //--set com pins hardware configuration
    WriteCmd(0x12);
    WriteCmd(0xdb); //--set vcomh
    WriteCmd(0x20); //0x20,0.77xVcc
    WriteCmd(0x8d); //--set DC-DC enable
    WriteCmd(0x14); //
    WriteCmd(0xaf); //--turn on oled panel
    
}

void OLED_SetPos(u8 x, u8 y) //������ʼ������
{ 
    WriteCmd(0xb0+y);
    WriteCmd(((x&0xf0)>>4)|0x10);
    WriteCmd((x&0x0f)|0x01);
}

void OLED_Fill(u8 fill_Data)//ȫ�����
{
    u8 m,n;
    for(m=0;m<8;m++)
    {
        WriteCmd(0xb0+m);        //page0-page1
        WriteCmd(0x00);        //low column start address
        WriteCmd(0x10);        //high column start address
        for(n=0;n<128;n++)
        {
            WriteDat(fill_Data);
        }
    }
    
}

void OLED_ClearStrBuff(void) {
    u8 i,j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 16; j++) {
            StrBuff[i][j] = ' ';
        }
        StrBuff[i][j] = 0;
    }
}
//void OLED_ClearContent(u8 fill_Data)//�������
//{
//    u8 m,n;
//    for(m=2;m<8;m++)
//    {
//        WriteCmd(0xb0+m);        //page0-page1
//        WriteCmd(0x00);        //low column start address
//        WriteCmd(0x10);        //high column start address
//        for(n=0;n<128;n++)
//        {
//            WriteDat(fill_Data);
//        }
//    }
//}

//void OLED_ClearLine(u8 line)//�����
//{
//    u8 n;
//    WriteCmd(0xb0+line);        //page0-page1
//    WriteCmd(0x00);        //low column start address
//    WriteCmd(0x10);        //high column start address
//    for(n=0;n<128;n++)
//    {
//        WriteDat(0xFF);
//    }
//}

//--------------------------------------------------------------
// Prototype      : void OLED_ON(void)
// Calls          : 
// Parameters     : none
// Description    : ��OLED�������л���
//--------------------------------------------------------------
void OLED_ON(void)
{
    WriteCmd(0X8D);  //���õ�ɱ�
    WriteCmd(0X14);  //������ɱ�
    WriteCmd(0XAF);  //OLED����
}

//--------------------------------------------------------------
// Prototype      : void OLED_OFF(void)
// Calls          : 
// Parameters     : none
// Description    : ��OLED���� -- ����ģʽ��,OLED���Ĳ���10uA
//--------------------------------------------------------------
void OLED_OFF(void)
{
    WriteCmd(0X8D);  //���õ�ɱ�
    WriteCmd(0X10);  //�رյ�ɱ�
    WriteCmd(0XAE);  //OLED����
}

//--------------------------------------------------------------
// Prototype      : void OLED_ShowChar(u8 x, u8 y, u8 ch[], u8 TextSize)
// Calls          : 
// Parameters     : x,y -- ��ʼ������(x:0~127, y:0~7); ch[] -- Ҫ��ʾ���ַ���; TextSize -- �ַ���С(1:6*8 ; 2:8*16)
// Description    : ��ʾcodetab.h�е�ASCII�ַ�,��6*8��8*16��ѡ��
//--------------------------------------------------------------
void OLED_ShowStr(u8 x, u8 y, char* ch, u8 TextSize)
{
    u8 c = 0,i = 0,j = 0;
    switch(TextSize)
    {
        case 1:
        {
            while(*(ch+j) != '\0')
            {
                c = *(ch+j) - 32;
                if(x > 126)
                {
                    x = 0;
                    y++;
                }
                OLED_SetPos(x,y);
                for(i=0;i<6;i++)
                    WriteDat(F6x8[c][i]);
                x += 6;
                j++;
            }
        }break;
        case 2:
        {
            while(*(ch+j) != '\0')
            {
                c = *(ch+j) - 32;
                if(x > 120)
                {
                    x = 0;
                    y++;
                }
                OLED_SetPos(x,y);
                for(i=0;i<8;i++)
                    WriteDat(F8X16[c*16+i]);
                OLED_SetPos(x,y+1);
                for(i=0;i<8;i++)
                    WriteDat(F8X16[c*16+i+8]);
                x += 8;
                j++;
            }
        }break;
    }
}

//void OLED_CenterShowStr(u8 y, char* ch) {
//    u8 i = 0;
//    u8 x = 0;
//    for (i = 0; ch[i] != 0; i++);
//    if (i >= 16) i = 16;
//    x = 64 - i * 8 / 2; //one char take up 8 pixel, and get its half length
//    OLED_ShowStr(x, y, ch, 2);
//}

void OLED_InsertStr(u8 start, u8 line, char* ch, u8 mode) {
    u8 i = 0;
    if (mode) {
        for (i = 0; ch[i] != 0; i++);
        if (i >= 16) i = 16;
        start = 8 - i / 2;
        for (i = 0; ch[i] != 0; i++) {
            StrBuff[line][start+i] = ch[i];
        }
    } else {
        for (i = 0; ch[i] != 0; i++) {
            if (start + i >= 16) break;
            StrBuff[line][start+i] = ch[i];
        }
    }
}

void OLED_ThreeLineCenterValidate(void) {
    u8 i = 0;
    for (i = 0; i < 3; i++) {
        OLED_ShowStr(0, i*2+1, StrBuff[i], 2);
    }
}
void OLED_TwoLineCenterValidate(void) {
    OLED_ShowStr(0, 1, StrBuff[0], 2);
    OLED_ShowStr(0, 4, StrBuff[1], 2);
}

void OLED_Validate(void) {
    u8 i = 0;
    for (i = 0; i < 4; i++) {
        OLED_ShowStr(0, i*2, StrBuff[i], 2);
    }
}

//--------------------------------------------------------------
// Prototype      : void OLED_ShowCN(u8 x, u8 y, u8 N)
// Calls          : 
// Parameters     : x,y -- ��ʼ������(x:0~127, y:0~7); N:������codetab.h�е�����
// Description    : ��ʾcodetab.h�еĺ���,16*16����
//--------------------------------------------------------------
void OLED_ShowCN(u8 x, u8 y, u8 N)
{
    u8 wm=0;
    unsigned int  adder=32*N;
    OLED_SetPos(x, y);
    for(wm = 0;wm < 16;wm++)
    {
        WriteDat(~F16x16[adder]);
        adder++;
    }
    OLED_SetPos(x,y + 1);
    for(wm = 0;wm < 16;wm++)
    {
        WriteDat(~F16x16[adder]);
        adder++;
    }
}

//--------------------------------------------------------------
// Prototype      : void OLED_DrawBMP(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[]);
// Calls          : 
// Parameters     : x0,y0 -- ��ʼ������(x0:0~127, y0:0~7); x1,y1 -- ���Խ���(������)������(x1:1~128,y1:1~8)
// Description    : ��ʾBMPλͼ
//--------------------------------------------------------------
void OLED_DrawBMP(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[])
{
    unsigned int j=0;
    u8 x,y;

  if(y1%8==0)
        y = y1/8;
  else
        y = y1/8 + 1;
    for(y=y0;y<y1;y++)
    {
        OLED_SetPos(x0,y);
        for(x=x0;x<x1;x++)
        {
            WriteDat(BMP[j++]);
        }
    }
}

void OLED_ShowCNS(u8 x, u8 y,u8 cns[], u8 num)
{
    u8 wm = 0, i = 0;
    for(i=0; i<num; i++)
    {
        OLED_SetPos(x+i*16, y);
        for(wm = 0;wm < 16;wm++)
        {
            WriteDat(cns[32*i+wm]);
        }
        OLED_SetPos(x+i*16,y + 1);
        for(wm = 16;wm < 32;wm++)
        {
            WriteDat(cns[32*i+wm]);
        }
    }
}



