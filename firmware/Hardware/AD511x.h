#ifndef AD511X_H
#define AD511X_H

#include "stm32f1xx_hal.h"


// 定义 AD511x 的 I2C 地址（请根据实际情况确认）
#define AD511X_I2C_ADDRESS (0x2F << 1)

// 函数声明
HAL_StatusTypeDef AD511x_Init(void);
HAL_StatusTypeDef AD511x_SetWiper(uint8_t wiper_value);
HAL_StatusTypeDef AD511x_ReadWiper(uint8_t *wiper_value);
HAL_StatusTypeDef AD511x_SaveToEEPROM(void);
HAL_StatusTypeDef AD511x_SoftwareShutdown(uint8_t shutdown_state);

#endif // AD511X_H
