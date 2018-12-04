/*********************************************************************************
 * 文件名：	delay.c
 * 注意：	SysTick受寄存器大小限制，一次最多1864 ms
 *        一、Delay N us
 *        二、Delay N ms  			
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
	while(temp&0x01&&!(temp&(1<<16)));	//等待时间到达   
	SysTick->CTRL=0x00;       			//关闭计数器
	SysTick->VAL =0X00;       			//清空计数器	
}

/*Delay N ms*/
void  Delay_ms(u16 nms)		  			//注意SysTick	一次最多1864 ms
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
	while(temp&0x01&&!(temp&(1<<16)));	//等待时间到达   
	SysTick->CTRL=0x00;       			//关闭计数器
	SysTick->VAL =0X00;       			//清空计数器	
}
/******************** (C) COPYRIGHT 2012 仿生实验室 *********************/
