/**
 * I2C_soft.c
 * @tingzhong666
 * 2024-04-01 11:50:42
 */
#include <I2C_soft.h>
#define I2C_soft_SCL_IO GPIOA
#define I2C_soft_SCL_IO_PIN GPIO_PIN_8

#define I2C_soft_SDA_IO GPIOA
#define I2C_soft_SDA_IO_PIN GPIO_PIN_9

void SCL(GPIO_PinState v)
{
    HAL_GPIO_WritePin(I2C_soft_SCL_IO, I2C_soft_SCL_IO_PIN, v);
}

void SDA(GPIO_PinState v)
{
    HAL_GPIO_WritePin(I2C_soft_SDA_IO, I2C_soft_SDA_IO_PIN, v);
}

void SDA_IN()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = I2C_soft_SDA_IO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(I2C_soft_SDA_IO, &GPIO_InitStruct);
}

void SDA_OUT()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = I2C_soft_SDA_IO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(I2C_soft_SDA_IO, &GPIO_InitStruct);
}

GPIO_PinState SDA_GET()
{
    return HAL_GPIO_ReadPin(I2C_soft_SDA_IO, I2C_soft_SDA_IO_PIN);
}

// 开始
void I2C_soft_start()
{
    SCL(GPIO_PIN_SET);
    SDA_OUT();
    SDA(GPIO_PIN_SET);
}
// 停止
// 应答
// 非应答
// 等待应答
// 发送数据
// 接收数据
