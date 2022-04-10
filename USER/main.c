
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





int main(void)
{  
	uint8_t i = 0;
	SystemInit();	//配置系统时钟为 72M 
	
   
	USART1_Config(); //USART1 配置 		
	
	LED_GPIO_Config();

	OLED_GPIO_CONFIG();
	
	LED1( ON );			  // 亮
	OLED_TEST();

	
	
	LED1( OFF );		

	while(1){
		LED1( ON );
		delay_ms(200);
		// UART1Deal();
		LED1( OFF );
		delay_ms(200);
		i++;
		OLED_ShowNum(0,6,i,6);
		// UART1Deal();
	}
}
