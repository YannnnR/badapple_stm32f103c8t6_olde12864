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
	
	/*//����ʹ��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);*/
	KEY0_Init();
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	//ӳ���ж���
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//�½��ش���
	
	EXTI_Init(&EXTI_InitStructure);
	//�жϷ���
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
	//��ʼ��IOkouΪ����
	KEY1_Init();
	
	//��������ʱ��
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	//����IO�����ж��ߵ�ӳ���ϵ
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);
	
	//��ʼ���жϣ����ô���������
	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//�½��ش���
	
	EXTI_Init(&EXTI_InitStructure);
	
	//�����жϷ���
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
