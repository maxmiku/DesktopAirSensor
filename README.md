# DesktopAirSensor
A wireless desktop air sensor base STM32

The project still working!

Notice: The document will be written in Chinese. If you can't understand Chinese, you can use [Google Translate](https://translate.google.com), thank you.

------

## 引脚定义

### 串口插座

| GPIO | 芯片IO | 描述                 |
| ---- | ------ | -------------------- |
| PA9  | Tx(2)  | USART1_TX            |
| PA10 | Rx(3)  | USART1_RX            |
| GND  | G(1)   | 数字地               |
| 3V3  | VCC(4) | 外部输入3.3V供电接口 |

### ESP8266

| GPIO | 芯片IO  | 描述      |
| ---- | ------- | --------- |
| PA3  | ESP_TXD | USART2_RX |
| PA2  | ESP_RXD | USART2_TX |
| GND  | GND     | 数字地    |
| 3V3  | VCC     | 供电      |

### 板载元件

| GPIO | 外设IO | 描述 |
| ---- | ------ | ---- |
| PC13 | LED    |      |
| PA0  | 按钮   |      |

### 拨码开关

| GPIO | 芯片IO | 描述     |
| ---- | ------ | -------- |
| PB12 | CLK    | 时钟     |
| PB14 | DT     | 数据     |
| PB15 | SW     | 按下按钮 |
| GND  | GND    | 数字地   |
| 3V3  | VCC    | 供电     |

### SHT30 SGP30

| GPIO | 芯片IO | 描述     |
| ---- | ------ | -------- |
| PB6  | SCL    | 时钟     |
| PB7  | SDA    | 数据总线 |
| GND  | GND    | 数字地   |
| 3V3  | VCC    | 供电     |