
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



void USART1_IRQHandler ()
{
    u8 k;
    //判断现在发生的中断的类型，可以用USART_GetFlagStatus吗？
    if(USART_GetITStatus(USART1,USART_IT_RXNE)== SET)
    {
        //读接收寄存器，系统自动清除接收中断标志位
        k=USART_ReceiveData(USART1);
        k=k+2;
        //发送数据
        USART_SendData(USART1,k);

        //等发送完成；可以用USART_GetITStatus吗？
        while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
    }
}



int main(void)
{  
	     
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
		// UART1Deal();
	}
}
