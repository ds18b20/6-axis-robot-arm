/*********************************************************************************
 * �ļ�����	delay.c
 * ע�⣺	SysTick�ܼĴ�����С���ƣ�һ�����1864 ms
 *        һ��Delay N us
 *        ����Delay N ms  			
**********************************************************************************/
#include "delay.h"

/*Delay N us*/
void  Delay_us(u32 nus)
{
	u32 temp;
	if (SysTick_Config(nus*SystemFrequency / 1000000))
	{/* Capture error */ 
		while (1);
	}
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));	//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       			//�رռ�����
	SysTick->VAL =0X00;       			//��ռ�����	
}

/*Delay N ms*/
void  Delay_ms(u16 nms)		  			//ע��SysTick	һ�����1864 ms
{
	u32 temp;
	if (SysTick_Config(nms*SystemFrequency / 1000))
	{ 
		/* Capture error */ 
		while (1);
	}
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));	//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       			//�رռ�����
	SysTick->VAL =0X00;       			//��ռ�����	
}
/******************** (C) COPYRIGHT 2012 ����ʵ���� *********************/
