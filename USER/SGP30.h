#ifndef __SGP30_H
#define	__SGP30_H
#include "delay.h"
#include "sys.h"

#define SGP30_Addr  0x58  //SGP30��ַ

#define write 0
#define read  1

void SGP30_Init(void);		//SGP30��ʼ��
u8 SGP30_read_result(void);	//SGP30��������

u32 SGP30_GetCO2Data(void);	//��ȡSGP30�Ķ�����̼����
u32 SGP30_GetTVOCData(void);//��ȡSGP30��TVOC����
void SGP30_SelfCheck(void);		//SGP30�Լ� ��������0xD400

#endif /* __SGP30_H */
