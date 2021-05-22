#include <led.h>

/**
 * LED的GPIO
 */
#define     LED_GPIO_CON      (0x11000100)
#define     LED_GPIO_DATA     (0x11000104)
#define     LED_INDEX         (0x0)

/**
 * 打开LED灯
 * @return  0
 */
int std_lamp_on(void)
{
    volatile unsigned *con = (unsigned *)LED_GPIO_CON;
    volatile unsigned *data = (unsigned *)LED_GPIO_DATA;

    *con &= ~(1 << (LED_INDEX * 4));
    *con |= (1 << (LED_INDEX * 4));

    *data |= (1 << LED_INDEX);

    return 0;
}