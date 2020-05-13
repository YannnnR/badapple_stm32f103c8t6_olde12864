#include "key.h"
#include "stm32f10x.h"

void KEY0_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能 PA 端口时钟
	
	//meky
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //配置 pin10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void KEY1_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能 PB端口时钟
	
	//meky
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //配置 pin10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
