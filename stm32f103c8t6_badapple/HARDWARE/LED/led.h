#ifndef __LED_H
#define __LED_H	 
#include "stm32f10x.h"

void LED_Init(void);//≥ı ºªØ
void ledon(void);
void ledoff(void); 	
void ledon_fast(u16);
void ledon_slow(u16);
#endif

