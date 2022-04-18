
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
#include "stdio.h"
#include "string.h"
#include "serialDeal.h"





int main(void)
{  
	uint8_t i = 0;
	SystemInit();	//配置系统时钟为 72M 
	USART1_Config(); //USART1 配置 	
	printf("USART初始化完成!");
	s_sendStr("测试数据",9);
	Delay_Init();
	printf("Delay_Init初始化完成!");
	IIC_Init();
	printf("IIC初始化完成!");

	
   
	LED_GPIO_Config();

	OLED_GPIO_CONFIG();
	
	LED1( ON );			  // 亮
	OLED_TEST();

	
	
	LED1( OFF );	
	printf("程序运行完成");	

	while(1){
		LED1( ON );
		Delay_ms(1000);
		// UART1Deal();
		LED1( OFF );
		Delay_ms(1000);
		i++;
		SHT30_read_result(0x44);

		OLED_ShowNum(0,4,SHT30_GetTemperature(),6);
		OLED_ShowNum(0,6,SHT30_GetHumidity(),6);

		//sprintf(buff,"%i",i);

		//s_sendStr(buff,10);
		// UART1Deal();
	}
}
