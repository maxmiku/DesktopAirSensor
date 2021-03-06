/**
 * @file oled.c
 * @author Lok
 * @brief 中景园oled驱动程序
 * @version 0.2
 * @date 2022-05-12
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "oled.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"
#include "led.h"
#include "oled.h"
#include "usart1.h"

// const int LEDpin = 9;

void OLED_GPIO_CONFIG() {
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // 使能PA端口时钟
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    //输出初始化
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出

    GPIO_InitStructure.GPIO_Pin = OLED_SCL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = OLED_DC | OLED_CS | OLED_ROM_CS | OLED_SDA;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //输入初始化
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入
    GPIO_InitStructure.GPIO_Pin = OLED_READ_FS0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
    // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    // GPIO_Init(GPIOC, &GPIO_InitStructure);
}

int OLED_TEST() {
    // uint8_t data[]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0xBF,0x5F,0xAF,0x57,0x2B,0x57,0xAF,0x5F,0xBF,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0xBF,0x5F,0xAF,0x57,0x2B,0x15,0x0A,0x05,0x02,0x01,0x00,0x00,0x82,0xC5,0xF2,0xF3,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0xBF,0x5F,0xAF,0x57,0x2B,0x15,0x0A,0x05,0x02,0x01,0x00,0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x1F,0x0F,0x1F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0xBF,0x5F,0xAF,0x57,0x2B,0x15,0x0A,0x05,0x02,0x01,0x00,0x80,0xC0,0xC0,0xE0,0xF0,0xFC,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF9,0xF0,0xE0,0xC0,0x80,0x00,0x00,0x02,0x05,0x0A,0x15,0x2B,0x57,0xAF,0x5F,0xBF,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0xBF,0x5F,0xAF,0x57,0x2B,0x15,0x0A,0x05,0x02,0x01,0x00,0x80,0xC0,0xC0,0xF0,0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFC,0xF8,0xF0,0xE0,0xC0,0x80,0x00,0x01,0x02,0x05,0x0A,0x15,0x2B,0x57,0xAF,0x5F,0xBF,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0xBF,0x5F,0xAF,0x57,0x2B,0x15,0x0A,0x05,0x02,0x01,0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFC,0xF8,0xF0,0xE0,0xC0,0x80,0x00,0x01,0x02,0x05,0x0A,0x01,0x0B,0x0B,0x05,0x0A,0x05,0x02,0x01,0x00,0xC0,0xE0,0xE0,0xF0,0xF8,0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFC,0xF8,0xF0,0xE0,0xC0,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

    // // 初始化树莓派GPIO库
    // if(wiringPiSetup()==-1)
    // {
    // 	printf("setup error\n");
    // 	exit(-1);
    // }

    // printf("程序开始执行\n");
    //
    // printf("设置接口为输出\n");
    // pinMode(OLED_SCL,OUTPUT); //CLK  公用时钟
    // pinMode(OLED_SDA,OUTPUT);   //MOSI OLED/字符芯片 公用数据输入
    // pinMode(OLED_DC,OUTPUT); //DC OLED数据/命令 选择  高电平为数据输入
    // pinMode(OLED_CS,OUTPUT);//CS1 OLED片选 低电平为选中
    // pinMode(OLED_READ_FS0,INPUT); //FSO 字符芯片输出
    // pinMode(OLED_ROM_CS,OUTPUT);//CS2 字符芯片片选 低电平为选中

    // printf("oled初始化\n");
    OLED_Init();          // oled初始化
    OLED_ColorTurn(0);    // 0正常显示，1 反色显示
    OLED_DisplayTurn(0);  // 0正常显示 1 屏幕翻转显示
    OLED_Clear();

    Delay_ms(1000);

    // printf("oled写出内容\n");
    // OLED_Display_128x64(bmp1);

    // printf("延迟2秒\n");
    // Delay_ms(2000);

    // printf("oled写清屏\n");
    // OLED_Clear();

    // OLED_Display_GB2312_string(24,0,"中景园电子");
    // OLED_Display_GB2312_string(0,2,"主要生产OLED模块");
    // OLED_Display_GB2312_string(0,4,"顾客至上真诚服务");
    // OLED_Display_GB2312_string(0,6,"诚信与质量第一！");

    // printf("延迟2秒\n");
    // Delay_ms(2000);
    // OLED_Clear();
    // Delay_ms(50);
    // printf("oled写出第二屏内容\n");

    // OLED_Display_GB2312_string(0,0,"<!@#$%^&*()_-+]/");	/*在第1页，第1列，显示一串16x16点阵汉字或8*16的ASCII字*/
    OLED_Display_string_5x7(0, 0, "abcdef"); /*在第3页，第1列，显示一串5x7点阵的ASCII字*/
    // OLED_Display_string_5x7(0,3,"XY electronics Co., ");/*显示一串5x7点阵的ASCII字*/
    // OLED_Display_string_5x7(0,4,"Ltd. established at  ");/*显示一串5x7点阵的ASCII字*/
    // OLED_Display_string_5x7(0,5,"year 2010.Focus OLED ");/*显示一串5x7点阵的ASCII字*/
    // OLED_Display_string_5x7(0,6,"Mobile:13265585975");/*显示一串5x7点阵的ASCII字*/
    // OLED_Display_string_5x7(0,7,"Tel:0755-32910715");/*显示一串5x7点阵的ASCII字*/

    // printf("延迟2秒\n");
    // Delay_ms(2000);
    // OLED_Clear();
    // Delay_ms(20);
    // printf("oled写出第三屏内容\n");

    // OLED_Display_GB2312_string(0,0,"下一节课:");
    // OLED_Display_GB2312_string(32,2,"高等数学");
    // OLED_Display_GB2312_string(32,4,"上午9:40");

    // char strtmp[50];
    // for(int i=0;i<10;i++){
    // sprintf(strtmp,"今天剩余 %d 节",i);
    // OLED_Display_GB2312_string(0,6, strtmp);
    // Delay_ms(2000);

    // }

    // Delay_ms(3000);

    // OLED_Display_128x64(data);

    // for(uint8_t i=1;i>0;i*=2){
    // printf("%d\n",i);
    // uint8_t data[6]={0,0,0,0,i,0};
    // OLED_Display_5x7(0,0,data);
    // Delay_ms(1000);
    // }
    // Delay_ms(2000);
    // OLED_Clear();

    OLED_Display_GB2312_string(16, 2, "程序运行结束");
    OLED_Display_GB2312_string(48, 4, "再见");
    OLED_Display_GB2312_string(48, 6, "Bye");

    // OLED_ColorTurn(0);

    // Delay_ms(3000);

    // OLED_DisPlay_Off();

    // printf("end\n");

    return 0;
}

//向SSD1306写入一个字节。
// mode:数据/命令标志 0,表示命令;1,表示数据;
void OLED_WR_Byte(uint8_t dat, uint8_t cmd) {
	OLED_WR_Byte_reverse(dat,cmd,0);
    // uint8_t i;
    // if (cmd) {
    //     OLED_DC_Set();
    // } else {
    //     OLED_DC_Clr();
    // }
    // OLED_CS_Clr();

    // for (i = 0; i < 8; i++) {
    //     OLED_SCL_Clr();

    //     if (dat & 0x80) {
    //         OLED_SDA_Set();
    //     } else {
    //         OLED_SDA_Clr();
    //     }

    //     OLED_SCL_Set();
    //     dat <<= 1;
    // }

    // OLED_CS_Set();
    // OLED_DC_Set();
}
void OLED_WR_Byte_reverse(uint8_t dat, uint8_t cmd, uint8_t reverse) {
    uint8_t i;
    if (cmd) {
        OLED_DC_Set();
    } else {
        OLED_DC_Clr();
    }
    OLED_CS_Clr();
	// Delay_us(1);
    if (reverse) {
        //翻转
        for (i = 0; i < 8; i++) {
            OLED_SCL_Clr();

            if (dat & 0x80) {
                OLED_SDA_Clr();
            } else {
                OLED_SDA_Set();
            }
			
            OLED_SCL_Set();
			// Delay_us(10);
            dat <<= 1;
        }
    } else {
        for (i = 0; i < 8; i++) {
            OLED_SCL_Clr();

            if (dat & 0x80) {
                OLED_SDA_Set();
            } else {
                OLED_SDA_Clr();
            }

            OLED_SCL_Set();
			// Delay_us(1);

            dat <<= 1;
        }
    }
    OLED_CS_Set();
    OLED_DC_Set();
}

//反显函数
void OLED_ColorTurn(uint8_t i) {
    if (i == 0) {
        OLED_WR_Byte(0xA6, OLED_CMD);  //正常显示
    }
    if (i == 1) {
        OLED_WR_Byte(0xA7, OLED_CMD);  //反色显示
    }
}

//屏幕旋转180度
void OLED_DisplayTurn(uint8_t i) {
    if (i == 0) {
        OLED_WR_Byte(0xC8, OLED_CMD);  //正常显示
        OLED_WR_Byte(0xA1, OLED_CMD);
    }
    if (i == 1) {
        OLED_WR_Byte(0xC0, OLED_CMD);  //反转显示
        OLED_WR_Byte(0xA0, OLED_CMD);
    }
}

//开启OLED显示
void OLED_DisPlay_On(void) {
    OLED_WR_Byte(0x8D, OLED_CMD);  //电荷泵使能
    OLED_WR_Byte(0x14, OLED_CMD);  //开启电荷泵
    OLED_WR_Byte(0xAF, OLED_CMD);  //点亮屏幕
}

//关闭OLED显示
void OLED_DisPlay_Off(void) {
    OLED_WR_Byte(0x8D, OLED_CMD);  //电荷泵使能
    OLED_WR_Byte(0x10, OLED_CMD);  //关闭电荷泵
    OLED_WR_Byte(0xAE, OLED_CMD);  //关闭屏幕
}

//清屏函数
void OLED_Clear(void) {
    uint8_t i, n;
    for (i = 0; i < 8; i++) {
        OLED_WR_Byte(0xb0 + i, OLED_CMD);  //设置页地址
        OLED_WR_Byte(0x10, OLED_CMD);      //设置列地址的高4位
        OLED_WR_Byte(0x00, OLED_CMD);      //设置列地址的低4位
		// Delay_us(1);
        for (n = 0; n < 128; n++) {
            OLED_WR_Byte(0x00, OLED_DATA);  //清除所有数据
        }
		// Delay_us(10);
		// Delay_us(10);
    }
}

/**
 * @brief 局部清除屏幕
 *
 * @param startX
 * @param startY
 * @param endX
 * @param endY
 */
void OLED_ClearPart(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY, uint8_t reverse) {
    uint8_t i, n;
    for (i = startY; i <= endY; i++) {
        // OLED_WR_Byte(0xb0 + i, OLED_CMD); //设置页地址
        // OLED_WR_Byte(0x10, OLED_CMD);	  //设置列地址的高4位
        // OLED_WR_Byte(0x00, OLED_CMD);	  //设置列地址的低4位
        OLED_address(startX, i);
        for (n = startX; n <= endX; n++) {
            OLED_WR_Byte_reverse(0x00, OLED_DATA, reverse);  //清除所有数据
        }
    }
}

//设置起始地址
void OLED_address(uint8_t x, uint8_t y) {
    OLED_WR_Byte(0xb0 + y, OLED_CMD);                  //设置页地址
    OLED_WR_Byte(((x & 0xf0) >> 4) | 0x10, OLED_CMD);  //设置列地址的高4位
    OLED_WR_Byte((x & 0x0f), OLED_CMD);                //设置列地址的低4位
}

//显示128x64点阵图像
void OLED_Display_128x64(uint8_t* dp) {
    OLED_Display_128x64_reverse(dp, 0);
}
void OLED_Display_128x64_reverse(uint8_t* dp, uint8_t reverse) {
    uint8_t i, j;
    for (i = 0; i < 8; i++) {
        OLED_address(0, i);
        for (j = 0; j < 128; j++) {
            OLED_WR_Byte_reverse(*dp, OLED_DATA, reverse);  //写数据到OLED,每写完一个8位的数据后列地址自动加1
            dp++;
        }
    }
}

//显示16x16点阵图像、汉字、生僻字或16x16点阵的其他图标
void OLED_Display_16x16(uint8_t x, uint8_t y, uint8_t* dp) {
    OLED_Display_16x16_reverse(x, y, dp, 0);
}
void OLED_Display_16x16_reverse(uint8_t x, uint8_t y, uint8_t* dp, uint8_t reverse) {
    uint8_t i, j;
    for (j = 0; j < 2; j++) {
        OLED_address(x, y);
        for (i = 0; i < 16; i++) {
            OLED_WR_Byte_reverse(*dp, OLED_DATA, reverse);  //写数据到OLED,每写完一个8位的数据后列地址自动加1
            dp++;
        }
        y++;
    }
}

//显示8x16点阵图像、ASCII, 或8x16点阵的自造字符、其他图标
void OLED_Display_8x16(uint8_t x, uint8_t y, uint8_t* dp) {
    OLED_Display_8x16_reverse(x, y, dp, 0);
}
void OLED_Display_8x16_reverse(uint8_t x, uint8_t y, uint8_t* dp, uint8_t reverse) {
    uint8_t i, j;
    for (j = 0; j < 2; j++) {
        OLED_address(x, y);
        for (i = 0; i < 8; i++) {
            OLED_WR_Byte_reverse(*dp, OLED_DATA, reverse);  //写数据到LCD,每写完一个8位的数据后列地址自动加1
            dp++;
        }
        y++;
    }
}

//显示5*7点阵图像、ASCII, 或5x7点阵的自造字符、其他图标
void OLED_Display_5x7(uint8_t x, uint8_t y, uint8_t* dp) {
    OLED_Display_5x7_reverse(x, y, dp, 0);
}
void OLED_Display_5x7_reverse(uint8_t x, uint8_t y, uint8_t* dp, uint8_t reverse) {
    uint8_t i;
    OLED_address(x, y);
    for (i = 0; i < 6; i++) {
        OLED_WR_Byte_reverse(*dp, OLED_DATA, reverse);
        dp++;
    }
}

// OLED的初始化
void OLED_Init(void) {
    OLED_CS_Set();
    OLED_ROM_CS_Set();
    Delay_ms(200);

    OLED_WR_Byte(0xAE, OLED_CMD);  //--turn off oled panel
    OLED_WR_Byte(0x00, OLED_CMD);  //---set low column address
    OLED_WR_Byte(0x10, OLED_CMD);  //---set high column address
    OLED_WR_Byte(0x40, OLED_CMD);  //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WR_Byte(0x81, OLED_CMD);  //--set contrast control register
    OLED_WR_Byte(0xCF, OLED_CMD);  // Set SEG Output Current Brightness
    OLED_WR_Byte(0xA1, OLED_CMD);  //--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
    OLED_WR_Byte(0xC8, OLED_CMD);  // Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
    OLED_WR_Byte(0xA6, OLED_CMD);  //--set normal display
    OLED_WR_Byte(0xA8, OLED_CMD);  //--set multiplex ratio(1 to 64)
    OLED_WR_Byte(0x3f, OLED_CMD);  //--1/64 duty
    OLED_WR_Byte(0xD3, OLED_CMD);  //-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
    OLED_WR_Byte(0x00, OLED_CMD);  //-not offset
    OLED_WR_Byte(0xd5, OLED_CMD);  //--set display clock divide ratio/oscillator frequency
    OLED_WR_Byte(0x80, OLED_CMD);  //--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WR_Byte(0xD9, OLED_CMD);  //--set pre-charge period
    OLED_WR_Byte(0xF1, OLED_CMD);  // Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WR_Byte(0xDA, OLED_CMD);  //--set com pins hardware configuration
    OLED_WR_Byte(0x12, OLED_CMD);
    OLED_WR_Byte(0xDB, OLED_CMD);  //--set vcomh
    OLED_WR_Byte(0x40, OLED_CMD);  // Set VCOM Deselect Level
    OLED_WR_Byte(0x20, OLED_CMD);  //-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WR_Byte(0x02, OLED_CMD);  //
    OLED_WR_Byte(0x8D, OLED_CMD);  //--set Charge Pump enable/disable
    OLED_WR_Byte(0x14, OLED_CMD);  //--set(0x10) disable
    OLED_WR_Byte(0xA4, OLED_CMD);  // Disable Entire Display On (0xa4/0xa5)
    OLED_WR_Byte(0xA6, OLED_CMD);  // Disable Inverse Display On (0xa6/a7)
    OLED_Clear();
    OLED_WR_Byte(0xAF, OLED_CMD); /*display ON*/
}

// 字符芯片部分
//送指令到晶联讯字库IC
void Send_Command_to_ROM(uint8_t dat) {
    uint8_t i;
    for (i = 0; i < 8; i++) {
        OLED_SCL_Clr();
        if (dat & 0x80) {
            OLED_SDA_Set();
        } else {
            OLED_SDA_Clr();
        }
        dat <<= 1;
        OLED_SCL_Set();
		// Delay_us(2);
        // Delay_ms(1);
    }
}

//从晶联讯字库IC中取汉字或字符数据（1个字节）
uint8_t Get_data_from_ROM(void) {
    uint8_t i, read = 0;
    for (i = 0; i < 8; i++) {
        OLED_SCL_Clr();
        // Delay_ms(10);
		// Delay_us(10);


        read <<= 1;

        if (OLED_READ_FS0_Read()) {
            // UART1SendByte('#');
            // LED1(ON);
            read++;
        } else {
            // UART1SendByte(' ');
            // LED1(OFF);
        }

        OLED_SCL_Set();
		// Delay_us(1);

    }
    // UART1SendByte('\n');
    // Delay_ms(10);

    return read;
}

//从相关地址（addrHigh：地址高字节,addrMid：地址中字节,addrLow：地址低字节）中连续读出DataLen个字节的数据到 pbuff的地址
//连续读取
void OLED_get_data_from_ROM(uint8_t addrHigh, uint8_t addrMid, uint8_t addrLow, uint8_t* pbuff, uint8_t DataLen) {
    uint8_t i;
    OLED_ROM_CS_Clr();
    Send_Command_to_ROM(0x03);
    Send_Command_to_ROM(addrHigh);
    Send_Command_to_ROM(addrMid);
    Send_Command_to_ROM(addrLow);
    for (i = 0; i < DataLen; i++) {
        *(pbuff + i) = Get_data_from_ROM();
    }
    OLED_ROM_CS_Set();
}

u32 fontaddr = 0;
/**
 * @brief 显示GB2312字符在OLED上
 * 一个中文GB2312字符为16x16 西文字符8x16
 * @param x 横向坐标 0-127
 * @param y 纵向页 0-7 (每页8位)
 * @param text 欲显示的字符串
 * @param reverse 反显 0-正常  1-反显
 * @param cleanUp 清空区域后再显示字符 0-不清空 1-清空
 */
void OLED_Display_GB2312_string(uint8_t x, uint8_t y, char* text) {
    OLED_Display_GB2312_string_format(x, y, 0, 0, text, 0, 0, 0);
}
/**
 * @brief 显示GB2312字符在OLED上
 * 一个中文GB2312字符为16x16 西文字符8x16
 * @param x 横向坐标 0-127
 * @param y 纵向页 0-7 (每页8位)
 * @param x1 横向终点坐标 0-127 0为不指定
 * @param y1 纵向终点页 0-7 (每页8位)
 * @param text 欲显示的字符串
 * @param reverse 反显 0-正常  1-反显
 * @param cleanUp 清空区域后再显示字符 0-不清空 1-清空
 * @param background 背景是否反色 0-不反色 1-跟随reverse
 */
void OLED_Display_GB2312_string_format(uint8_t x, uint8_t y, uint8_t x1, uint8_t y1, char* text, uint8_t reverse, uint8_t cleanUp, uint8_t background) {
    uint8_t i = 0;
    uint8_t addrHigh, addrMid, addrLow;
    uint8_t fontbuf[32];

    // char text[64];

    // utf-8转换为gb2312
    //  if(u2g(buf, strlen(buf), text, sizeof(text))!=0){
    //  	printf("[Error]转换utf-8到gb2012出错 OLED_Display_GB2312_string\n");
    //  	return;
    //  }

    

    while (text[i] > 0x00) {
        if ((text[i] >= 0xb0) && (text[i] <= 0xf7) && (text[i + 1] >= 0xa1)) {
            //国标简体（GB2312）汉字在晶联讯字库IC中的地址由以下公式来计算：
            // Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 846)*32+ BaseAdd;BaseAdd=0
            //由于担心8位单片机有乘法溢出问题，所以分三部取地址
            fontaddr = (text[i] - 0xb0) * 94;
            fontaddr += (text[i + 1] - 0xa1) + 846;
            fontaddr = fontaddr * 32;

            addrHigh = (fontaddr & 0xff0000) >> 16;  //地址的高8位,共24位
            addrMid = (fontaddr & 0xff00) >> 8;      //地址的中8位,共24位
            addrLow = (fontaddr & 0xff);             //地址的低8位,共24位

            OLED_get_data_from_ROM(addrHigh, addrMid, addrLow, fontbuf, 32);
            //取32个字节的数据，存到"fontbuf[32]"
            OLED_Display_16x16_reverse(x, y, fontbuf, reverse);
            //显示汉字到LCD上，y为页地址，x为列地址，fontbuf[]为数据
            x += 16;
            i += 2;
        } else if ((text[i] >= 0xa1) && (text[i] <= 0xa3) && (text[i + 1] >= 0xa1)) {
            fontaddr = (text[i] - 0xa1) * 94;
            fontaddr += (text[i + 1] - 0xa1);
            fontaddr = fontaddr * 32;

            addrHigh = (fontaddr & 0xff0000) >> 16;
            addrMid = (fontaddr & 0xff00) >> 8;
            addrLow = (fontaddr & 0xff);

            OLED_get_data_from_ROM(addrHigh, addrMid, addrLow, fontbuf, 32);
            OLED_Display_16x16_reverse(x, y, fontbuf, reverse);
            x += 16;
            i += 2;
        } else if ((text[i] >= 0x20) && (text[i] <= 0x7e)) {
            unsigned char fontbuf[16];
            fontaddr = (text[i] - 0x20);
            fontaddr = (unsigned long)(fontaddr * 16);
            fontaddr = (unsigned long)(fontaddr + 0x3cf80);

            addrHigh = (fontaddr & 0xff0000) >> 16;
            addrMid = (fontaddr & 0xff00) >> 8;
            addrLow = fontaddr & 0xff;

            OLED_get_data_from_ROM(addrHigh, addrMid, addrLow, fontbuf, 16);
            OLED_Display_8x16_reverse(x, y, fontbuf, reverse);
            x += 8;
            i += 1;
        } else {
            i++;
        }
    }
    if (x1 != 0) {
        if (cleanUp) {
            OLED_ClearPart(x, y, x1, y1, background & reverse);
        }
    }
}

void OLED_Display_string_5x7(uint8_t x, uint8_t y, char* text) {
    uint8_t i = 0;
    uint8_t addrHigh, addrMid, addrLow;
    while (text[i] > 0x00) {
        if ((text[i] >= 0x20) && (text[i] <= 0x7e)) {
            uint8_t fontbuf[8];
            fontaddr = (text[i] - 0x20);
            fontaddr = (unsigned long)(fontaddr * 8);
            fontaddr = (unsigned long)(fontaddr + 0x3bfc0);
            // ASCII字符处理

            addrHigh = (fontaddr & 0xff0000) >> 16;
            addrMid = (fontaddr & 0xff00) >> 8;
            addrLow = fontaddr & 0xff;

            OLED_get_data_from_ROM(addrHigh, addrMid, addrLow, fontbuf, 8);
            OLED_Display_5x7(x, y, fontbuf);
            x += 6;
            i += 1;
        } else
            i++;
    }
}

//显示小数
// x,y :起点坐标
// num1：要显示的小数
// len :数字的位数
void OLED_ShowNum(uint8_t x, uint8_t y, float num1, uint8_t len) {
    uint8_t i;
    u32 t, num;
    x = x + len * 8 + 8;                         //要显示的小数最低位的横坐标
    num = num1 * 100;                            //将小数左移两位并转化为整数
    OLED_Display_GB2312_string(x - 24, y, ".");  //显示小数点
    for (i = 0; i < len; i++) {
        t = num % 10;    //取个位数的数值
        num = num / 10;  //将整数右移一位
        x -= 8;
        if (i == 2) {
            x -= 8;
        }  //当显示出来两个小数之后，空出小数点的位置
        switch (t) {
            case 0:
                OLED_Display_GB2312_string(x, y, "0");
                break;
            case 1:
                OLED_Display_GB2312_string(x, y, "1");
                break;
            case 2:
                OLED_Display_GB2312_string(x, y, "2");
                break;
            case 3:
                OLED_Display_GB2312_string(x, y, "3");
                break;
            case 4:
                OLED_Display_GB2312_string(x, y, "4");
                break;
            case 5:
                OLED_Display_GB2312_string(x, y, "5");
                break;
            case 6:
                OLED_Display_GB2312_string(x, y, "6");
                break;
            case 7:
                OLED_Display_GB2312_string(x, y, "7");
                break;
            case 8:
                OLED_Display_GB2312_string(x, y, "8");
                break;
            case 9:
                OLED_Display_GB2312_string(x, y, "9");
                break;
        }
    }
}

//显示整数
// x,y :起点坐标
// num1：要显示的整数
// len :数字的位数
void OLED_ShowInt(uint8_t x, uint8_t y, uint16_t num1, uint8_t len) {
    uint8_t i;
    u32 t, num;
    x = x + len * 8;  //要显示的小数最低位的横坐标
    num = num1;       //将小数左移两位并转化为整数
    // OLED_Display_GB2312_string(x - 24, y, "."); //显示小数点
    for (i = 0; i < len; i++) {
        t = num % 10;    //取个位数的数值
        num = num / 10;  //将整数右移一位
        x -= 8;

        switch (t) {
            case 0:
                OLED_Display_GB2312_string(x, y, "0");
                break;
            case 1:
                OLED_Display_GB2312_string(x, y, "1");
                break;
            case 2:
                OLED_Display_GB2312_string(x, y, "2");
                break;
            case 3:
                OLED_Display_GB2312_string(x, y, "3");
                break;
            case 4:
                OLED_Display_GB2312_string(x, y, "4");
                break;
            case 5:
                OLED_Display_GB2312_string(x, y, "5");
                break;
            case 6:
                OLED_Display_GB2312_string(x, y, "6");
                break;
            case 7:
                OLED_Display_GB2312_string(x, y, "7");
                break;
            case 8:
                OLED_Display_GB2312_string(x, y, "8");
                break;
            case 9:
                OLED_Display_GB2312_string(x, y, "9");
                break;
        }
    }
}

// /**
//  * @brief 判断potRange是否有效
//  *
//  * @param pot
//  * @return uint8_t 有效时为1 无效时为0
//  */
// uint8_t checkPotAvailable(struct potRange_s* pot) {
// 	if(pot==NULL){
// 		return 0;
// 	}
//     if (pot->startX == 255 || pot->startY == 255 || pot->endX == 255 || pot->endY == 255) {
//         return 0;
//     }
//     return 1;
// }

// /**
//  * @brief 设置pot的坐标
//  *
//  * @param pot
//  * @param startX
//  * @param startY
//  * @param endX
//  * @param endY
//  */
// void setPotRange(struct potRange_s* pot, uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY) {
//     pot->startX = startX;
//     pot->startY = startY;
//     pot->endX = endX;
//     pot->endY = endY;
// }
