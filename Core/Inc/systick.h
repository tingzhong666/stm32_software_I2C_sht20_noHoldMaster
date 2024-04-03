/**
 * systick.h
 * @tingzhong666
 * 2024-04-02 14:34:04
 */

#ifndef SYSTICK_H
#define SYSTICK_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"
    HAL_StatusTypeDef systick_init(void);
    void systick_increment(void);
    void delay_1us(uint32_t us);
    void delay_1ms(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif
