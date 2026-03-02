#ifndef KT0803L_H
#define KT0803L_H

#include "stm32f1xx_hal.h"


// 定义 KT0803L 的 I2C 地址（请根据实际情况确认）
#define KT0803L_I2C_ADDRESS (0x3E << 1)

uint8_t KT0803L_FREQ_SET(float Rreq);
HAL_StatusTypeDef KT0803L_ReadREG(uint8_t *wiper_value,uint8_t addr);
#endif 