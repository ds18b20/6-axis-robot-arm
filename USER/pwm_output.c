/*********************************************************************************
 * �ļ���  ��pwm_output.c
 * Ӳ�����ӣ�---------------------
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

/* PWM�źŵ�ƽ ��ʼ ����ֵ */
extern unsigned int CCR1_Val;			//MIN
extern unsigned int CCR2_Val;			//MAX
extern unsigned int CCR3_Val;			//MID
extern unsigned int CCR4_Val;			//Other
extern unsigned int CCR5_Val;			//MID
extern unsigned int CCR6_Val;			//Other

/* ȫ�ֽṹ�� */
TIM_OCInitTypeDef  TIM_OCInitStructure;

/*
 * ��������TIM3+LED_GPIO_Config
 * ����  ������TIM3�������PWMʱ�õ���I/O + ����LED���PWMʱ�õ���I/O 
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
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;		    // �����������
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/*GPIOB Configuration: TIM3 channel 3 and 4 as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_6 | GPIO_Pin_7; 	// PB0-TIM3-Channel3 PB1-TIM3-Channel4 PB6-TIM4-Channel1 PB7-TIM4-Channel2
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;		    // �����������
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;		
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/*GPIOC Configuration: LED push-pull */
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_6 | GPIO_Pin_7;	// PC6-LED D1  PC7-LED D2
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_Out_PP;			// �����������
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/* PWM1 Mode configuration: Channel1 */
void Channel_1_Config(void)
{
	TIM_OCInitStructure.TIM_OCMode 		= TIM_OCMode_PWM1;	    		//����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse 		= CCR1_Val;	   					//��������ֵ�������������������ֵʱ����ƽ��������
	TIM_OCInitStructure.TIM_OCPolarity 	= TIM_OCPolarity_High;  		//����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);	 						//TIM_OC1Initʹ��ͨ��1
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
}
/* PWM1 Mode configuration: Channel2 */
void Channel_2_Config(void)
{
	TIM_OCInitStructure.TIM_OCMode 		= TIM_OCMode_PWM1;	    		//����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse 		= CCR2_Val;	   					//��������ֵ�������������������ֵʱ����ƽ��������
	TIM_OCInitStructure.TIM_OCPolarity 	= TIM_OCPolarity_High;  		//����ʱ������ֵС��CCR2_ValʱΪ�ߵ�ƽ	
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);	 						//TIM_OC2Initʹ��ͨ��2
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
}
/* PWM1 Mode configuration: Channel3 */
void Channel_3_Config(void)
{
	TIM_OCInitStructure.TIM_OCMode 		= TIM_OCMode_PWM1;	    		//����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse 		= CCR3_Val;	   					//��������ֵ�������������������ֵʱ����ƽ��������
	TIM_OCInitStructure.TIM_OCPolarity 	= TIM_OCPolarity_High;  		//����ʱ������ֵС��CCR3_ValʱΪ�ߵ�ƽ
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);	 						//TIM_OC3Initʹ��ͨ��3
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
}
/* PWM1 Mode configuration: Channel4 */
void Channel_4_Config(void)
{
	TIM_OCInitStructure.TIM_OCMode 		= TIM_OCMode_PWM1;	    		//����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse 		= CCR4_Val;	   					//��������ֵ�������������������ֵʱ����ƽ��������
	TIM_OCInitStructure.TIM_OCPolarity 	= TIM_OCPolarity_High;  		//����ʱ������ֵС��CCR4_ValʱΪ�ߵ�ƽ	
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);	 						//TIM_OC4Initʹ��ͨ��4	
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
}

/* PWM1 Mode configuration: Channel5 */
void Channel_5_Config(void)
{
	TIM_OCInitStructure.TIM_OCMode 		= TIM_OCMode_PWM1;	    		//����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse 		= CCR5_Val;	   					//��������ֵ�������������������ֵʱ����ƽ��������
	TIM_OCInitStructure.TIM_OCPolarity 	= TIM_OCPolarity_High;  		//����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);	 						//TIM_OC1Initʹ��ͨ��1
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
}

/* PWM1 Mode configuration: Channel6 */
void Channel_6_Config(void)
{
	TIM_OCInitStructure.TIM_OCMode 		= TIM_OCMode_PWM1;	    		//����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse 		= CCR6_Val;	   					//��������ֵ�������������������ֵʱ����ƽ��������
	TIM_OCInitStructure.TIM_OCPolarity 	= TIM_OCPolarity_High;  		//����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);	 						//TIM_OC2Initʹ��ͨ��1
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
}

/*
 * ��������TIM3_Mode_Config
 * ����  ������TIM3�����PWM�źŵ�ģʽ�������ڡ����ԡ�ռ�ձ�
 */
static void TIM3_4_Base_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	/* Time base configuration */		 
	TIM_TimeBaseStructure.TIM_Period 		= 19999;       				//����ʱ����0������19999����Ϊ20000�Σ�Ϊһ����ʱ����=20ms
	TIM_TimeBaseStructure.TIM_Prescaler 	= 72-1;	    				//����Ԥ��Ƶ����Ԥ��Ƶ����Ϊ36MHz 72��Ƶ=1/2M ����72������1 ��v=1M
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;						//����ʱ�ӷ�Ƶϵ��������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up;  		//���ϼ���ģʽ
	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);		
}

void TIM3_4_PWM_Init(void)
{	
	/* �������� */
	GPIO_Config();

	/* TIM3ʱ��+PWM���� */
	TIM3_4_Base_Config();
	
	/*Channel_*_Config*/
	Channel_1_Config();
	Channel_2_Config();
	Channel_3_Config();
	Channel_4_Config();
	Channel_5_Config();
	Channel_6_Config();

	TIM_ARRPreloadConfig(TIM3, ENABLE);		//ʹ��TIM3���ؼĴ���ARR	
	TIM_Cmd(TIM3, ENABLE);					//ʹ�ܶ�ʱ��3

	TIM_ARRPreloadConfig(TIM4, ENABLE);		//ʹ��TIM4���ؼĴ���ARR	
	TIM_Cmd(TIM4, ENABLE);					//ʹ�ܶ�ʱ��4

	Delay_ms(500);		  					//ע��SysTick	һ�����1864 ms		��ʼ����ʱ��
}
/******************** (C) COPYRIGHT 2012 ����ʵ���� *********************/
