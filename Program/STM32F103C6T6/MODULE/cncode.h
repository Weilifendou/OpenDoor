#ifndef __CNCODE_H
#define __CNCODE_H 			   
#include "sys.h" 

u8 Title[] = {
0x00,0x00,0x10,0x10,0x98,0xA4,0x47,0x44,0xA4,0x54,0x0C,0x04,0x00,0x00,0x00,0x00,
0x00,0x81,0x89,0x89,0x44,0x44,0x4A,0x31,0x21,0x11,0x09,0x05,0x03,0x00,0x00,0x00,/*"多",0*/

0x08,0x08,0x08,0xF8,0x08,0x08,0x08,0x10,0x10,0xFF,0x10,0x10,0x10,0xF0,0x00,0x00,
0x10,0x30,0x10,0x1F,0x08,0x88,0x48,0x30,0x0E,0x01,0x40,0x80,0x40,0x3F,0x00,0x00,/*"功",1*/

0x08,0xCC,0x4A,0x49,0x48,0x4A,0xCC,0x18,0x00,0x7F,0x88,0x88,0x84,0x82,0xE0,0x00,
0x00,0xFF,0x12,0x12,0x52,0x92,0x7F,0x00,0x00,0x7E,0x88,0x88,0x84,0x82,0xE0,0x00,/*"能",2*/

0x10,0x94,0x53,0x32,0x1E,0x32,0x52,0x10,0x00,0x7E,0x42,0x42,0x42,0x7E,0x00,0x00,
0x00,0x00,0x00,0xFF,0x49,0x49,0x49,0x49,0x49,0x49,0x49,0xFF,0x00,0x00,0x00,0x00,/*"智",3*/

0x08,0xCC,0x4A,0x49,0x48,0x4A,0xCC,0x18,0x00,0x7F,0x88,0x88,0x84,0x82,0xE0,0x00,
0x00,0xFF,0x12,0x12,0x52,0x92,0x7F,0x00,0x00,0x7E,0x88,0x88,0x84,0x82,0xE0,0x00,/*"能",4*/

0x00,0x00,0xF8,0x88,0x88,0x88,0x88,0xFF,0x88,0x88,0x88,0x88,0xF8,0x00,0x00,0x00,
0x00,0x00,0x1F,0x08,0x08,0x08,0x08,0x7F,0x88,0x88,0x88,0x88,0x9F,0x80,0xF0,0x00,/*"电",5*/

0x00,0x04,0x24,0x24,0x24,0x24,0x24,0xFF,0x24,0x24,0x24,0x24,0x24,0x04,0x00,0x00,
0x21,0x21,0x11,0x09,0xFD,0x83,0x41,0x23,0x05,0x09,0x11,0x29,0x25,0x41,0x41,0x00,/*"表",6*/
	
};

u8 QFKP[] = {
	0x40,0x42,0xCC,0x00,0x00,0x44,0x54,0x54,0x54,0x7F,0x54,0x54,0x54,0x44,0x40,0x00,
	0x00,0x00,0x7F,0x20,0x10,0x00,0xFF,0x15,0x15,0x15,0x55,0x95,0x7F,0x00,0x00,0x00,/*"请",0*/

	0x08,0x08,0xF9,0x4A,0x48,0xC8,0x48,0x20,0xD8,0x17,0x10,0x10,0xF0,0x10,0x10,0x00,
	0x40,0x30,0x0F,0x20,0x40,0x3F,0x80,0x40,0x21,0x16,0x08,0x16,0x21,0x40,0x80,0x00,/*"放",1*/

	0x40,0x40,0x40,0x40,0x40,0x40,0xFF,0x44,0x44,0x44,0x44,0x44,0x44,0x40,0x40,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x02,0x04,0x08,0x10,0x00,0x00,0x00,/*"卡",2*/

	0x00,0x00,0x00,0xFE,0x20,0x20,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x00,0x00,
	0x00,0x80,0x60,0x1F,0x02,0x02,0x02,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x00,/*"片",3*/



};


u8 CZCG[] = {
	0x04,0x04,0x84,0xC4,0xA4,0x9C,0x85,0x86,0x84,0x84,0xA4,0xC4,0x84,0x04,0x04,0x00,
	0x00,0x80,0x80,0x40,0x30,0x0F,0x00,0x00,0x00,0x7F,0x80,0x80,0x81,0xF0,0x00,0x00,/*"充",0*/

	0x00,0x80,0x60,0xF8,0x07,0x04,0xE4,0xA4,0xA4,0xBF,0xA4,0xA4,0xE4,0x04,0x00,0x00,
	0x01,0x00,0x00,0xFF,0x40,0x40,0x7F,0x4A,0x4A,0x4A,0x4A,0x4A,0x7F,0x40,0x40,0x00,/*"值",1*/

	0x00,0x00,0xF8,0x88,0x88,0x88,0x88,0x08,0x08,0xFF,0x08,0x09,0x0A,0xC8,0x08,0x00,
	0x80,0x60,0x1F,0x00,0x10,0x20,0x1F,0x80,0x40,0x21,0x16,0x18,0x26,0x41,0xF8,0x00,/*"成",2*/

	0x08,0x08,0x08,0xF8,0x08,0x08,0x08,0x10,0x10,0xFF,0x10,0x10,0x10,0xF0,0x00,0x00,
	0x10,0x30,0x10,0x1F,0x08,0x88,0x48,0x30,0x0E,0x01,0x40,0x80,0x40,0x3F,0x00,0x00,/*"功",3*/

};
u8 XFCG[] = {
   0x10,0x60,0x02,0x0C,0xC0,0x00,0xE2,0x2C,0x20,0x3F,0x20,0x28,0xE6,0x00,0x00,0x00,
   0x04,0x04,0x7C,0x03,0x00,0x00,0xFF,0x09,0x09,0x09,0x49,0x89,0x7F,0x00,0x00,0x00,/*"消",0*/

   0x00,0x02,0x3A,0xAA,0x6A,0x3F,0x2A,0x2A,0x2A,0xFF,0x2A,0xAA,0x2E,0xE0,0x00,0x00,
   0x00,0x02,0x81,0x9E,0x42,0x42,0x22,0x1A,0x22,0x22,0x42,0x5E,0x81,0x00,0x00,0x00,/*"费",1*/

   0x00,0x00,0xF8,0x88,0x88,0x88,0x88,0x08,0x08,0xFF,0x08,0x09,0x0A,0xC8,0x08,0x00,
   0x80,0x60,0x1F,0x00,0x10,0x20,0x1F,0x80,0x40,0x21,0x16,0x18,0x26,0x41,0xF8,0x00,/*"成",2*/

   0x08,0x08,0x08,0xF8,0x08,0x08,0x08,0x10,0x10,0xFF,0x10,0x10,0x10,0xF0,0x00,0x00,
   0x10,0x30,0x10,0x1F,0x08,0x88,0x48,0x30,0x0E,0x01,0x40,0x80,0x40,0x3F,0x00,0x00,/*"功",3*/

};
u8 WZCGKP[] = {
	0x80,0x80,0x88,0x88,0x88,0x88,0x88,0xFF,0x88,0x88,0x88,0x88,0x88,0x80,0x80,0x00,
	0x20,0x20,0x10,0x08,0x04,0x02,0x01,0xFF,0x01,0x02,0x04,0x08,0x10,0x20,0x20,0x00,/*"未",0*/

	0x10,0x60,0x02,0x8C,0x00,0x08,0x08,0x08,0x09,0xFA,0x08,0x08,0x08,0x08,0x00,0x00,
	0x04,0x04,0x7E,0x01,0x40,0x40,0x41,0x41,0x41,0x7F,0x41,0x41,0x41,0x41,0x40,0x00,/*"注",1*/

	0x80,0x80,0x80,0xFE,0x82,0x82,0xFE,0x80,0x80,0xFE,0x82,0x82,0xFE,0x80,0x80,0x00,
	0x00,0x80,0x40,0x3F,0x00,0x40,0x7F,0x80,0x60,0x1F,0x40,0x80,0x7F,0x00,0x00,0x00,/*"册",2*/

	0x40,0x42,0xCC,0x00,0x04,0x84,0xC4,0xB4,0x8D,0x86,0xC4,0x34,0x04,0xC4,0x04,0x00,
	0x00,0x00,0x3F,0x10,0x88,0x90,0x48,0x44,0x22,0x11,0x08,0x14,0x23,0xC0,0x00,0x00,/*"该",3*/

	0x40,0x40,0x40,0x40,0x40,0x40,0xFF,0x44,0x44,0x44,0x44,0x44,0x44,0x40,0x40,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x02,0x04,0x08,0x10,0x00,0x00,0x00,/*"卡",4*/

	0x00,0x00,0x00,0xFE,0x20,0x20,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x00,0x00,
	0x00,0x80,0x60,0x1F,0x02,0x02,0x02,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x00,/*"片",5*/

};
u8 DKCW[] = {
   0x40,0x40,0x42,0xCC,0x00,0x00,0x20,0x24,0xA4,0x24,0x3F,0xA4,0x24,0xA4,0x60,0x00,
   0x00,0x00,0x00,0x7F,0x20,0x10,0x88,0x8A,0x4C,0x29,0x18,0x0F,0x18,0x28,0xC8,0x00,/*"读",0*/

   0x40,0x40,0x40,0x40,0x40,0x40,0xFF,0x44,0x44,0x44,0x44,0x44,0x44,0x40,0x40,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x02,0x04,0x08,0x10,0x00,0x00,0x00,/*"卡",1*/

   0x40,0x30,0xEF,0x24,0x64,0x48,0x48,0x7F,0x48,0x48,0x48,0x7F,0x48,0x48,0x40,0x00,
   0x01,0x01,0x7F,0x21,0x11,0x00,0xFF,0x49,0x49,0x49,0x49,0x49,0xFF,0x00,0x00,0x00,/*"错",2*/

   0x40,0x42,0xCC,0x00,0x00,0x80,0x9E,0x92,0x92,0x92,0x92,0x92,0x9E,0x80,0x00,0x00,
   0x00,0x00,0x7F,0x20,0x94,0x84,0x44,0x24,0x14,0x0F,0x14,0x24,0x44,0x84,0x84,0x00,/*"误",3*/

};
u8 DQYE[] = {
	0x00,0x40,0x42,0x44,0x58,0x40,0x40,0x7F,0x40,0x40,0x50,0x48,0xC6,0x00,0x00,0x00,
	0x00,0x40,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0xFF,0x00,0x00,0x00,/*"当",0*/

	0x08,0x08,0xE8,0x29,0x2E,0x28,0xE8,0x08,0x08,0xC8,0x0C,0x0B,0xE8,0x08,0x08,0x00,
	0x00,0x00,0xFF,0x09,0x49,0x89,0x7F,0x00,0x00,0x0F,0x40,0x80,0x7F,0x00,0x00,0x00,/*"前",1*/

	0x80,0x80,0x40,0x20,0x50,0x48,0x44,0xC3,0x44,0x48,0x50,0x20,0x40,0x80,0x80,0x00,
	0x00,0x40,0x22,0x1A,0x02,0x42,0x82,0x7F,0x02,0x02,0x02,0x0A,0x12,0x60,0x00,0x00,/*"余",2*/

	0x00,0x8C,0x44,0xB5,0x26,0xA4,0x64,0x0C,0x02,0xF2,0x1A,0xD6,0x12,0xF2,0x02,0x00,
	0x10,0x08,0xFC,0x4A,0x49,0x4A,0xFC,0x08,0x80,0x4F,0x30,0x0F,0x10,0x2F,0xC0,0x00,/*"额",3*/

};

u8 SK[] =
{
	0x10,0x28,0x24,0xE3,0x24,0x28,0x50,0x42,0x42,0x4A,0xD2,0x6A,0x46,0x40,0xC0,0x00,
	0x01,0xF9,0x49,0x4F,0x49,0xF9,0x01,0x00,0x40,0x80,0x7F,0x00,0x00,0x01,0x00,0x00,/*"舒",0*/

	0x20,0x10,0x2C,0xE7,0x24,0x24,0x00,0xFE,0x92,0x92,0x92,0x92,0x92,0xFE,0x00,0x00,
	0x01,0x01,0x01,0x7F,0x21,0x11,0x00,0xFE,0x44,0x24,0x00,0x7E,0x88,0x84,0xE2,0x00,/*"锟",1*/
};


u8 HQL[] = {
0x10,0x10,0x12,0xD2,0x52,0x5F,0x52,0xF2,0x52,0x5F,0x52,0xD2,0x12,0x10,0x10,0x00,
0x00,0x00,0x00,0x9F,0x52,0x32,0x12,0x1F,0x12,0x32,0x52,0x9F,0x00,0x00,0x00,0x00,/*"黄",0*/

0x08,0x08,0xE8,0x29,0x2E,0x28,0xE8,0x08,0x08,0xC8,0x0C,0x0B,0xE8,0x08,0x08,0x00,
0x00,0x00,0xFF,0x09,0x49,0x89,0x7F,0x00,0x00,0x0F,0x40,0x80,0x7F,0x00,0x00,0x00,/*"前",1*/

0x10,0x10,0x10,0x10,0x10,0xFF,0x10,0x10,0xF0,0x10,0x11,0x16,0xD0,0x10,0x10,0x00,
0x80,0x40,0x20,0x18,0x06,0x41,0x20,0x10,0x3F,0x44,0x42,0x41,0x40,0x40,0x78,0x00,/*"龙",2*/

};


u8 KK[] = {
   0x20,0x10,0x2C,0xE7,0x24,0x24,0x00,0xFE,0x92,0x92,0x92,0x92,0x92,0xFE,0x00,0x00,
   0x01,0x01,0x01,0x7F,0x21,0x11,0x00,0xFE,0x44,0x24,0x00,0x7E,0x88,0x84,0xE2,0x00,/*"锟",0*/
/* (16 X 16 , 宋体 )*/

   0x20,0x10,0x2C,0xE7,0x24,0x24,0x00,0xFE,0x92,0x92,0x92,0x92,0x92,0xFE,0x00,0x00,
   0x01,0x01,0x01,0x7F,0x21,0x11,0x00,0xFE,0x44,0x24,0x00,0x7E,0x88,0x84,0xE2,0x00,/*"锟",1*/
/* (16 X 16 , 宋体 )*/

};

u8 LL[] = {
   0x10,0x10,0x10,0x10,0x10,0xFF,0x10,0x10,0xF0,0x10,0x11,0x16,0xD0,0x10,0x10,0x00,
   0x80,0x40,0x20,0x18,0x06,0x41,0x20,0x10,0x3F,0x44,0x42,0x41,0x40,0x40,0x78,0x00,/*"龙",0*/
/* (16 X 16 , 宋体 )*/

   0x10,0x10,0x10,0x10,0x10,0xFF,0x10,0x10,0xF0,0x10,0x11,0x16,0xD0,0x10,0x10,0x00,
   0x80,0x40,0x20,0x18,0x06,0x41,0x20,0x10,0x3F,0x44,0x42,0x41,0x40,0x40,0x78,0x00,/*"龙",1*/
/* (16 X 16 , 宋体 )*/

};

u8 ZS[] = {
   0x02,0xE2,0x22,0x22,0x3E,0x80,0x80,0xFF,0x80,0xA0,0x90,0x88,0x86,0x80,0x80,0x00,
   0x00,0x43,0x82,0x42,0x3E,0x00,0x00,0xFF,0x40,0x21,0x06,0x08,0x10,0x20,0x40,0x00,/*"张",0*/
/* (16 X 16 , 宋体 )*/

   0x00,0x04,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x04,0x00,0x00,
   0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,/*"三",1*/
/* (16 X 16 , 宋体 )*/

};


u8 SH[] = {
0x90,0x8C,0x84,0x84,0x84,0x84,0x85,0x86,0x84,0xF4,0x84,0x84,0x84,0x94,0x8C,0x00,
0x00,0x00,0x00,0x04,0x18,0x00,0x00,0x40,0x80,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,/*"守",0*/

0x10,0x10,0x10,0xFF,0x10,0x90,0x00,0xF8,0x88,0x89,0x8E,0x88,0x88,0x88,0xF8,0x00,
0x04,0x44,0x82,0x7F,0x81,0x40,0x30,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,/*"护",1*/

};

u8 YBZ[] = {
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"一",0*/

0x00,0x22,0x2A,0x2A,0x2A,0x7F,0xC0,0x00,0x00,0x7F,0x2A,0x2A,0x2A,0x22,0x00,0x00,
0x20,0x20,0x21,0x29,0x2D,0x2B,0x29,0xFF,0x29,0x29,0x29,0x29,0x21,0x20,0x20,0x00,/*"辈",1*/

0x80,0x82,0x82,0x82,0x82,0x82,0x82,0xE2,0xA2,0x92,0x8A,0x86,0x82,0x80,0x80,0x00,
0x00,0x00,0x00,0x00,0x00,0x40,0x80,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"子",2*/

};


u8 Connection[] = {
   0x10,0x28,0x24,0xE3,0x24,0x28,0x50,0x42,0x42,0x4A,0xD2,0x6A,0x46,0x40,0xC0,0x00,
   0x01,0xF9,0x49,0x4F,0x49,0xF9,0x01,0x00,0x40,0x80,0x7F,0x00,0x00,0x01,0x00,0x00,/*"舒",0*/
/* (16 X 16 , 宋体 )*/

   0x20,0x10,0x2C,0xE7,0x24,0x24,0x00,0xFE,0x92,0x92,0x92,0x92,0x92,0xFE,0x00,0x00,
   0x01,0x01,0x01,0x7F,0x21,0x11,0x00,0xFE,0x44,0x24,0x00,0x7E,0x88,0x84,0xE2,0x00,/*"锟",1*/
/* (16 X 16 , 宋体 )*/

   0x00,0xE0,0xF8,0x1C,0x04,0x06,0x02,0x02,0x02,0x06,0x04,0x1C,0xF8,0xE0,0x00,0x00,
   0x00,0x03,0x0F,0x1C,0x10,0x30,0x20,0x20,0x20,0x30,0x10,0x1C,0x0F,0x03,0x00,0x00,/*"○",2*/
/* (16 X 16 , 宋体 )*/

   0x10,0x10,0x12,0xD2,0x52,0x5F,0x52,0xF2,0x52,0x5F,0x52,0xD2,0x12,0x10,0x10,0x00,
   0x00,0x00,0x00,0x9F,0x52,0x32,0x12,0x1F,0x12,0x32,0x52,0x9F,0x00,0x00,0x00,0x00,/*"黄",3*/
/* (16 X 16 , 宋体 )*/

   0x08,0x08,0xE8,0x29,0x2E,0x28,0xE8,0x08,0x08,0xC8,0x0C,0x0B,0xE8,0x08,0x08,0x00,
   0x00,0x00,0xFF,0x09,0x49,0x89,0x7F,0x00,0x00,0x0F,0x40,0x80,0x7F,0x00,0x00,0x00,/*"前",4*/
/* (16 X 16 , 宋体 )*/

   0x10,0x10,0x10,0x10,0x10,0xFF,0x10,0x10,0xF0,0x10,0x11,0x16,0xD0,0x10,0x10,0x00,
   0x80,0x40,0x20,0x18,0x06,0x41,0x20,0x10,0x3F,0x44,0x42,0x41,0x40,0x40,0x78,0x00,/*"龙",5*/
/* (16 X 16 , 宋体 )*/

};
#endif


