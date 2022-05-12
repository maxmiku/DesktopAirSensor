#ifndef SHT30_H
#define SHT30_H
#include "delay.h"
#include "stdio.h"
#include "string.h"
#include "sys.h"
#include "usart1.h"

extern char humiture_buff1[20];
uint8_t SHT30_read_result(u8 addr);
float SHT30_GetTemperature(void);
float SHT30_GetHumidity(void);
void SHT30_Init(u8 addr);

#endif
