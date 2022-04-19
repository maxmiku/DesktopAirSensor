#include "SGP30.h"
#include "IICUtils.h"
#include "stdio.h"

u32 CO2Data = 0, TVOCData = 0; //����CO2Ũ�ȱ�����TVOCŨ�ȱ���
u8 SGP30_Inited = 0;		   // SGP30��������־ 0δ���� 1������

// SGP30 ��ʼд��
void SGP30_IIC_Start_Write()
{
	IIC_Start();
	IIC_Send_Byte(SGP30_Addr << 1 | write); //���͵�ַ��дָ��
}

// SGP30 ��ʼ��ȡ
void SGP30_Start_Read()
{
	IIC_Start();
	IIC_Send_Byte(SGP30_Addr << 1 | read); //���͵�ַ��дָ��
}

// SGP30 д�������� ���ֶ�ֹͣIIC
void SGP30_Send_Command(u8 b1, u8 b2)
{
	SGP30_IIC_Start_Write(); //ָ����ַ��ģʽ
	IIC_Wait_Ack();
	IIC_Send_Byte(b1);
	IIC_Wait_Ack();
	IIC_Send_Byte(b2);
	IIC_Wait_Ack();
	IIC_Stop(); //����ָ����Ҫ��ȡ���� �벻Ҫȡ�����ע��
	Delay_ms(300);
}

// //SGP30��ȡ32λ����
// u32 SGP30_Read_DWord()
// {
// 	u32 dat = 0;
// 	IIC_Start();
// 	IIC_Send_Byte(SGP30_Addr << 1 | read); //���͵�ַ��дָ��
// 	IIC_Wait_Ack();

// 	dat = IIC_Read_Word(1);
// 	dat <<= 16;

// 	IIC_Read_Word(1); // crc���ݣ���ȥ

// 	dat += IIC_Read_Word(1);
// 	IIC_Stop();
// 	return dat;
// }

u32 SGP30_Read_DWord(void)
{
	u32 dat;
	IIC_Start();
	IIC_Send_Byte(SGP30_Addr << 1 | read); //����������ַ+��ָ��
	IIC_Wait_Ack();
	dat = IIC_Read_Byte(1);
	dat <<= 8;
	dat += IIC_Read_Byte(1);
	IIC_Read_Byte(1); // crc���ݣ���ȥ
	dat <<= 8;
	dat += IIC_Read_Byte(1);
	dat <<= 8;
	dat += IIC_Read_Byte(1);
	IIC_Read_Byte(0); // crc���ݣ���ȥ
	IIC_Stop();
	return (dat);
}

u16 SGP30_Read_Word(void)
{
	u16 dat;
	IIC_Start();
	IIC_Send_Byte(SGP30_Addr << 1 | read); //����������ַ+��ָ��
	IIC_Wait_Ack();
	dat = IIC_Read_Byte(1);
	dat <<= 8;
	dat += IIC_Read_Byte(1);
	
	IIC_Read_Byte(0); // crc���ݣ���ȥ
	IIC_Stop();
	return (dat);
}

//��ʼ��SGP30
void SGP30_Init(void)
{
	SGP30_Send_Command(0x20, 0x03); //���ͳ�ʼ������ Init_air_quality
	IIC_Stop();
	SGP30_Inited = 0;

	Delay_ms(100);
}

// SGP30��оƬ��ȡ��ֵ ��ʼ����Ϊ0 ��ʼ���Ϊ1
u8 SGP30_read_result()
{
	u32 sgp30_dat;

	SGP30_Send_Command(0x20, 0x08); // Measure_air_quality

	sgp30_dat = SGP30_Read_DWord();

	// printf("%X\n", sgp30_dat);

	CO2Data = (sgp30_dat & 0xffff0000) >> 16;
	TVOCData = sgp30_dat & 0x0000ffff;
	// SGP30ģ�鿪����Ҫһ��ʱ���ʼ�����ڳ�ʼ���׶ζ�ȡ��CO2Ũ��Ϊ400ppm��TVOCΪ0ppd�Һ㶨���䣬����ϵ��ÿ��һ��ʱ���ȡһ��
	// SGP30ģ���ֵ�����CO2Ũ��Ϊ400ppm��TVOCΪ0ppd�����͡����ڼ����...����ֱ��SGP30ģ���ʼ����ɡ�
	//��ʼ����ɺ�տ�ʼ�������ݻᲨ���Ƚϴ�������������һ��ʱ�����������ȶ���
	//�����ഫ�����Ƚ������ܻ���Ӱ�죬�������ݳ��ֲ����������ģ�����������˲�������
	// printf("CO2:%dppm TVOC:%dppd", CO2Data, TVOCData);
	if (SGP30_Inited == 0)
	{
		if (CO2Data != 400 || TVOCData != 0)
		{
			SGP30_Inited = 1; //оƬ��ʼ�����
		}
		else
		{
			return 0;
		}
	}

	return 1;
}

//��ȡSGP30�Ķ�����̼����
u32 SGP30_GetCO2Data(void)
{
	return CO2Data;
}

//��ȡSGP30��TVOC����
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
	printf("\nSGP�Լ췵��:%X\n", rec);
}
