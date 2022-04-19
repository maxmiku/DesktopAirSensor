#ifndef __OLED_H
#define	__OLED_H

#include "stm32f10x.h"
#include "delay.h"


//~ #define uint8_t  char
//~ #define u32  long



//~ 引脚定义
#define OLED_SCL GPIO_Pin_4       //CLK  公用时钟
#define OLED_SDA GPIO_Pin_5       //MOSI OLED/字符芯片 公用数据输入
#define OLED_DC GPIO_Pin_6        //DC OLED数据/命令 选择  高电平为数据输入
#define OLED_CS GPIO_Pin_7        //CS1 OLED片选 低电平为选中
#define OLED_READ_FS0 GPIO_Pin_0  //FSO 字符芯片输出
#define OLED_ROM_CS GPIO_Pin_1    //CS2 字符芯片片选 低电平为选中

#define OLED_CMD  0   //写命令
#define OLED_DATA 1   //写数据

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

void OLED_GPIO_CONFIG(void);	//配置GPIO
int OLED_TEST(void);	//OLED测试程序

void OLED_ColorTurn(uint8_t i);
void OLED_DisplayTurn(uint8_t i);
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);
void OLED_Clear(void);
void OLED_address(uint8_t x,uint8_t y);
void OLED_Display_128x64(uint8_t *dp);
void OLED_Display_16x16(uint8_t x,uint8_t y,uint8_t *dp);
void OLED_Display_8x16(uint8_t x,uint8_t y,uint8_t *dp);
void OLED_Display_5x7(uint8_t x,uint8_t y,uint8_t *dp);
void OLED_Init(void);


void Send_Command_to_ROM(uint8_t dat);
uint8_t Get_data_from_ROM(void);
void OLED_get_data_from_ROM(uint8_t addrHigh,uint8_t addrMid,uint8_t addrLow,uint8_t *pbuff,uint8_t DataLen);
void OLED_Display_GB2312_string(uint8_t x,uint8_t y,char *text);
void OLED_Display_string_5x7(uint8_t x,uint8_t y,char *text);
void OLED_ShowNum(uint8_t x,uint8_t y,float num,uint8_t len);
void OLED_ShowInt(uint8_t x, uint8_t y, uint16_t num1, uint8_t len);
void OLED_DisPlay_Off(void);

					
					
					
					

#endif /* __OLED_H */
