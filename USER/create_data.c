#include <math.h>

#define pi 3.141592653
#define CNT 30				 //最大 迭代次数

extern double out1;
extern double out2;
extern double temp1;
extern double temp2;
extern double theta1;
extern double theta2;

/* 计算角度 */
void Create_Data(double length , double height)
{
	double f1,f2;
	double det;				//雅克比矩阵 行列式值
	double dth1,dth2;
	double epsilon=0.0005;
	double D=1;
	unsigned int cnt=0;

	theta1=temp1*pi/180;		//初值 角度 -> 弧度
	theta2=temp2*pi/180;		//初值 角度 -> 弧度

	f1=105*cos(theta1)+92*cos(theta2)+165-length;
	f2=105*sin(theta1)+92*sin(theta2)-height;

	while (D>epsilon&&cnt<CNT)
	{
		cnt++;				//迭代次数
		det=9660*sin(theta2-theta1);
		dth1=-92/det*(cos(theta2)*f1+sin(theta2)*f2);
		dth2=105/det*(cos(theta1)*f1+sin(theta1)*f2);
		theta1=theta1+dth1;
		theta2=theta2+dth2;
		f1=105*cos(theta1)+92*cos(theta2)+165-length;
		f2=105*sin(theta1)+92*sin(theta2)-height;
        D=sqrt(f1*f1+f2*f2);
	}
	out1=theta1/pi*180;
	out2=theta2/pi*180;

	while (out1<0)
	{
	out1=out1+360;
	}
	
	while (out1>360)
	{
	out1=out1-360;
	}
	
	while (out2<0)
	{
	out2=out2+360;
	}
	
	while (out2>360)
	{
	out2=out2-360;
	}
}

/*
		
				L3=170//165
			|_________
		   /|)90
	L2=92 / |
		 /  |
		/_)theta2
		|
		|
		|
L1=105  |
		|
		|)theta1

*/
