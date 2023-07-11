#include "adjust.h"


double PID_Adjust(double cv, double tv) //PID调节算法
{
	double e = 0;
	double r = 0;
	double kp = 7.3; //比例系数
	double ki = 2.8; //积分系数
	double kd = 3.4; //微分系数
	static double lv1 = 0;  //上一次的量
	static double lv2 = 0;  //上上次量
	static double le1 = 0;  //上一次误差
	static double le2 = 0;  //上上次误差
	e = tv - cv;  //误差计算
	le1 = tv - lv1;  //计算上次误差
	le2 = tv - lv2;  //计算上上次误差
	lv1 = cv;   //记录本次误差
	lv2 = lv1;   //记录上次误差
	r = kp*(e-le1)+ki*e+kd*(e-2*le1+le2);   //计算调节量
    return r;
}
