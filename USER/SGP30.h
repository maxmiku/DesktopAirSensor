#ifndef __SGP30_H
#define	__SGP30_H
#include "delay.h"
#include "sys.h"

#define SGP30_Addr  0x58  //SGP30地址

#define write 0
#define read  1

void SGP30_Init(void);		//SGP30初始化
u8 SGP30_read_result(void);	//SGP30更新数据

u32 SGP30_GetCO2Data(void);	//获取SGP30的二氧化碳数据
u32 SGP30_GetTVOCData(void);//获取SGP30的TVOC数据
void SGP30_SelfCheck(void);		//SGP30自检 正常返回0xD400

#endif /* __SGP30_H */
