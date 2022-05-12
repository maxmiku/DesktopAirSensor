#ifndef __OLED_H
#define	__OLED_H

#include "stm32f10x.h"
#include "delay.h"


//~ #define uint8_t  char
//~ #define u32  long
// struct potRange_s{	//���귶Χ�ṹ
// 	/*
// 		StartPot*-------
// 				|       |
// 				 -------* EndPot
// 	*/
// 	uint8_t startX;	//��ʼX
// 	uint8_t startY;	//��ʼY
// 	uint8_t endX;	//����X
// 	uint8_t endY;	//����Y
// };


//~ ���Ŷ���
#define OLED_SCL GPIO_Pin_7       //CLK  ����ʱ��
#define OLED_SDA GPIO_Pin_0       //MOSI OLED/�ַ�оƬ ������������
#define OLED_DC GPIO_Pin_1        //DC OLED����/���� ѡ��  �ߵ�ƽΪ��������
#define OLED_CS GPIO_Pin_2        //CS1 OLEDƬѡ �͵�ƽΪѡ��
#define OLED_READ_FS0 GPIO_Pin_11  //FSO �ַ�оƬ���
#define OLED_ROM_CS GPIO_Pin_10    //CS2 �ַ�оƬƬѡ �͵�ƽΪѡ��

#define OLED_CMD  0   //д����
#define OLED_DATA 1   //д����

#define OLED_SCL_Set() GPIO_SetBits(GPIOA,OLED_SCL);
#define OLED_SCL_Clr() GPIO_ResetBits(GPIOA,OLED_SCL);

#define OLED_SDA_Set() GPIO_SetBits(GPIOB,OLED_SDA);
#define OLED_SDA_Clr() GPIO_ResetBits(GPIOB,OLED_SDA);

#define OLED_DC_Set() GPIO_SetBits(GPIOB,OLED_DC);
#define OLED_DC_Clr() GPIO_ResetBits(GPIOB,OLED_DC);

#define OLED_CS_Set() GPIO_SetBits(GPIOB,OLED_CS);
#define OLED_CS_Clr() GPIO_ResetBits(GPIOB,OLED_CS);

#define OLED_ROM_CS_Set() GPIO_SetBits(GPIOB,OLED_ROM_CS);
#define OLED_ROM_CS_Clr() GPIO_ResetBits(GPIOB,OLED_ROM_CS);

#define OLED_READ_FS0_Read() GPIO_ReadInputDataBit(GPIOB,OLED_READ_FS0)==1

void OLED_GPIO_CONFIG(void);	//����GPIO
int OLED_TEST(void);	//OLED���Գ���

void OLED_ColorTurn(uint8_t i);
void OLED_DisplayTurn(uint8_t i);
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);
void OLED_WR_Byte_reverse(uint8_t dat, uint8_t cmd, uint8_t reverse);
void OLED_Clear(void);
void OLED_ClearPart(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY,uint8_t reverse);
void OLED_address(uint8_t x,uint8_t y);
void OLED_Display_128x64(uint8_t *dp);
void OLED_Display_128x64_reverse(uint8_t* dp,uint8_t reverse);
void OLED_Display_16x16(uint8_t x,uint8_t y,uint8_t *dp);
void OLED_Display_16x16_reverse(uint8_t x, uint8_t y, uint8_t* dp,uint8_t reverse);
void OLED_Display_8x16(uint8_t x,uint8_t y,uint8_t *dp);
void OLED_Display_8x16_reverse(uint8_t x, uint8_t y, uint8_t* dp,uint8_t reverse);
void OLED_Display_5x7(uint8_t x,uint8_t y,uint8_t *dp);
void OLED_Display_5x7_reverse(uint8_t x, uint8_t y, uint8_t* dp,uint8_t reverse);
void OLED_Init(void);


void Send_Command_to_ROM(uint8_t dat);
uint8_t Get_data_from_ROM(void);
void OLED_get_data_from_ROM(uint8_t addrHigh,uint8_t addrMid,uint8_t addrLow,uint8_t *pbuff,uint8_t DataLen);
void OLED_Display_GB2312_string(uint8_t x,uint8_t y,char *text);
void OLED_Display_GB2312_string_format(uint8_t x, uint8_t y, uint8_t x1, uint8_t y1, char* text, uint8_t reverse, uint8_t cleanUp, uint8_t background);
void OLED_Display_string_5x7(uint8_t x,uint8_t y,char *text);
void OLED_ShowNum(uint8_t x,uint8_t y,float num,uint8_t len);
void OLED_ShowInt(uint8_t x, uint8_t y, uint16_t num1, uint8_t len);
void OLED_DisPlay_Off(void);

					
// uint8_t checkPotAvailable(struct potRange_s* pot);
// void setPotRange(struct potRange_s* pot, uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY);					
					
					

#endif /* __OLED_H */
