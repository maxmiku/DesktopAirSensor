#ifndef __SERIALDEAL_H
#define	__SERIALDEAL_H

#include "stm32f10x.h"

//���ڽ����жϴ��������
void s_receive(char recData);
//���ڷ����ַ�������
void s_sendStr(char *sdata, uint8_t len);

#endif /* __SERIALDEAL_H */
