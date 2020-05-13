#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "oled_iic.h"
//#include "stdio.h"
extern unsigned char BMP2[256];

 int main(void)
 {	
	 u16 i=0;
	 //u16 len=10;
	 	 
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	 delay_init();
	 OLED_Init();
	 USART1_Init(921600);

	while(1)
	{

		//OLED_ShowStr(10,2,(unsigned char*)"hello world",1);
		/*if(rx_flag)
		{
		  len = number;
			printf("发送的消息有%d个，如下\n",len);
			for(i=0;i<number;i++)
			{
				USART_SendData(USART1,BMP2[i]);
				//printf("%c",USART_RX_BUF[i]);
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
			}
			printf("\n");
			printf("消息如上");
			rx_flag=0;
			number = 0;
			for(i=0;i<256;i++)
			BMP2[i]= 0;
		}*/
		
		if(rx_flag)
		{
			OLED_DrawBMP(0,0,84,8,(unsigned char*)BMP2);
			rx_flag=0;
			number = 0;
		}
		
		//OLED_DrawBMP(0,0,16,2,(unsigned char*)BMP2);
	}
}	
