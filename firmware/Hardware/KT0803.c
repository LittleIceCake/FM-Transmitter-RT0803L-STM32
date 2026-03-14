#include "KT0803.h"

// 引入外部定义的 I2C 句柄
extern I2C_HandleTypeDef hi2c2;

static HAL_StatusTypeDef KT0803L_WriteREG(uint8_t dat,uint8_t addr) {

    HAL_StatusTypeDef status = HAL_I2C_Mem_Write(&hi2c2, KT0803L_I2C_ADDRESS,addr,I2C_MEMADD_SIZE_8BIT,&dat, 1, HAL_MAX_DELAY);
    return status;
}

HAL_StatusTypeDef KT0803L_ReadREG(uint8_t *wiper_value,uint8_t addr) {

    
    uint8_t read_data;
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c2, KT0803L_I2C_ADDRESS,addr,I2C_MEMADD_SIZE_8BIT,&read_data, 1, HAL_MAX_DELAY);

    if (status == HAL_OK) {
        
        *wiper_value = read_data;
    }

    return status;
}


uint8_t KT0803L_FREQ_SET(float Rreq){
    if(Rreq<70||Rreq>108)
        return 0;
    uint8_t temp;
    temp = (uint16_t)(Rreq*20)>>1;
    KT0803L_WriteREG(temp,0x00);
    temp = 0xC0|((uint16_t)(Rreq*20)>>9);
    KT0803L_WriteREG(temp,0x01);
    temp = 0x40|(((uint16_t)(Rreq*20)&0x01)<<7);
    KT0803L_WriteREG(temp,0x02);
    KT0803L_WriteREG(0x00,0x0B);
    return 1;
}