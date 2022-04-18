
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
#include "Delay.h"
#include "IICUtils.h"
#include "SHT30.h"
#include "stdio.h"
#include "string.h"
#include "serialDeal.h"





int main(void)
{  
	uint8_t i = 0;
	SystemInit();	//����ϵͳʱ��Ϊ 72M 
	USART1_Config(); //USART1 ���� 	
	printf("USART��ʼ�����!");
	s_sendStr("��������",9);
	Delay_Init();
	printf("Delay_Init��ʼ�����!");
	IIC_Init();
	printf("IIC��ʼ�����!");

	
   
	LED_GPIO_Config();

	OLED_GPIO_CONFIG();
	
	LED1( ON );			  // ��
	OLED_TEST();

	
	
	LED1( OFF );	
	printf("�����������");	

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
