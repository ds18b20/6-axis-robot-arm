/*********************************************************************************
 * 文件名  ：pwm_output.c
 * 硬件连接：---------------------
 *          |  PA.06: (TIM3_CH1)  |
 *          |  PA.07: (TIM3_CH2)  |
 *      	|  PB.00: (TIM3_CH3)  | 
 *    		|  PB.01: (TIM3_CH4)  |
 *           ---------------------    			
**********************************************************************************/
#include "pwm_output.h"
#include "delay.h"

#define		  	  MAX	  2150
#define		  	  MIN	  750
#define		TIME_STEP	  25

/* PWM信号电平 初始 跳变值 */
extern unsigned int CCR1_Val;			//MIN
extern unsigned int CCR2_Val;			//MAX
extern unsigned int CCR3_Val;			//MID
extern unsigned int CCR4_Val;			//Other
extern unsigned int CCR5_Val;			//MID
extern unsigned int CCR6_Val;			//Other

/* 全局结构体 */
TIM_OCInitTypeDef  TIM_OCInitStructure;

/*
 * 函数名：TIM3+LED_GPIO_Config
 * 描述  ：配置TIM3复用输出PWM时用到的I/O + 配置LED输出PWM时用到的I/O 
 */
void GPIO_Config(void) 
{
	GPIO_InitTypeDef	GPIO_InitStructure;

	/*RCC_APB1 TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4, ENABLE); 
	
	/*RCC_APB2 GPIOA and GPIOB clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE); 
	
	/*GPIOA Configuration: TIM3 channel 1 and 2 as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_6 | GPIO_Pin_7;	// PA6-TIM3-Channel1 PA7-TIM3-Channel2
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;		    // 复用推挽输出
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/*GPIOB Configuration: TIM3 channel 3 and 4 as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_6 | GPIO_Pin_7; 	// PB0-TIM3-Channel3 PB1-TIM3-Channel4 PB6-TIM4-Channel1 PB7-TIM4-Channel2
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;		    // 复用推挽输出
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;		
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/*GPIOC Configuration: LED push-pull */
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_6 | GPIO_Pin_7;	// PC6-LED D1  PC7-LED D2
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_Out_PP;			// 复用推挽输出
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/* PWM1 Mode configuration: Channel1 */
void Channel_1_Config(void)
{
	TIM_OCInitStructure.TIM_OCMode 		= TIM_OCMode_PWM1;	    		//配置为PWM模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse 		= CCR1_Val;	   					//设置跳变值，当计数器计数到这个值时，电平发生跳变
	TIM_OCInitStructure.TIM_OCPolarity 	= TIM_OCPolarity_High;  		//当定时器计数值小于CCR1_Val时为高电平
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);	 						//TIM_OC1Init使能通道1
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
}
/* PWM1 Mode configuration: Channel2 */
void Channel_2_Config(void)
{
	TIM_OCInitStructure.TIM_OCMode 		= TIM_OCMode_PWM1;	    		//配置为PWM模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse 		= CCR2_Val;	   					//设置跳变值，当计数器计数到这个值时，电平发生跳变
	TIM_OCInitStructure.TIM_OCPolarity 	= TIM_OCPolarity_High;  		//当定时器计数值小于CCR2_Val时为高电平	
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);	 						//TIM_OC2Init使能通道2
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
}
/* PWM1 Mode configuration: Channel3 */
void Channel_3_Config(void)
{
	TIM_OCInitStructure.TIM_OCMode 		= TIM_OCMode_PWM1;	    		//配置为PWM模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse 		= CCR3_Val;	   					//设置跳变值，当计数器计数到这个值时，电平发生跳变
	TIM_OCInitStructure.TIM_OCPolarity 	= TIM_OCPolarity_High;  		//当定时器计数值小于CCR3_Val时为高电平
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);	 						//TIM_OC3Init使能通道3
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
}
/* PWM1 Mode configuration: Channel4 */
void Channel_4_Config(void)
{
	TIM_OCInitStructure.TIM_OCMode 		= TIM_OCMode_PWM1;	    		//配置为PWM模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse 		= CCR4_Val;	   					//设置跳变值，当计数器计数到这个值时，电平发生跳变
	TIM_OCInitStructure.TIM_OCPolarity 	= TIM_OCPolarity_High;  		//当定时器计数值小于CCR4_Val时为高电平	
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);	 						//TIM_OC4Init使能通道4	
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
}

/* PWM1 Mode configuration: Channel5 */
void Channel_5_Config(void)
{
	TIM_OCInitStructure.TIM_OCMode 		= TIM_OCMode_PWM1;	    		//配置为PWM模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse 		= CCR5_Val;	   					//设置跳变值，当计数器计数到这个值时，电平发生跳变
	TIM_OCInitStructure.TIM_OCPolarity 	= TIM_OCPolarity_High;  		//当定时器计数值小于CCR1_Val时为高电平
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);	 						//TIM_OC1Init使能通道1
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
}

/* PWM1 Mode configuration: Channel6 */
void Channel_6_Config(void)
{
	TIM_OCInitStructure.TIM_OCMode 		= TIM_OCMode_PWM1;	    		//配置为PWM模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse 		= CCR6_Val;	   					//设置跳变值，当计数器计数到这个值时，电平发生跳变
	TIM_OCInitStructure.TIM_OCPolarity 	= TIM_OCPolarity_High;  		//当定时器计数值小于CCR1_Val时为高电平
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);	 						//TIM_OC2Init使能通道1
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
}

/*
 * 函数名：TIM3_Mode_Config
 * 描述  ：配置TIM3输出的PWM信号的模式，如周期、极性、占空比
 */
static void TIM3_4_Base_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	/* Time base configuration */		 
	TIM_TimeBaseStructure.TIM_Period 		= 19999;       				//当定时器从0计数到19999，即为20000次，为一个定时周期=20ms
	TIM_TimeBaseStructure.TIM_Prescaler 	= 72-1;	    				//设置预分频：不预分频，即为36MHz 72分频=1/2M 由于72不等于1 故v=1M
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;						//设置时钟分频系数：不分频
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up;  		//向上计数模式
	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);		
}

void TIM3_4_PWM_Init(void)
{	
	/* 引脚配置 */
	GPIO_Config();

	/* TIM3时钟+PWM周期 */
	TIM3_4_Base_Config();
	
	/*Channel_*_Config*/
	Channel_1_Config();
	Channel_2_Config();
	Channel_3_Config();
	Channel_4_Config();
	Channel_5_Config();
	Channel_6_Config();

	TIM_ARRPreloadConfig(TIM3, ENABLE);		//使能TIM3重载寄存器ARR	
	TIM_Cmd(TIM3, ENABLE);					//使能定时器3

	TIM_ARRPreloadConfig(TIM4, ENABLE);		//使能TIM4重载寄存器ARR	
	TIM_Cmd(TIM4, ENABLE);					//使能定时器4

	Delay_ms(500);		  					//注意SysTick	一次最多1864 ms		初始动作时间
}
/******************** (C) COPYRIGHT 2012 仿生实验室 *********************/
