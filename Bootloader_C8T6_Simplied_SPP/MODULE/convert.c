#include "convert.h"


/*****************************************************

���´�������ֵת��Ϊ�ַ����ĳ���
u8* IntToString(long value); �˺�����һ����������ת��Ϊ�ַ���������ֵΪһ���ַ���ָ�롣
u8* FloatToString(double value, u8 precision); �˺�����һ������������ת��Ϊ�ַ���������ֵΪһ���ַ���ָ�롣

*******************************************************/



char* IntToString(long value)        //������ֵת��Ϊ�ַ�������
{
    static char text[15];  
    u8 bits = 0;
    long integer = 0;
    long compare = 1; 
    if(value < 0){
        value = -value;
        text[bits] = '-';
        bits++;
    }
    integer = (long) value;
    do{
        compare *= 10;
    }while(compare <= integer);
    do{                                         
        compare /= 10;
        text[bits] = integer / compare % 10 + '0';
        bits++;
    }while(compare > 1);
    text[bits] = 0;
    return text;
}

char* FloatToString(double value, u8 precision)       //��������ֵת��Ϊ�ַ�������
{
    static char text[15];
    u8 bits = 0;
    long integer = 0;
    long compare = 1;
    long decimalPower = 1;  
    double decimal = 0;
    if(value < 0){
        value = -value;
        text[bits] = '-';
        bits++;
    }
    integer = (long) value;
    decimal = value - integer;
    do{
        compare *= 10;
    }while(compare <= integer);
    do{
        compare /= 10;
        text[bits] = integer / compare % 10 + '0';
        bits++;
    }while(compare > 1);
    if(precision > 0){
        text[bits] = '.';
        do{
            bits++;
            precision--;
            decimalPower *= 10;
            text[bits] = (long) (decimal * decimalPower) % 10 + '0';
        }while(precision);
        text[++bits] = 0;
    }
    else text[bits] = 0;
    return text;
}




