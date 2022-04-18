#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"

void Delay_Init(void);
void Delay_us(__IO u32 nTime);
void Delay_ms(unsigned int ms);

#endif /* __DELAY_H */


