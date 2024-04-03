/**
 * I2C_soft.h
 * @tingzhong666
 * 2024-04-01 11:50:57
 */

#ifndef I2C_SOFT_H
#define I2C_SOFT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

    void I2C_soft_start(void);
    void I2C_soft_stop(void);
    void I2C_soft_ack(void);
    void I2C_soft_nack(void);
    int I2C_soft_awaitAck(void);
    void I2C_soft_sendByte(uint8_t data);
    uint8_t I2C_soft_recByte(void);

#ifdef __cplusplus
}
#endif

#endif
