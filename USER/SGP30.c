#include "SGP30.h"
#include "IICUtils.h"
#include "stdio.h"

u32 CO2Data = 0, TVOCData = 0; //定义CO2浓度变量与TVOC浓度变量
u8 SGP30_Inited = 0;		   // SGP30已启动标志 0未启动 1已启动

// SGP30 开始写入
void SGP30_IIC_Start_Write()
{
	IIC_Start();
	IIC_Send_Byte(SGP30_Addr << 1 | write); //发送地址及写指令
}

// SGP30 开始读取
void SGP30_Start_Read()
{
	IIC_Start();
	IIC_Send_Byte(SGP30_Addr << 1 | read); //发送地址及写指令
}

// SGP30 写出字命令 请手动停止IIC
void SGP30_Send_Command(u8 b1, u8 b2)
{
	SGP30_IIC_Start_Write(); //指定地址与模式
	IIC_Wait_Ack();
	IIC_Send_Byte(b1);
	IIC_Wait_Ack();
	IIC_Send_Byte(b2);
	IIC_Wait_Ack();
	IIC_Stop(); //部分指令需要获取数据 请不要取消这个注释
	Delay_ms(300);
}

// //SGP30读取32位数据
// u32 SGP30_Read_DWord()
// {
// 	u32 dat = 0;
// 	IIC_Start();
// 	IIC_Send_Byte(SGP30_Addr << 1 | read); //发送地址及写指令
// 	IIC_Wait_Ack();

// 	dat = IIC_Read_Word(1);
// 	dat <<= 16;

// 	IIC_Read_Word(1); // crc数据，舍去

// 	dat += IIC_Read_Word(1);
// 	IIC_Stop();
// 	return dat;
// }

u32 SGP30_Read_DWord(void)
{
	u32 dat;
	IIC_Start();
	IIC_Send_Byte(SGP30_Addr << 1 | read); //发送器件地址+读指令
	IIC_Wait_Ack();
	dat = IIC_Read_Byte(1);
	dat <<= 8;
	dat += IIC_Read_Byte(1);
	IIC_Read_Byte(1); // crc数据，舍去
	dat <<= 8;
	dat += IIC_Read_Byte(1);
	dat <<= 8;
	dat += IIC_Read_Byte(1);
	IIC_Read_Byte(0); // crc数据，舍去
	IIC_Stop();
	return (dat);
}

u16 SGP30_Read_Word(void)
{
	u16 dat;
	IIC_Start();
	IIC_Send_Byte(SGP30_Addr << 1 | read); //发送器件地址+读指令
	IIC_Wait_Ack();
	dat = IIC_Read_Byte(1);
	dat <<= 8;
	dat += IIC_Read_Byte(1);
	
	IIC_Read_Byte(0); // crc数据，舍去
	IIC_Stop();
	return (dat);
}

//初始化SGP30
void SGP30_Init(void)
{
	SGP30_Send_Command(0x20, 0x03); //发送初始化命令 Init_air_quality
	IIC_Stop();
	SGP30_Inited = 0;

	Delay_ms(100);
}

// SGP30从芯片读取数值 初始化中为0 初始完成为1
u8 SGP30_read_result()
{
	u32 sgp30_dat;

	SGP30_Send_Command(0x20, 0x08); // Measure_air_quality

	sgp30_dat = SGP30_Read_DWord();

	// printf("%X\n", sgp30_dat);

	CO2Data = (sgp30_dat & 0xffff0000) >> 16;
	TVOCData = sgp30_dat & 0x0000ffff;
	// SGP30模块开机需要一定时间初始化，在初始化阶段读取的CO2浓度为400ppm，TVOC为0ppd且恒定不变，因此上电后每隔一段时间读取一次
	// SGP30模块的值，如果CO2浓度为400ppm，TVOC为0ppd，发送“正在检测中...”，直到SGP30模块初始化完成。
	//初始化完成后刚开始读出数据会波动比较大，属于正常现象，一段时间后会逐渐趋于稳定。
	//气体类传感器比较容易受环境影响，测量数据出现波动是正常的，可自行添加滤波函数。
	// printf("CO2:%dppm TVOC:%dppd", CO2Data, TVOCData);
	if (SGP30_Inited == 0)
	{
		if (CO2Data != 400 || TVOCData != 0)
		{
			SGP30_Inited = 1; //芯片初始化完成
		}
		else
		{
			return 0;
		}
	}

	return 1;
}

//获取SGP30的二氧化碳数据
u32 SGP30_GetCO2Data(void)
{
	return CO2Data;
}

//获取SGP30的TVOC数据
u32 SGP30_GetTVOCData(void)
{
	return TVOCData;
}

void SGP30_SelfCheck()
{
	u32 rec = 0;
	// IIC_Start();
	// IIC_Send_Byte(0xb0);
	// IIC_Wait_Ack();

	// IIC_Send_Byte(0x20);
	// IIC_Wait_Ack();
	// IIC_Send_Byte(0x32);
	// IIC_Wait_Ack();
	// IIC_Stop();
	SGP30_Send_Command(0x20,0x32);

	// Delay_ms(500);
	rec=SGP30_Read_Word();

	// IIC_Start();
	// IIC_Send_Byte(0xb1);
	// IIC_Wait_Ack();

	// rec = IIC_Read_Byte_1(1);
	// rec <<= 8;
	// rec += IIC_Read_Byte_1(1);
	// rec <<= 8;

	// IIC_Read_Byte_1(1);

	// rec += IIC_Read_Byte_1(1);
	// rec <<= 8;
	// rec += IIC_Read_Byte_1(1);

	// IIC_Read_Byte_1(0);
	// IIC_Stop();
	printf("\nSGP自检返回:%X\n", rec);
}
