

#include "oled_iic.h"
#include "codetab.h"//��������
#include "delay.h"




 /**
  * @brief  I2C_Configuration����ʼ��Ӳ��IIC����
  * @param  ��
  * @retval ��
  */
void I2C_Configuration(void)
{
    I2C_InitTypeDef  I2C_InitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure; 

    /*I2C1����ʱ��ʹ�� */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);

    /*I2C1����GPIOʱ��ʹ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	/* I2C_SCL��I2C_SDA*/
	//PB6:SCL PB7:SDA
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;          // ��©���
  GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* I2C ���� */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;    
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;    /* �ߵ�ƽ�����ȶ����͵�ƽ���ݱ仯 SCL ʱ���ߵ�ռ�ձ� */
  I2C_InitStructure.I2C_OwnAddress1 =0x10;    //������I2C��ַ.�������豸���ظ�����
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;  
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; /* I2C��Ѱַģʽ */
  I2C_InitStructure.I2C_ClockSpeed = 400000; //400k                            /* ͨ������ */

  I2C_Init(I2C1, &I2C_InitStructure);                                         /* I2C1 ��ʼ�� */
  I2C_Cmd(I2C1, ENABLE);                                                    /* ʹ�� I2C1 */

}


 /**
  * @brief  I2C_WriteByte����OLED�Ĵ�����ַдһ��byte������
  * @param  addr���Ĵ�����ַ
    *                   data��Ҫд�������
  * @retval ��
  */
void I2C_WriteByte(uint8_t addr,uint8_t data)
{
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY))
		;

    I2C_GenerateSTART(I2C1, ENABLE);//����I2C1
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,��ģʽ*/

    I2C_Send7bitAddress(I2C1, OLED_ADDRESS, I2C_Direction_Transmitter);//������ַ -- Ĭ��0x78
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    I2C_SendData(I2C1, addr  );//�Ĵ�����ַ
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    I2C_SendData(I2C1, data);//��������
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    I2C_GenerateSTOP(I2C1, ENABLE);//�ر�I2C1����
}


 /**
  * @brief  WriteCmd����OLEDд������
  * @param  I2C_Command���������
  * @retval ��
  */
void WriteCmd(unsigned char I2C_Command)//д����
{
    I2C_WriteByte(0x00, I2C_Command);
}


 /**
  * @brief  WriteDat����OLEDд������
  * @param  I2C_Data������
  * @retval ��
  */
void WriteDat(unsigned char I2C_Data)//д����
{
    I2C_WriteByte(0x40, I2C_Data);
}


 /**
  * @brief  OLED_Init����ʼ��OLED
  * @param  ��
  * @retval ��
  */
void OLED_Init(void)
{
    delay_ms(1000);     // 1s,�������ʱ����Ҫ,�ϵ����ʱ��û�д�����������
		I2C_Configuration();
	
    WriteCmd(0xAE); //display off
    WriteCmd(0x20); //Set Memory Addressing Mode    
    WriteCmd(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
    WriteCmd(0xb0); //Set Page Start Address for Page Addressing Mode,0-7
    WriteCmd(0xc8); //Set COM Output Scan Direction
    WriteCmd(0x00); //---set low column address
    WriteCmd(0x10); //---set high column address
    WriteCmd(0x40); //--set start line address
    WriteCmd(0x81); //--set contrast control register
    WriteCmd(0xff); //���ȵ��� 0x00~0xff
    WriteCmd(0xa1); //--set segment re-map 0 to 127
    WriteCmd(0xa6); //--set normal display
    WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
    WriteCmd(0x3F); //
    WriteCmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
    WriteCmd(0xd3); //-set display offset
    WriteCmd(0x00); //-not offset
    WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
    WriteCmd(0xf0); //--set divide ratio
    WriteCmd(0xd9); //--set pre-charge period
    WriteCmd(0x22); //
    WriteCmd(0xda); //--set com pins hardware configuration
    WriteCmd(0x12);
    WriteCmd(0xdb); //--set vcomh
    WriteCmd(0x20); //0x20,0.77xVcc
    WriteCmd(0x8d); //--set DC-DC enable
    WriteCmd(0x14); //
    WriteCmd(0xaf); //--turn on oled panel
		
		OLED_CLS();
}


 /**
  * @brief  OLED_SetPos�����ù��
  * @param  x,���xλ��
    *                   y�����yλ��
  * @retval ��
  */
void OLED_SetPos(unsigned char x, unsigned char y) //������ʼ������
 { 
    WriteCmd(0xb0+y);
    WriteCmd(((x&0xf0)>>4)|0x10); //���ݸ���λΪ1 ����λΪ�е�ַ�ĸ���λ
    WriteCmd((x&0x0f)|0x01);			//���ݸ���λΪ0 ����λΪ�е�ַ�ĵ���λ
}

 /**
  * @brief  OLED_Fill�����������Ļ
  * @param  fill_Data:Ҫ��������
    * @retval ��
  */
void OLED_Fill(unsigned char fill_Data)//ȫ�����
{
    unsigned char m,n;
    for(m=0;m<8;m++)
    {
        WriteCmd(0xb0+m);       //page0-page1
        WriteCmd(0x00);     //low column start address
        WriteCmd(0x10);     //high column start address
        for(n=0;n<128;n++)
            {
                WriteDat(fill_Data);
            }
    }
}

 /**
  * @brief  OLED_CLS������
  * @param  ��
    * @retval ��
  */
void OLED_CLS(void)//����
{
    OLED_Fill(0x00);
}


 /**
  * @brief  OLED_ON����OLED�������л���
  * @param  ��
    * @retval ��
  */
void OLED_ON(void)
{
    WriteCmd(0X8D);  //���õ�ɱ�
    WriteCmd(0X14);  //������ɱ�
    WriteCmd(0XAF);  //OLED����
}


 /**
  * @brief  OLED_OFF����OLED���� -- ����ģʽ��,OLED���Ĳ���10uA
  * @param  ��
    * @retval ��
  */
void OLED_OFF(void)
{
    WriteCmd(0X8D);  //���õ�ɱ�
    WriteCmd(0X10);  //�رյ�ɱ�
    WriteCmd(0XAE);  //OLED����
}


 /**
  * @brief  OLED_ShowStr����ʾcodetab.h�е�ASCII�ַ�,��6*8��8*16��ѡ��
  * @param  x,y : ��ʼ������(x:0~127, y:0~7);
    *                   ch[] :- Ҫ��ʾ���ַ���; 
    *                   TextSize : �ַ���С(1:6*8 ; 2:8*16)
    * @retval ��
  */
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
{
    unsigned char c = 0,i = 0,j = 0;
    switch(TextSize)
    {
        case 1:
        {
            while(ch[j] != '\0')
            {
                c = ch[j] - 32;
                if(x > 126)
                {
                    x = 0;
                    y++;
                }
                OLED_SetPos(x,y);
                for(i=0;i<6;i++)
                    WriteDat(F6x8[c][i]);
                x += 6;
                j++;
            }
        }break;
        case 2:
        {
            while(ch[j] != '\0')
            {
                c = ch[j] - 32;
                if(x > 120)
                {
                    x = 0;
                    y++;
                }
                OLED_SetPos(x,y);
                for(i=0;i<8;i++)
                    WriteDat(F8X16[c*16+i]);
                OLED_SetPos(x,y+1);
                for(i=0;i<8;i++)
                    WriteDat(F8X16[c*16+i+8]);
                x += 8;
                j++;
            }
        }break;
    }
}

 /**
  * @brief  OLED_ShowCN����ʾcodetab.h�еĺ���,16*16����
  * @param  x,y: ��ʼ������(x:0~127, y:0~7); 
    *                   N:������codetab.h�е�����
    * @retval ��
  */
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
{
    unsigned char wm=0;
    unsigned int  adder=32*N;
    OLED_SetPos(x , y);
    for(wm = 0;wm < 16;wm++)
    {
        WriteDat(F16x16[adder]);
        adder += 1;
    }
    OLED_SetPos(x,y + 1);
    for(wm = 0;wm < 16;wm++)
    {
        WriteDat(F16x16[adder]);
        adder += 1;
    }
}



 /**
  * @brief  OLED_DrawBMP����ʾBMPλͼ
  * @param  x0,y0 :��ʼ������(x0:0~127, y0:0~7);
    *                   x1,y1 : ���Խ���(������)������(x1:1~128,y1:1~8)
    * @retval ��
  */
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[])
{
    unsigned int j=0;
    unsigned char x,y;

  if(y1%8==0)
        y = y1/8;
  else
        y = y1/8 + 1;
    for(y=y0;y<y1;y++)
    {
       OLED_SetPos(x0,y);
			 for(x=x0;x<x1;x++)
				{
						WriteDat(BMP[j++]);
				}
    }
}