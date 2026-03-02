#include "ad511x.h"

// 引入外部定义的 I2C 句柄
extern I2C_HandleTypeDef hi2c2;

// 初始化数字电位器
HAL_StatusTypeDef AD511x_Init(void) {
    uint8_t init_data = 0x00;
    return HAL_I2C_Master_Transmit(&hi2c2, AD511X_I2C_ADDRESS, &init_data, 1, HAL_MAX_DELAY);
}

// 设置游标值
HAL_StatusTypeDef AD511x_SetWiper(uint8_t wiper_value) {
    uint8_t data[2];
    data[0] = 0x02;       // 写命令
    data[1] = wiper_value;  // 设置游标值

    return HAL_I2C_Master_Transmit(&hi2c2, AD511X_I2C_ADDRESS, data, 2, HAL_MAX_DELAY);
}

HAL_StatusTypeDef AD511x_ReadWiper(uint8_t *wiper_value) {
    // 第一步：向器件发送回读命令
    uint8_t read_command[2] = {0x05, 0x00}; // 假设命令字节为 0x06，后续字节设为 0
    HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&hi2c2, AD511X_I2C_ADDRESS, read_command, 2, HAL_MAX_DELAY);
    
    if (status != HAL_OK) {
        return status; // 如果写入回读命令失败，直接返回错误状态
    }

    // 第二步：读取两个字节的数据（16 位）
    uint8_t read_data[2];
    status = HAL_I2C_Master_Receive(&hi2c2, AD511X_I2C_ADDRESS, read_data, 2, HAL_MAX_DELAY);

    if (status == HAL_OK) {
        
        // 提取 16 位中的高 8 位为 RDAC 数据位
        *wiper_value = read_data[0];
    }

    return status;
}

// 将当前游标设置保存到 EEPROM
HAL_StatusTypeDef AD511x_SaveToEEPROM(void) {
    uint8_t save_command = 0x01;  // 保存命令
    return HAL_I2C_Master_Transmit(&hi2c2, AD511X_I2C_ADDRESS, &save_command, 1, HAL_MAX_DELAY);
}

// 软件关断功能
HAL_StatusTypeDef AD511x_SoftwareShutdown(uint8_t shutdown_state) {
    if (shutdown_state != 0 && shutdown_state != 1) {
        // 关断状态只能是0（关闭）或1（开启）
        return HAL_ERROR;
    }
		uint8_t data[2];
    data[0] = 0x03; // 假设此命令用于控制关断功能
    data[1] = shutdown_state; // 设置 MSB 为 0 或 1，其余部分留空

    return HAL_I2C_Master_Transmit(&hi2c2, AD511X_I2C_ADDRESS, data, 2, HAL_MAX_DELAY);
}
