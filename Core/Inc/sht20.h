/**
 * sht20.h
 * @tingzhong666
 * 2024-04-03 13:49:30
 */

#ifndef SHT20_H
#define SHT20_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"
#include "i2c.h"
#include "math.h"
#include "I2C_soft.h"

    typedef enum
    {
        temperature, // 温度
        humidity     // 湿度
    } MeasurementType;

    void sht20_init(void);
    double sht20_Tmeasurement_HM(MeasurementType);
    double sht20_Tmeasurement_NHM(MeasurementType t);

#ifdef __cplusplus
}
#endif

#endif
