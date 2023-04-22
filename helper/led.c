#include <led.h>
#include <asm/io.h>

/**
 * LED的GPIO
 */
#define     LED_GPIO_CON      (0x11000100)
#define     LED_GPIO_DATA     (0x11000104)
#define     LED_INDEX         (0x0)

/**
 * 打开LED灯
 */
// void std_lamp_on(void)
// {
//     volatile unsigned *con = (unsigned *)LED_GPIO_CON;
//     volatile unsigned *data = (unsigned *)LED_GPIO_DATA;

//     *con &= ~(1 << (LED_INDEX * 4));
//     *con |= (1 << (LED_INDEX * 4));

//     *data |= (1 << LED_INDEX);

// }

void std_lamp_on(void)
{
	unsigned int *led2_con_addr=(unsigned int *)0x11000100;
	unsigned int *led2_data_addr=(unsigned int *)0x11000104;
	unsigned int value=readl(led2_con_addr);
	value |=0x1;
	writel(value,led2_con_addr);

	value=readl(led2_data_addr);
	value |=0x1;
	writel(value,led2_data_addr);
}
// -
// -void led2off(void)
// -{
// -	unsigned int *led2_con_addr=(unsigned int *)0x11000100;
// -	unsigned int *led2_data_addr=(unsigned int *)0x11000104;
// -	unsigned int value=readl(led2_con_addr);
// -	value |=0x1;
// -	writel(value,led2_con_addr);
// -
// -	value=readl(led2_data_addr);
// -	value &=0xfffffffe;
// -	writel(value,led2_data_addr);
// -
// -	return;
// -}
