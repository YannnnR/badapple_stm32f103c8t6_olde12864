#include "key.h"
#include "stm32f10x.h"

void KEY0_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ�� PA �˿�ʱ��
	
	//meky
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //���� pin10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void KEY1_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ�� PB�˿�ʱ��
	
	//meky
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //���� pin10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
