/**
 * sht20.c
 * @tingzhong666
 * 2024-04-03 13:49:12
 */
#include <sht20.h>
#define I2C HARDWARE
// #define I2C SOFTWARE

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
#if I2C == HARDWARE
    HAL_I2C_Master_Transmit(&hi2c1, 0x80, rec, 1, 0xffff);
    // sht20_MeasurementAwait(t);
    HAL_I2C_Master_Receive(&hi2c1, 0x81, rec, 3, 0xffff);
#elif I2C == SOFTWARE
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
