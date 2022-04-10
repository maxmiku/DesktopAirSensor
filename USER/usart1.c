/***************************************
 * �ļ���  ��usart1.c
 * ����    ������USART1
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103C8T6
 * Ӳ�����ӣ�------------------------
 *          | PA9  - USART1(Tx)      |
 *          | PA10 - USART1(Rx)      |
 *           ------------------------
 * ��汾  ��ST3.0.0

**********************************************************************************/

#include "usart1.h"
#include <stdarg.h>
#include "misc.h"

void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* ʹ�� USART1 ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

	/* USART1 ʹ��IO�˿����� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);				  //��ʼ��GPIOA

	/* USART1 ����ģʽ���� */
	USART_InitStructure.USART_BaudRate = 115200;									//���������ã�115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;						//����λ�����ã�8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;							//ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity = USART_Parity_No;								//�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//�����뷢�Ͷ�ʹ��
	USART_Init(USART1, &USART_InitStructure);										//��ʼ��USART1
	USART_Cmd(USART1, ENABLE);														// USART1ʹ��

	//�ж����� ע����Ҫ���� misc.h�ļ�
	//��USART1�Ĵ��ڽ����жϣ�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	//����жϱ�־λ
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);

	//���ж�����
	//�ǵ������жϲ���֮ǰ��Ҫ�����жϷ��飻
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	//ѡ��USART1�ж�
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //ʹ�ܴ����ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		  //����Ӧ���ȼ�

	NVIC_Init(&NVIC_InitStructure); //��ʼ���ж�
}

/*����һ���ֽ�����*/
void UART1SendByte(unsigned char SendData)
{
	USART_SendData(USART1, SendData);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
		;
}

/*����һ���ֽ�����*/
unsigned char UART1GetByte(unsigned char *GetData)
{
	if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
	{
		return 0; //û���յ�����
	}
	*GetData = USART_ReceiveData(USART1);
	return 1; //�յ�����
}
/*����һ�����ݣ����Ϸ��ؽ��յ����������*/
void UART1Deal(void)
{
	unsigned char i = 0;
	while (UART1GetByte(&i) == 1)
	{
		USART_SendData(USART1, i);
	}
}

//�����жϴ������
void USART1_IRQHandler()
{
	u8 k;
	//�ж����ڷ������жϵ����ͣ�������USART_GetFlagStatus��
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		//�����ռĴ�����ϵͳ�Զ���������жϱ�־λ
		k = USART_ReceiveData(USART1);
		k = k + 2;
		//��������
		USART_SendData(USART1, k);

		//�ȷ�����ɣ�������USART_GetITStatus��
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	}
}
