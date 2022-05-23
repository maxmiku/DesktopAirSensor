#include "SHT30.h"
#include "IICUtils.h"
#include "stdio.h"

#define write 0
#define read 1

float Temperature = 0;
float Humidity = 0;

float humiture[4];
// char humiture_buff1[20];

/**
 * @brief ����sht30
 *
 * @param addr оƬ��ַ Ĭ��0x44
 */
void SHT30_Init(u8 addr) {
    IIC_Start();
    IIC_Send_Byte(addr << 1 | write);  //д7λI2C�豸��ַ��0��Ϊдȡλ,1Ϊ��ȡλ
    IIC_Wait_Ack();
    IIC_Send_Byte(0x30);
    IIC_Wait_Ack();
    IIC_Send_Byte(0xA2);
    IIC_Wait_Ack();
    IIC_Stop();
}

/*******************************************************************
 ��ʪ�Ȼ�ȡ����
����ԭ��: SHT30_read_result(u8 addr);
����: �������մ������ɼ����ϳ���ʪ��
����0��Ч 1��Ч
********************************************************************/
uint8_t SHT30_read_result(u8 addr) {
    u16 tem, hum;
    u16 buff[6];

    // printf("iic_start");

    IIC_Start();
    // printf("iic_start_success");

    IIC_Send_Byte(addr << 1 | write);  //д7λI2C�豸��ַ��0��Ϊдȡλ,1Ϊ��ȡλ
    // printf("sht_���͵�ַ");
    IIC_Wait_Ack();
    IIC_Send_Byte(0x2C);
    // printf("sht_��ʼ��1");

    IIC_Wait_Ack();
    IIC_Send_Byte(0x06);  //����ʱ�Ӹ���
    // printf("sht_��ʼ��2");

    IIC_Wait_Ack();
    IIC_Stop();
    Delay_ms(50);

    // printf("SHT��ʼ���ɹ�!");

    IIC_Start();
    IIC_Send_Byte(addr << 1 | read);  //д7λI2C�豸��ַ��0��Ϊдȡλ,1Ϊ��ȡλ
    if (IIC_Wait_Ack() == 0) {
        buff[0] = IIC_Read_Byte(1);
        buff[1] = IIC_Read_Byte(1);
        buff[2] = IIC_Read_Byte(1);
        buff[3] = IIC_Read_Byte(1);
        buff[4] = IIC_Read_Byte(1);
        buff[5] = IIC_Read_Byte(0);
        IIC_NAck();
        IIC_Stop();
    }

    tem = ((buff[0] << 8) | buff[1]);  //�¶�ƴ��
    hum = ((buff[3] << 8) | buff[4]);  //ʪ��ƴ��

    printf("��ʪ��ԭʼ���ݣ�%x[%x]  %x[%x]\n", tem, buff[2], hum, buff[5]);

    /*ת��ʵ���¶�*/
    Temperature = (175.0 * (float)tem / 65535.0 - 45.0);  // T = -45 + 175 * tem / (2^16-1)
    Humidity = (100.0 * (float)hum / 65535.0);            // RH = hum*100 / (2^16-1)
    printf("ȡ����ʪ�ȣ�%6.2f*C %6.2f%%\n", Temperature, Humidity);

    if ((Temperature >= -20) && (Temperature <= 125) && (Humidity >= 0) && (Humidity <= 100))  //���˴�������
    {
        if (tem != 0x7fff && tem != 0x0000) {
            humiture[0] = Temperature;
        } else {
            printf("Temperature Error ignore.\n");
			return 0;
        }

        if (hum != 0xffff && hum != 0x0000) {
            humiture[2] = Humidity;
        } else {
            printf("Humidity Error ignore.\n");
			return 0;
        }

        // sprintf(humiture_buff1,"%6.2f*C %6.2f%%",Temperature,Humidity);//111.01*C 100.01%������2λС����
    }

    hum = 0;
    tem = 0;
	return 1;
}

float SHT30_GetTemperature() {
    return humiture[0];
}

float SHT30_GetHumidity() {
    return humiture[2];
}
