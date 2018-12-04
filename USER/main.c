/******************** (C) COPYRIGHT 2012 仿生实验室 ********************
 * 文件名  ：main.c
 * 描述    ：定时器TIM3产生四路PWM波输出。
 *           - PA.06: (TIM3_CH1)
 *           - PA.07: (TIM3_CH2)
 *           - PB.00: (TIM3_CH3) 关节3
 *           - PB.01: (TIM3_CH4) 关节4
 *           
 *       目前可以计算出3、4的PWM值了！！！    
 *       更改的时候注意.c 和.h都要改！！！  
**********************************************************************************/
#include "stm32f10x.h"
#include "pwm_output.h"
#include "create_data.h"
#include "delay.h"

double	theta1,theta2;
double	out1,out2;
double	temp1=130;
double	temp2=18;
unsigned char i;
float L_C[23]=	{176.49 ,171.25 ,165.98 ,161.31 ,158.24 ,
				158.00 ,160.35 ,164.33 ,168.87 ,173.48 ,
				178.19 ,182.90 ,187.67 ,192.49 ,197.24 ,
				202.04 ,207.99 ,212.54 ,216.81 ,217.90 ,
				212.66 ,202.02 ,194.69  };						
float J_C[23]=	{40.34 ,40.19 ,40.10 ,39.47 ,38.24 ,
				36.61 ,35.11 ,34.20 ,33.90 ,33.99 ,
				34.11 ,34.19 ,34.35 ,34.64 ,35.06 ,
				35.53 ,35.78 ,36.20 ,36.53 ,36.95 ,
				37.70 ,38.41 ,38.65};

float L_X[44]=	{222.79 ,220.84 ,219.66 ,220.54 ,223.56 ,
				226.78 ,229.48 ,231.94 ,236.65 ,240.83 ,
				245.10 ,249.38 ,253.67 ,257.85 ,262.00 ,
				266.32 ,262.00 ,257.85 ,253.67 ,249.38 ,
				245.10 ,240.83 ,234.06 ,231.95 ,228.50 ,
				223.79 ,219.45 ,215.92 ,212.00 ,207.66 ,
				211.90 ,216.22 ,220.55 ,224.88 ,229.18 ,
				232.66 ,234.78 ,237.61 ,243.79 ,248.24 ,
				251.62 ,255.78 ,258.24 ,260.84 ,};
float J_X[44]=	{49.76 ,49.16 ,48.72 ,47.87 ,46.84 ,
				46.21 ,45.82 ,45.37 ,44.93 ,44.87 ,
				45.06 ,45.33 ,45.60 ,45.90 ,46.20 ,
				46.35 ,46.20 ,45.90 ,45.60 ,45.33 ,
				45.06 ,44.87 ,44.50 ,44.32 ,44.16 ,
				44.02 ,43.78 ,43.38 ,43.04 ,42.70 ,
				43.06 ,43.30 ,43.51 ,43.75 ,43.99 ,
				44.15 ,44.33 ,44.34 ,44.33 ,43.88 ,
				43.36 ,42.71 ,42.32 ,41.64 };


unsigned int CCR1_Val = 2000;			//MIN
unsigned int CCR2_Val = 2300;			//MAX
unsigned int CCR3_Val = 2300;			//MID
unsigned int CCR4_Val = 1250;			//Other
unsigned int CCR5_Val = 1250;			//MID
unsigned int CCR6_Val = 1850;			//Other

/* 
 ******主函数******
*/
int main(void)
{
	SystemInit();	 			/* 配置系统时钟为72M */
	TIM3_4_PWM_Init(); 			/* 各种初始化：GPIO+定时器基本设置+各通道设置 */

/*		到位		*/
	Create_Data(180,140);	 	/* 计算角度	void Create_Data(double length , double height)	 */
	temp1=out1;
	temp2=out2;
	
	CCR2_Val=-10.556*out1+2300;			//角度->PWM2 换算公式	CCR2_Val=10.556*out1+400;
	Channel_2_Config();					//Channel_3_Config();!!!错误
	
	CCR3_Val=10.833*(180-out1+out2)+450;//角度->PWM3 换算公式
	Channel_3_Config();
		
	CCR4_Val=10.444*(180-out2)-400;	//角度->PWM4 换算公式//或者是-455	     //	CCR4_Val=10.222*(180-out2+90)-800 ！！！错误  out2是补偿后的out2了	
	Channel_4_Config();

	Delay_ms(1000);					//Delay
	Delay_ms(1000);					//Delay
	Delay_ms(1000);					//Delay
	Delay_ms(1000);					//Delay

/*		写C		*/
	for (i=0;i<23;i++)
	{
		CCR1_Val=2300-38*J_C[i];		//10.69	
		Channel_1_Config();

		Create_Data(L_C[i],140);	 	/* 计算角度	void Create_Data(double length , double height)	 */
		temp1=out1;
		temp2=out2;

		CCR2_Val=-10.556*out1+2300;			//角度->PWM2 换算公式	CCR2_Val=10.556*out1+400;
		Channel_2_Config();					//Channel_3_Config();!!!错误

		CCR3_Val=10.833*(180-out1+out2)+450;			//角度->PWM3 换算公式
		Channel_3_Config();
			
		CCR4_Val=10.444*(180-out2)-400;	//角度->PWM4 换算公式//或者是-455	     //	CCR4_Val=10.222*(180-out2+90)-800 ！！！错误  out2是补偿后的out2了	
		Channel_4_Config();
		
		Delay_ms(800);					//Delay
		Delay_ms(1000);					//Delay
//		Delay_ms(1000);					//Delay
	}

/*		提笔		*/
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay

		CCR3_Val+=100;			//角度->PWM3 换算公式
		Channel_3_Config();
			
		CCR4_Val-=75;			//角度->PWM4 换算公式//或者是-455	     //	CCR4_Val=10.222*(180-out2+90)-800 ！！！错误  out2是补偿后的out2了	
		Channel_4_Config();

		CCR1_Val=780;			
		Channel_1_Config();

		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
/*		过渡		*/
		Create_Data(198,140);	 	/* 计算角度	void Create_Data(double length , double height)	 */
		temp1=out1;
		temp2=out2;

		CCR2_Val=-10.556*out1+2300;			//角度->PWM2 换算公式	CCR2_Val=10.556*out1+400;
		Channel_2_Config();					//Channel_3_Config();!!!错误

		CCR3_Val=10.833*(180-out1+out2)+450;			//角度->PWM3 换算公式
		Channel_3_Config();
			
		CCR4_Val=10.444*(180-out2)-400;	//角度->PWM4 换算公式//或者是-455	     //	CCR4_Val=10.222*(180-out2+90)-800 ！！！错误  out2是补偿后的out2了	
		Channel_4_Config();
		
		Delay_ms(800);					//Delay
		Delay_ms(1000);					//Delay

		Create_Data(210,140);	 	/* 计算角度	void Create_Data(double length , double height)	 */
		temp1=out1;
		temp2=out2;

		CCR2_Val=-10.556*out1+2300;			//角度->PWM2 换算公式	CCR2_Val=10.556*out1+400;
		Channel_2_Config();					//Channel_3_Config();!!!错误

		CCR3_Val=10.833*(180-out1+out2)+450;			//角度->PWM3 换算公式
		Channel_3_Config();
			
		CCR4_Val=10.444*(180-out2)-400;	//角度->PWM4 换算公式//或者是-455	     //	CCR4_Val=10.222*(180-out2+90)-800 ！！！错误  out2是补偿后的out2了	
		Channel_4_Config();
		
		Delay_ms(800);					//Delay
		Delay_ms(1000);					//Delay

/*		写X		*/
	for (i=0;i<44;i++)
	{
		CCR1_Val=2300-40*J_X[i];			
		Channel_1_Config();

		Create_Data(L_X[i],140);	 	/* 计算角度	void Create_Data(double length , double height)	 */
		temp1=out1;
		temp2=out2;

		CCR2_Val=-10.556*out1+2300;			//角度->PWM2 换算公式	CCR2_Val=10.556*out1+400;
		Channel_2_Config();					//Channel_3_Config();!!!错误

		CCR3_Val=10.833*(180-out1+out2)+450;			//角度->PWM3 换算公式
		Channel_3_Config();
			
		CCR4_Val=10.444*(180-out2)-400;	//角度->PWM4 换算公式//或者是-455	     //	CCR4_Val=10.222*(180-out2+90)-800 ！！！错误  out2是补偿后的out2了	
		Channel_4_Config();
		
		Delay_ms(800);					//Delay
		Delay_ms(1000);					//Delay

	}

/*		起笔		*/
//	CCR1_Val=1250;			//
//	Channel_1_Config();
//
//	for (i=0;i<10;i++)
//	{
//		CCR1_Val-=20;			//
//		Channel_1_Config();
//
//		Delay_ms(1000);					//Delay
//		Delay_ms(1000);					//Delay
//	}
//
//	for (i=0;i<20;i++)
//	{
//		Create_Data(L[i],140);	 	/* 计算角度	void Create_Data(double length , double height)	 */
//		temp1=out1;
//		temp2=out2;
//		
//		CCR1_Val-=20;			//
//		Channel_1_Config();
//
//		CCR2_Val=-10.556*out1+2300;			//角度->PWM2 换算公式	CCR2_Val=10.556*out1+400;
//		Channel_2_Config();					//Channel_3_Config();!!!错误
//
//		CCR3_Val=10.833*(180-out1+out2)+450;			//角度->PWM3 换算公式
//		Channel_3_Config();
//			
//		CCR4_Val=10.444*(180-out2)-400;	//角度->PWM4 换算公式//或者是-455	     //	CCR4_Val=10.222*(180-out2+90)-800 ！！！错误  out2是补偿后的out2了	
//		Channel_4_Config();
//		
//		Delay_ms(800);					//Delay
////		Delay_ms(1000);					//Delay
//	}

	while(1)
	{
		GPIO_SetBits(GPIOC , GPIO_Pin_6);
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
	
		GPIO_ResetBits(GPIOC , GPIO_Pin_6);
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
		Delay_ms(1000);					//Delay
	}

}
/******************** (C) COPYRIGHT 2012 仿生实验室 *********************/
