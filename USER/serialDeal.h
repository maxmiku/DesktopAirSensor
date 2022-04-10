#ifndef __SERIALDEAL_H
#define	__SERIALDEAL_H

#include "stm32f10x.h"

//串口接收中断传入的数据
void s_receive(char recData);
//串口发送字符串数据
void s_sendStr(char *sdata, uint8_t len);

#endif /* __SERIALDEAL_H */
