#include "led.h"
#include "stm32f10x.h"
#include "delay.h"

void LED_Init() {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ�� PB �˿�ʱ��
	
	//nled
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; //���� pin10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO ��ת 50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_14);
		
}
void ledon()
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
}
void ledoff()
{
	GPIO_SetBits(GPIOB,GPIO_Pin_14);
}
void ledon_fast(u16 time)
{
	u16 i;
	i=10*time;
	while(i>0)
	{
		ledon();
		delay_ms(100);
		ledoff();
		delay_ms(100);
		i-=2;
	}
}
void ledon_slow(u16 time)
{
	u16 i;
	i=10*time;
	while(i>0)
	{
		ledon();
		delay_ms(1000);
		ledoff();
		delay_ms(1000);
		i-=20;
	}
}
