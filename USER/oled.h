#ifndef __OLED_H
#define	__OLED_H

#include "stm32f10x.h"


//~ #define u8  char
//~ #define u32  long
#define u8  unsigned char
#define u32 unsigned long

//~ ���Ŷ���
#define OLED_SCL GPIO_Pin_4       //CLK  ����ʱ��
#define OLED_SDA GPIO_Pin_5       //MOSI OLED/�ַ�оƬ ������������
#define OLED_DC GPIO_Pin_6        //DC OLED����/���� ѡ��  �ߵ�ƽΪ��������
#define OLED_CS GPIO_Pin_7        //CS1 OLEDƬѡ �͵�ƽΪѡ��
#define OLED_READ_FS0 GPIO_Pin_0  //FSO �ַ�оƬ���
#define OLED_ROM_CS GPIO_Pin_1    //CS2 �ַ�оƬƬѡ �͵�ƽΪѡ��

#define OLED_CMD  0   //д����
#define OLED_DATA 1   //д����

#define OLED_SCL_Set() GPIO_SetBits(GPIOA,OLED_SCL);
#define OLED_SCL_Clr() GPIO_ResetBits(GPIOA,OLED_SCL);

#define OLED_SDA_Set() GPIO_SetBits(GPIOA,OLED_SDA);
#define OLED_SDA_Clr() GPIO_ResetBits(GPIOA,OLED_SDA);

#define OLED_DC_Set() GPIO_SetBits(GPIOA,OLED_DC);
#define OLED_DC_Clr() GPIO_ResetBits(GPIOA,OLED_DC);

#define OLED_CS_Set() GPIO_SetBits(GPIOA,OLED_CS);
#define OLED_CS_Clr() GPIO_ResetBits(GPIOA,OLED_CS);

#define OLED_ROM_CS_Set() GPIO_SetBits(GPIOA,OLED_ROM_CS);
#define OLED_ROM_CS_Clr() GPIO_ResetBits(GPIOA,OLED_ROM_CS);

#define OLED_READ_FS0_Read() GPIO_ReadInputDataBit(GPIOA,OLED_READ_FS0)==1

void OLED_GPIO_CONFIG(void);	//����GPIO
int OLED_TEST(void);	//OLED���Գ���

void delay_ms(unsigned int ms);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void OLED_WR_Byte(u8 dat,u8 cmd);
void OLED_Clear(void);
void OLED_address(u8 x,u8 y);
void OLED_Display_128x64(u8 *dp);
void OLED_Display_16x16(u8 x,u8 y,u8 *dp);
void OLED_Display_8x16(u8 x,u8 y,u8 *dp);
void OLED_Display_5x7(u8 x,u8 y,u8 *dp);
void OLED_Init(void);


void Send_Command_to_ROM(u8 dat);
u8 Get_data_from_ROM(void);
void OLED_get_data_from_ROM(u8 addrHigh,u8 addrMid,u8 addrLow,u8 *pbuff,u8 DataLen);
void OLED_Display_GB2312_string(u8 x,u8 y,char *text);
void OLED_Display_string_5x7(u8 x,u8 y,char *text);
void OLED_ShowNum(u8 x,u8 y,float num,u8 len);
void OLED_DisPlay_Off(void);

					
					
					
					

#endif /* __OLED_H */
