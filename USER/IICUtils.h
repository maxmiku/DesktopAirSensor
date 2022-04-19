#ifndef __IICUtils_H
#define __IICUtils_H
#include "sys.h"

   	   		   
//IO��������
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=0X80000000;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=0X30000000;}

//IO��������	 
#define IIC_SCL    PBout(6) //SCL
#define IIC_SDA    PBout(7) //SDA	 
#define READ_SDA   PBin(7)  //����SDA 

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
// void IIC_Send_Word(u8 txd1,u8 txd2);//IIC����һ����
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u16 IIC_Read_Byte_1(unsigned char ack);
// u16 IIC_Read_Word(unsigned char ack);//IIC��ȡһ����
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�


#endif
