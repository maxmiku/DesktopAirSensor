#ifndef SHT30_H
#define SHT30_H
#include "delay.h"
#include "sys.h"
#include "stdio.h"
#include "usart1.h"
#include "string.h"

extern char humiture_buff1[20];
void SHT30_read_result(u8 addr);
float SHT30_GetTemperature(void);
float SHT30_GetHumidity(void);
 
#endif

