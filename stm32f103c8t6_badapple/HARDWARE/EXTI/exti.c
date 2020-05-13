#include "exti.h"
#include "stm32f10x.h"
#include "delay.h"
#include "key.h"
#include "led.h"
#include "beep.h"
void KEY0_Exti_Init()
{
	EXTI_InitTypeDef EXTI_InitStructure;
	//GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_AFIO,ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	/*//按键使能
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);*/
	KEY0_Init();
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	//映射中断线
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//下降沿触发
	
	EXTI_Init(&EXTI_InitStructure);
	//中断分组
	NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	
	NVIC_Init(&NVIC_InitStructure);

}


void EXTI0_IRQHandler(void)
{
	delay_ms(10);
	if(key0 == 0)
	
	{
	beepon();
		delay_ms (3000);
	}
	EXTI_ClearITPendingBit(EXTI_Line0);
}

void KEY1_Exti_Init()
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//初始化IOkou为输入
	KEY1_Init();
	
	//开启复用时钟
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	//设置IO口与中断线的映射关系
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);
	
	//初始化中断，设置触发条件等
	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//下降沿触发
	
	EXTI_Init(&EXTI_InitStructure);
	
	//配置中断分组
	NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	
	NVIC_Init(&NVIC_InitStructure);
}
void EXTI1_IRQHandler(void)
{
	delay_ms(10);
	//if(EXTI_GetITStatus(EXTI_Line1)!=RESET)
	if(key1 == 0)
	//while(1)
	{
			ledon_fast(4);
	}
	EXTI_ClearITPendingBit(EXTI_Line1);
}
