#ifndef __OLED_I2C_H
#define __OLED_I2C_H

#include "stm32f10x.h"
#define OLED_ADDRESS    0x78 //ͨ������0R����,������0x78��0x7A������ַ -- Ĭ��0x78

/* STM32 I2C ����ģʽ */
#define I2C_Speed              400000

/*I2C�ӿ�*/
#define OLED_I2C                          I2C1
#define OLED_I2C_CLK                      RCC_APB1Periph_I2C1
#define OLED_I2C_CLK_INIT                 RCC_APB1PeriphClockCmd

#define OLED_I2C_SCL_PIN                  GPIO_Pin_6                 
#define OLED_I2C_SCL_GPIO_PORT            GPIOB                       
#define OLED_I2C_SCL_GPIO_CLK             RCC_APB2Periph_GPIOB
#define OLED_I2C_SCL_SOURCE               GPIO_PinSource6
#define OLED_I2C_SCL_AF                   GPIO_AF_I2C1

#define OLED_I2C_SDA_PIN                  GPIO_Pin_7                  
#define OLED_I2C_SDA_GPIO_PORT            GPIOB                       
#define OLED_I2C_SDA_GPIO_CLK             RCC_APB2Periph_GPIOB
#define OLED_I2C_SDA_SOURCE               GPIO_PinSource7
#define OLED_I2C_SDA_AF                   GPIO_AF_I2C1

//I2C��ʼ������
void I2C_Configuration(void);
void I2C_WriteByte(uint8_t addr,uint8_t data);
void WriteCmd(unsigned char I2C_Command);
void WriteDat(unsigned char I2C_Data);

void OLED_Init(void);
void OLED_SetPos(unsigned char x, unsigned char y);//���ù��λ��
void OLED_Fill(unsigned char fill_Data);//���������Ļ
void OLED_CLS(void);//����
void OLED_ON(void);//��OLED�������л���
void OLED_OFF(void);//��OLED���� -- ����ģʽ��,OLED���Ĳ���10uA

 /**
  * @brief  OLED_ShowStr����ʾcodetab.h�е�ASCII�ַ�,��6*8��8*16��ѡ��
  * @param  x,y : ��ʼ������(x:0~127, y:0~7);
    *                   ch[] :- Ҫ��ʾ���ַ���; 
    *                   TextSize : �ַ���С(1:6*8 ; 2:8*16)
    * @retval ��
  */
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);

 /**
  * @brief  OLED_ShowCN����ʾcodetab.h�еĺ���,16*16����
  * @param  x,y: ��ʼ������(x:0~127, y:0~7); 
    *                   N:������codetab.h�е�����
    * @retval ��
  */
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);

 /**
  * @brief  OLED_DrawBMP����ʾBMPλͼ
  * @param  x0,y0 :��ʼ������(x0:0~127, y0:0~7);
    *                   x1,y1 : ���Խ���(������)������(x1:1~128,y1:1~8)
    * @retval ��
  */
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);

#endif

