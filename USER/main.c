
/**************************************
 * 文件名  ：main.c
 * 描述    ：通过串口调试软件，向板子发送数据，板子接收到数据后，立即回传给电脑。
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 库版本  ：ST3.0.0

*********************************************************/

#include "Delay.h"
#include "IICUtils.h"
#include "SGP30.h"
#include "SHT30.h"
#include "led.h"
#include "oled.h"
#include "serialDeal.h"
#include "stdio.h"
#include "stm32f10x.h"
#include "string.h"
#include "usart1.h"

int main(void) {
    u8 flushOLED = 0;
    char buff[17];

    SystemInit();     //配置系统时钟为 72M
    USART1_Config();  // USART1 配置
    printf("USART初始化完成!\n");
    s_sendStr("测试数据", 9);
    Delay_Init();
    printf("Delay_Init初始化完成!\n");
    IIC_Init();
    printf("IIC初始化完成!\n");

    SGP30_SelfCheck();

    SGP30_Init();
    printf("SGP30初始化完成!\n");

    // SHT30_Init(0x44);
    // printf("SHT30初始化完成!\n");

    LED_GPIO_Config();

    OLED_GPIO_CONFIG();

    LED1(ON);  // 亮
    OLED_Init();
    // OLED_TEST();


    OLED_Display_GB2312_string(0, 0, "智能制造技术训练");
    OLED_Display_GB2312_string(0, 4, "   LokHin Can");
    OLED_Display_GB2312_string(0, 6, "    荣誉出品");

    Delay_ms(3000);

    OLED_Clear();

    LED1(OFF);

    while (1) {
        LED1(ON);
        Delay_ms(1500);
        // UART1Deal();
        // SGP30_SelfCheck();
        LED1(OFF);
		// OLED_Clear();


		// OLED_Display_GB2312_string(0, 4, "Temp ");
		// OLED_Display_GB2312_string(0, 6, "Humi ");
		// OLED_Display_GB2312_string(0, 0, "CO   ");
		// OLED_Display_GB2312_string(0, 2, "TVOC ");
		// SGP30_read_result();
		// SHT30_read_result(0x44);

		// OLED_Display_GB2312_string_format(40,4,127,5,"buff",0,1,0);
		// OLED_Display_GB2312_string_format(40,6,127,7,"buff",0,1,0);

		// continue;


        flushOLED++;
        if (flushOLED > 5) {
            flushOLED = 0;
            OLED_Init();

			OLED_Display_GB2312_string(0, 4, "Temp ");
			OLED_ShowNum(40, 4, SHT30_GetTemperature(), 4);
			OLED_Display_GB2312_string(80, 4, "'C");

			OLED_Display_GB2312_string(0, 6, "Humi ");
			sprintf(buff,"%.2f%%",SHT30_GetHumidity());
			OLED_Display_GB2312_string(40,6,buff);
        }


        if (SGP30_read_result() == 1) {
            //初始化完成
            // sprintf(buff,"CO2  %d",SGP30_GetCO2Data());
            // Delay_ms(10);
            // OLED_Display_GB2312_string(0,0,buff);
			Delay_ms(100);

            OLED_Display_GB2312_string(0, 0, "CO   ");
            OLED_Display_string_5x7(16, 1, "2");
            OLED_ShowInt(40, 0, SGP30_GetCO2Data(), 4);
            OLED_Display_GB2312_string(72, 0, "ppm");

            // sprintf(buff,"TVOC %d",SGP30_GetTVOCData());
            // Delay_ms(10);
            OLED_Display_GB2312_string(0, 2, "TVOC ");
            OLED_ShowInt(40, 2, SGP30_GetTVOCData(), 4);
            OLED_Display_GB2312_string(72, 2, "ppd");

            // if(SGP30_GetTVOCData()>5000){
            // 	printf("\n数据异常 重新初始化SGP30\n");
            // 	SGP30_Init();

            // }
        } else {
            OLED_Display_GB2312_string(0, 0, "SGP30");
            OLED_Display_GB2312_string(0, 2, "初始化中");
        }

        if(SHT30_read_result(0x44)){
			Delay_ms(100);
			
			OLED_Display_GB2312_string(0, 4, "Temp ");
			// OLED_ShowNum(40, 4, SHT30_GetTemperature(), 4);
			// OLED_Display_GB2312_string(80, 4, "'C");
			sprintf(buff,"%.2f%'C",SHT30_GetTemperature());
			OLED_Display_GB2312_string_format(40,4,127,5,buff,0,1,1);

			OLED_Display_GB2312_string(0, 6, "Humi ");
			// OLED_ShowNum(40, 6, SHT30_GetHumidity(), 5);
			// OLED_Display_GB2312_string(88, 6, "%");

			sprintf(buff,"%.2f%%",SHT30_GetHumidity());
			OLED_Display_GB2312_string_format(40,6,127,7,buff,0,1,1);

			// Delay_ms(300);
			// OLED_Display_GB2312_string_format(40,6,127,7,buff,0,1,1);
			// sprintf(buff,"%.2f%'C",SHT30_GetTemperature());
			// OLED_Display_GB2312_string_format(40,4,127,5,buff,0,1,1);
			
		}

        


        // sprintf(buff,"%i",i);

        // s_sendStr(buff,10);
        //  UART1Deal();
    }
}
