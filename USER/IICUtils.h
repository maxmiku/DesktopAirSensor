#ifndef __IICUtils_H
#define __IICUtils_H
#include "sys.h"

   	   		   
//IO方向设置
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=0X80000000;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=0X30000000;}

//IO操作函数	 
#define IIC_SCL    PBout(6) //SCL
#define IIC_SDA    PBout(7) //SDA	 
#define READ_SDA   PBin(7)  //输入SDA 

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
// void IIC_Send_Word(u8 txd1,u8 txd2);//IIC发送一个字
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u16 IIC_Read_Byte_1(unsigned char ack);
// u16 IIC_Read_Word(unsigned char ack);//IIC读取一个字
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号


#endif
