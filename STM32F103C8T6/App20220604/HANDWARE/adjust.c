#include "adjust.h"


double PID_Adjust(double cv, double tv) //PID�����㷨
{
	double e = 0;
	double r = 0;
	double kp = 7.3; //����ϵ��
	double ki = 2.8; //����ϵ��
	double kd = 3.4; //΢��ϵ��
	static double lv1 = 0;  //��һ�ε���
	static double lv2 = 0;  //���ϴ���
	static double le1 = 0;  //��һ�����
	static double le2 = 0;  //���ϴ����
	e = tv - cv;  //������
	le1 = tv - lv1;  //�����ϴ����
	le2 = tv - lv2;  //�������ϴ����
	lv1 = cv;   //��¼�������
	lv2 = lv1;   //��¼�ϴ����
	r = kp*(e-le1)+ki*e+kd*(e-2*le1+le2);   //���������
    return r;
}
