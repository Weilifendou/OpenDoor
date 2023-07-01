/************************************************************************************

* Function List:
*    1. void I2C_Configuration(void) -- 配置CPU的硬件I2C
* 2. void I2C_WriteByte(uint8_t addr,uint8_t data) -- 向寄存器地址写一个byte的数据
* 3. void WriteCmd(unsigned char I2C_Command) -- 写命令
* 4. void WriteDat(unsigned char I2C_Data) -- 写数据
* 5. void OLED_Init(void) -- OLED屏初始化
* 6. void OLED_SetPos(unsigned char x, unsigned char y) -- 设置起始点坐标
* 7. void OLED_Fill(unsigned char fill_Data) -- 全屏填充
* 8. void OLED_CLS(void) -- 清屏
* 9. void OLED_ON(void) -- 唤醒
* 10. void OLED_OFF(void) -- 睡眠
* 11. void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize) -- 显示字符串(字体大小有6*8和8*16两种)
* 12. void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N) -- 显示中文(中文需要先取模，然后放到codetab.h中)
* 13. void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]) -- BMP图片
*
* History: none;
*
*************************************************************************************/

#include "oled.h"
#include "delay.h"
#include "codetab.h"

static char StrBuff[4][17] = {0};

//初始化IIC
void OLED_IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //RCC->APB2ENR|=1<<4;//先使能外设IO PORTC时钟 
    RCC_APB2PeriphClockCmd(    RCC_APB2Periph_GPIOB, ENABLE );    
       
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
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


//产生IIC起始信号
void OLED_IIC_Start(void)
{
    OLED_SDA_OUT();     //sda线输出
    OLED_IIC_SDA=1;            
    OLED_IIC_SCL=1;
    OLED_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
    OLED_IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}      
//产生IIC停止信号
void OLED_IIC_Stop(void)
{
    OLED_SDA_OUT();//sda线输出
    OLED_IIC_SCL=0;
    OLED_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
    OLED_IIC_SCL=1; 
    OLED_IIC_SDA=1;//发送I2C总线结束信号                               
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 OLED_IIC_Wait_Ack(void)
{
    u8 ucErrTime=0;
    OLED_SDA_IN();      //SDA设置为输入  
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
    OLED_IIC_SCL=0;//时钟输出0        
    return 0;  
} 
//产生ACK应答
void OLED_IIC_Ack(void)
{
    OLED_IIC_SCL=0;
    OLED_SDA_OUT();
    OLED_IIC_SDA=0;
    OLED_IIC_SCL=1;
    OLED_IIC_SCL=0;
}
//不产生ACK应答            
void OLED_IIC_NAck(void)
{
    OLED_IIC_SCL=0;
    OLED_SDA_OUT();
    OLED_IIC_SDA=1;
    OLED_IIC_SCL=1;
    OLED_IIC_SCL=0;
}                                          
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答              
void OLED_IIC_Send_Byte(u8 txd)
{                        
    u8 t;
    OLED_SDA_OUT();
    OLED_IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        OLED_IIC_SDA=(txd&0x80)>>7;
        txd<<=1;       
        OLED_IIC_SCL=1;
        OLED_IIC_SCL=0;    
    }
    
}         
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 OLED_IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    OLED_SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
    {
        OLED_IIC_SCL=0; 
        OLED_IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
    }                     
    if (!ack)
        OLED_IIC_NAck();//发送nACK
    else
        OLED_IIC_Ack(); //发送ACK   
    return receive;
}


void OLED_Write(u8 a, u8 b)
{
    __disable_irq();   // 关闭总中断
    OLED_IIC_Start();
    OLED_IIC_Send_Byte(OLED_ADDRESS); //发送器件地址+写指令
    OLED_IIC_Wait_Ack();
    OLED_IIC_Send_Byte(a);        //发送控制字节
    OLED_IIC_Wait_Ack();
    OLED_IIC_Send_Byte(b);
    OLED_IIC_Wait_Ack();
    OLED_IIC_Stop();
    __enable_irq();   // 打开总中断
}


void WriteCmd(unsigned char I2C_Command)//写命令
{
    OLED_Write(0x00, I2C_Command);
}

void WriteDat(unsigned char I2C_Data)//写数据
{
    OLED_Write(0x40, I2C_Data);
}

void OLED_Init(void)
{
    OLED_IIC_Init();
    delay_ms(100); //这里的延时很重要
    WriteCmd(0xAE); //display off
    WriteCmd(0x20);    //Set Memory Addressing Mode    
    WriteCmd(0x10);    //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
    WriteCmd(0xb0);    //Set Page Start Address for Page Addressing Mode,0-7
    WriteCmd(0xc8);    //Set COM Output Scan Direction
    WriteCmd(0x00); //---set low column address
    WriteCmd(0x10); //---set high column address
    WriteCmd(0x40); //--set start line address
    WriteCmd(0x81); //--set contrast control register
    WriteCmd(0xff); //亮度调节 0x00~0xff
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

void OLED_SetPos(unsigned char x, unsigned char y) //设置起始点坐标
{ 
    WriteCmd(0xb0+y);
    WriteCmd(((x&0xf0)>>4)|0x10);
    WriteCmd((x&0x0f)|0x01);
}

void OLED_Fill(unsigned char fill_Data)//全屏填充
{
    unsigned char m,n;
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

void ClearStrBuff(void) {
    u8 i,j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 16; j++) {
            StrBuff[i][j] = ' ';
        }
        StrBuff[i][j] = 0;
    }
}
//void OLED_ClearContent(unsigned char fill_Data)//清楚内容
//{
//    unsigned char m,n;
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

//void OLED_ClearLine(unsigned char line)//清除行
//{
//    unsigned char n;
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
// Description    : 将OLED从休眠中唤醒
//--------------------------------------------------------------
void OLED_ON(void)
{
    WriteCmd(0X8D);  //设置电荷泵
    WriteCmd(0X14);  //开启电荷泵
    WriteCmd(0XAF);  //OLED唤醒
}

//--------------------------------------------------------------
// Prototype      : void OLED_OFF(void)
// Calls          : 
// Parameters     : none
// Description    : 让OLED休眠 -- 休眠模式下,OLED功耗不到10uA
//--------------------------------------------------------------
void OLED_OFF(void)
{
    WriteCmd(0X8D);  //设置电荷泵
    WriteCmd(0X10);  //关闭电荷泵
    WriteCmd(0XAE);  //OLED休眠
}

//--------------------------------------------------------------
// Prototype      : void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
// Calls          : 
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); ch[] -- 要显示的字符串; TextSize -- 字符大小(1:6*8 ; 2:8*16)
// Description    : 显示codetab.h中的ASCII字符,有6*8和8*16可选择
//--------------------------------------------------------------
void OLED_ShowStr(unsigned char x, unsigned char y, char* ch, unsigned char TextSize)
{
    unsigned char c = 0,i = 0,j = 0;
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

void OLED_CenterValidate(void) {
    u8 i = 0;
    for (i = 0; i < 3; i++) {
        OLED_ShowStr(0, i*2+1, StrBuff[i], 2);
    }
}

void OLED_Validate(void) {
    u8 i = 0;
    for (i = 0; i < 4; i++) {
        OLED_ShowStr(0, i*2, StrBuff[i], 2);
    }
}

//--------------------------------------------------------------
// Prototype      : void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
// Calls          : 
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); N:汉字在codetab.h中的索引
// Description    : 显示codetab.h中的汉字,16*16点阵
//--------------------------------------------------------------
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
{
    unsigned char wm=0;
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
// Prototype      : void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
// Calls          : 
// Parameters     : x0,y0 -- 起始点坐标(x0:0~127, y0:0~7); x1,y1 -- 起点对角线(结束点)的坐标(x1:1~128,y1:1~8)
// Description    : 显示BMP位图
//--------------------------------------------------------------
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[])
{
    unsigned int j=0;
    unsigned char x,y;

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



