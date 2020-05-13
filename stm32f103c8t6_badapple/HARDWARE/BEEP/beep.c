#include "beep.h"
#include "sys.h"
#include "delay.h"
void BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
}
void beepon()
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
}

void beepoff()
{
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
}
void beepon_times(u8 times)
{
	while(times>0)
	{
		beepon();
		delay_ms(200);
		beepoff();
		delay_ms(800);
		times-=1;
	}
}
