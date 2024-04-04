/**
 * I2C_soft.c
 * @tingzhong666
 * 2024-04-01 11:50:42
 */
#include <I2C_soft.h>

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
    SDA_OUT();
    SDA(GPIO_PIN_SET);
    SCL(GPIO_PIN_SET);
    delay_1us(5);
    SDA(GPIO_PIN_RESET);
    delay_1us(5);
    SCL(GPIO_PIN_RESET);
}
// 停止
void I2C_soft_stop()
{
    SDA_OUT();
    SDA(GPIO_PIN_RESET);
    SCL(GPIO_PIN_SET);
    delay_1us(5);
    SDA(GPIO_PIN_SET);
    delay_1us(5);
}
// 应答
void I2C_soft_ack()
{
    SDA_OUT();
    SDA(GPIO_PIN_RESET);
    SCL(GPIO_PIN_SET);
    delay_1us(5);
    SCL(GPIO_PIN_RESET);
}
// 非应答
void I2C_soft_nack()
{
    SDA_OUT();
    SDA(GPIO_PIN_SET);
    SCL(GPIO_PIN_SET);
    delay_1us(5);
    SCL(GPIO_PIN_RESET);
}
// 等待应答 1 ack -1 nack
int I2C_soft_awaitAck()
{
    SDA_OUT();
    SDA(GPIO_PIN_SET);
    SDA_IN();
    delay_1us(5);
    SCL(GPIO_PIN_SET);
    delay_1us(5);
    for (int i = 10; i--;)
    {
        // 应答
        if (HAL_GPIO_ReadPin(I2C_soft_SDA_IO, I2C_soft_SDA_IO_PIN) == GPIO_PIN_RESET)
        {
            SDA_OUT();
            SCL(GPIO_PIN_RESET);
            return 1;
        }
        delay_1us(5);
    }
    // 非应答
    I2C_soft_stop();
    return -1;
}
// 发送数据
void I2C_soft_sendByte(uint8_t data)
{
    SDA_OUT();

    for (int i = 8; i--;)
    {
        SCL(GPIO_PIN_RESET);
        SDA((GPIO_PinState)((data & 0x80) >> 7));
        SCL(GPIO_PIN_SET);
        delay_1us(5);
        data <<= 1;
    }
    SCL(GPIO_PIN_RESET);
}

// 接收数据
uint8_t I2C_soft_recByte()
{
    uint8_t res = 0;
    SDA_IN();
    for (int i = 8; i--;)
    {
        res <<= 1;
        SCL(GPIO_PIN_RESET);
        delay_1us(5);
        SCL(GPIO_PIN_SET);
        delay_1us(5);
        res |= SDA_GET();
    }
    SCL(GPIO_PIN_RESET);
    SDA_OUT();
    return res;
}
