/**
 * sht20.c
 * @tingzhong666
 * 2024-04-03 13:49:12
 */
#include <sht20.h>
#define I2C_SOFTWARE 1

// 測量精度
uint8_t MeasurementResolution_T = 14;
uint8_t MeasurementResolution_RH = 12;

void sht20_init()
{
    delay_1ms(15);
}

// 测量时间
void sht20_MeasurementAwait(MeasurementType t)
{
    switch (t)
    {
    case temperature:
        switch (MeasurementResolution_T)
        {
        case 14:
            delay_1ms(85);
            break;
        case 13:
            delay_1ms(43);
            break;
        case 12:
            delay_1ms(22);
            break;
        case 11:
            delay_1ms(11);
            break;

        default:
            break;
        }
        break;
    case humidity:
        switch (MeasurementResolution_RH)
        {
        case 12:
            delay_1ms(29);
            break;
        case 11:
            delay_1ms(15);
            break;
        case 10:
            delay_1ms(9);
            break;
        case 9:
            delay_1ms(4);
            break;

        default:
            break;
        }
        break;

    default:
        break;
    }
}

// 阻塞测量
double sht20_Tmeasurement_HM(MeasurementType t)
{
    uint8_t rec[3] = {0};
    uint16_t tmp = 0;
    volatile double res = 0;
    rec[0] = t == temperature ? 0xe3 : rec[0];
    rec[0] = t == humidity ? 0xe5 : rec[0];
#if I2C_SOFTWARE == 0
    return -1; // HAL库的API无法使用阻塞测量
#elif I2C_SOFTWARE == 1
#endif
    tmp = rec[0] << 8; // 高8
    tmp |= rec[1];     // 低8
    tmp >>= 2;         // 去掉状态位
    if (t == temperature)
        res = 175.72 * tmp / pow(2, 16) - 46.85;
    if (t == humidity)
        res = 128 * tmp / pow(2, 16) - 6;
    printf("sht20_Tmeasurement_HM tmp=0x%x rec[0]=0x%x rec[1]=0x%x\n", tmp, rec[0], rec[1]);
    return res;
}

// 异步测量
double sht20_Tmeasurement_NHM(MeasurementType t)
{
    uint8_t rec[3] = {0};
    uint16_t tmp = 0;
    volatile double res = 0;
    rec[0] = t == temperature ? 0xf3 : rec[0];
    rec[0] = t == humidity ? 0xf5 : rec[0];
#if I2C_SOFTWARE == 0
    HAL_I2C_Master_Transmit(&hi2c1, 0x80, rec, 1, 0xffff);
    sht20_MeasurementAwait(t);
    while (HAL_I2C_Master_Receive(&hi2c1, 0x81, rec, 3, 0xffff) == HAL_BUSY)
        ;
#elif I2C_SOFTWARE == 1
    // 开始
    I2C_soft_start();
    // 发送 地址写
    I2C_soft_sendByte(0X80);
    // 等待应答
    if (I2C_soft_awaitAck() == -1)
    {
        printf("err 1\n");
    }
    // 发送 读取指令
    I2C_soft_sendByte(rec[0]);
    // 等待应答
    if (I2C_soft_awaitAck() == -1)
    {
        printf("err 2\n");
    }
    // 轮训等待应答
    delay_1us(20);
    while (1)
    {
        // -开始
        I2C_soft_start();
        // -地址读
        I2C_soft_sendByte(0x81);
        // -等待应答 nack停止 ack跳出循环
        if (I2C_soft_awaitAck() == 1)
            break;
    }
    // 接收数据MSB
    rec[0] = I2C_soft_recByte();
    // ack
    I2C_soft_ack();
    // 接收数据LSB
    rec[1] = I2C_soft_recByte();
    // nacK
    I2C_soft_nack();
    // 停止
    I2C_soft_stop();

#endif
    tmp = rec[0] << 8; // 高8
    tmp |= rec[1];     // 低8
    tmp &= 0xffffc;    // 去掉状态位
    if (t == temperature)
        res = 175.72 * tmp / pow(2, 16) - 46.85;
    if (t == humidity)
        res = 125 * tmp / pow(2, 16) - 6;
    printf("sht20_Tmeasurement_HM tmp=0x%x rec[0]=0x%x rec[1]=0x%x\n", tmp, rec[0], rec[1]);
    return res;
}
