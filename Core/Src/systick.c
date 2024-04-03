/**
 * systick.c
 * @tingzhong666
 * 2024-04-02 14:33:42
 */
#include <systick.h>

volatile uint32_t systick_count = 0;

HAL_StatusTypeDef systick_init()
{
    if (HAL_SYSTICK_Config(SystemCoreClock / 1000000) > 0U)
    {
        return HAL_ERROR;
    }
    return HAL_OK;
}

void systick_increment()
{
    if (systick_count > 0)
    {
        systick_count--;
    }
}

void delay_1us(uint32_t us)
{
    systick_count = us;
    while (systick_count > 0)
        ;
}

void delay_1ms(uint32_t ms)
{
    while (ms--)
        delay_1us(1000);
}
