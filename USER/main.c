
/**************************************
 * �ļ���  ��main.c
 * ����    ��ͨ�����ڵ������������ӷ������ݣ����ӽ��յ����ݺ������ش������ԡ�         
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103C8T6
 * ��汾  ��ST3.0.0  																										  

*********************************************************/

#include "stm32f10x.h"
#include "usart1.h"
#include "led.h"
#include "oled.h"





int main(void)
{  
	uint8_t i = 0;
	SystemInit();	//����ϵͳʱ��Ϊ 72M 
	
   
	USART1_Config(); //USART1 ���� 		
	
	LED_GPIO_Config();

	OLED_GPIO_CONFIG();
	
	LED1( ON );			  // ��
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
