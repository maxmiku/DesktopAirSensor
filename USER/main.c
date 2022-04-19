
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
#include "SGP30.h"
#include "stdio.h"
#include "string.h"
#include "serialDeal.h"





int main(void)
{  
	uint8_t i = 0;
	// char buff[17];
	SystemInit();	//����ϵͳʱ��Ϊ 72M 
	USART1_Config(); //USART1 ���� 	
	printf("USART��ʼ�����!");
	s_sendStr("��������",9);
	Delay_Init();
	printf("Delay_Init��ʼ�����!");
	IIC_Init();
	printf("IIC��ʼ�����!");
	
	SGP30_SelfCheck();

	SGP30_Init();
	printf("SGP30��ʼ�����!");

   
	LED_GPIO_Config();

	OLED_GPIO_CONFIG();
	
	LED1( ON );			  // ��
	OLED_TEST();

	Delay_ms(1000);

	OLED_Clear();
	
	LED1( OFF );	
	printf("�����������");	

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
		OLED_Display_GB2312_string(80,4,"��");

		
		OLED_Display_GB2312_string(0,6,"Humi ");
		OLED_ShowNum(40,6,SHT30_GetHumidity(),4);
		OLED_Display_GB2312_string(80,6,"%");


		if(SGP30_read_result()==1){
			//��ʼ�����
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
			// 	printf("\n�����쳣 ���³�ʼ��SGP30\n");
			// 	SGP30_Init();

			// }
		}else{
			OLED_Display_GB2312_string(0,0,"SGP30");
			OLED_Display_GB2312_string(0,2,"��ʼ����");

		}

		//sprintf(buff,"%i",i);

		//s_sendStr(buff,10);
		// UART1Deal();
	}
}
