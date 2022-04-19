
/**************************************
 * 文件名  ：main.c
 * 描述    ：通过串口调试软件，向板子发送数据，板子接收到数据后，立即回传给电脑。         
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 库版本  ：ST3.0.0  																										  

*********************************************************/

#include "stm32f10x.h"
#include "usart1.h"
#include "led.h"
#include "oled.h"
#include "Delay.h"
#include "IICUtils.h"
#include "SHT30.h"
#include "SGP30.h"
#include "stdio.h"
#include "string.h"
#include "serialDeal.h"





int main(void)
{  
	uint8_t i = 0;
	// char buff[17];
	SystemInit();	//配置系统时钟为 72M 
	USART1_Config(); //USART1 配置 	
	printf("USART初始化完成!");
	s_sendStr("测试数据",9);
	Delay_Init();
	printf("Delay_Init初始化完成!");
	IIC_Init();
	printf("IIC初始化完成!");
	
	SGP30_SelfCheck();

	SGP30_Init();
	printf("SGP30初始化完成!");

   
	LED_GPIO_Config();

	OLED_GPIO_CONFIG();
	
	LED1( ON );			  // 亮
	OLED_TEST();

	Delay_ms(1000);

	OLED_Clear();
	
	LED1( OFF );	
	printf("程序运行完成");	

	while(1){
		LED1( ON );
		Delay_ms(1000);
		// UART1Deal();
		// SGP30_SelfCheck();
		LED1( OFF );
		Delay_ms(1000);
		i++;
		SHT30_read_result(0x44);

		OLED_Display_GB2312_string(0,4,"Temp ");
		OLED_ShowNum(40,4,SHT30_GetTemperature(),4);
		OLED_Display_GB2312_string(80,4,"℃");

		
		OLED_Display_GB2312_string(0,6,"Humi ");
		OLED_ShowNum(40,6,SHT30_GetHumidity(),4);
		OLED_Display_GB2312_string(80,6,"%");


		if(SGP30_read_result()==1){
			//初始化完成
			// sprintf(buff,"CO2  %d",SGP30_GetCO2Data());
			// Delay_ms(10);
			// OLED_Display_GB2312_string(0,0,buff);
			OLED_Display_GB2312_string(0,0,"CO2  ");
			OLED_ShowInt(40,0,SGP30_GetCO2Data(),4);
			OLED_Display_GB2312_string(72,0,"ppm");

			// sprintf(buff,"TVOC %d",SGP30_GetTVOCData());
			// Delay_ms(10);
			OLED_Display_GB2312_string(0,2,"TVOC ");
			OLED_ShowInt(40,2,SGP30_GetTVOCData(),4);
			OLED_Display_GB2312_string(72,2,"ppd");

			// if(SGP30_GetTVOCData()>5000){
			// 	printf("\n数据异常 重新初始化SGP30\n");
			// 	SGP30_Init();

			// }
		}else{
			OLED_Display_GB2312_string(0,0,"SGP30");
			OLED_Display_GB2312_string(0,2,"初始化中");

		}

		//sprintf(buff,"%i",i);

		//s_sendStr(buff,10);
		// UART1Deal();
	}
}
