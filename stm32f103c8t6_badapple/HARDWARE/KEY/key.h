#ifndef __KEY_H
#define __KEY_H
#define key0 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define key1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)
void KEY0_Init(void);
void KEY1_Init(void);

#endif
