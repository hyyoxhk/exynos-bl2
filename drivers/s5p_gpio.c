
#include <asm/io.h>
#include <drivers/s5p_gpio.h>
#include <drivers/cpu.h>

#define S5P_GPIO_GET_PIN(x)	(x % GPIO_PER_BANK)

#define CON_MASK(val)		(0xf << ((val) << 2))
#define CON_SFR(gpio, cfg)	((cfg) << ((gpio) << 2))

#define PULL_MASK(gpio)		(0x3 << ((gpio) << 1))
#define PULL_MODE(gpio, pull)	((pull) << ((gpio) << 1))

#define EXYNOS4X12_GPIO_NUM_PARTS	8
static struct gpio_info exynos4x12_gpio_data[EXYNOS4X12_GPIO_NUM_PARTS] = {
	{ EXYNOS4X12_GPIO_PART1_0, EXYNOS4X12_GPIO_MAX_PORT_PART_1_0 },
	{ EXYNOS4X12_GPIO_PART1_1, EXYNOS4X12_GPIO_MAX_PORT_PART_1_1 },
	{ EXYNOS4X12_GPIO_PART1_2, EXYNOS4X12_GPIO_MAX_PORT_PART_1_2 },
	{ EXYNOS4X12_GPIO_PART2_1, EXYNOS4X12_GPIO_MAX_PORT_PART_2_1 },
	{ EXYNOS4X12_GPIO_PART2_2, EXYNOS4X12_GPIO_MAX_PORT_PART_2_2 },
	{ EXYNOS4X12_GPIO_PART2_3, EXYNOS4X12_GPIO_MAX_PORT_PART_2_3 },
	{ EXYNOS4X12_GPIO_PART3_BASE, EXYNOS4X12_GPIO_MAX_PORT_PART_3 },
	{ EXYNOS4X12_GPIO_PART4_BASE, EXYNOS4X12_GPIO_MAX_PORT },
};

static struct s5p_gpio_bank *s5p_gpio_get_bank(unsigned int gpio)
{
	const struct gpio_info *data = exynos4x12_gpio_data;
	unsigned int upto;
	int i, count = EXYNOS4X12_GPIO_NUM_PARTS;

	upto = 0;

	for (i = 0; i < count; i++) {
		if (gpio < data->max_gpio) {
			struct s5p_gpio_bank *bank;
			bank = (struct s5p_gpio_bank *)data->reg_addr;
			bank += (gpio - upto) / GPIO_PER_BANK;
			return bank;
		}

		upto = data->max_gpio;
		data++;
	}

	return NULL;
}

static void s5p_gpio_cfg_pin(struct s5p_gpio_bank *bank, int gpio, int cfg)
{
	unsigned int value;

	value = readl(&bank->con);
	value &= ~CON_MASK(gpio);
	value |= CON_SFR(gpio, cfg);
	writel(value, &bank->con);
}

static void s5p_gpio_set_pull(struct s5p_gpio_bank *bank, int gpio, int mode)
{
	unsigned int value;

	value = readl(&bank->pull);
	value &= ~PULL_MASK(gpio);

	switch (mode) {
	case S5P_GPIO_PULL_DOWN:
	case S5P_GPIO_PULL_UP:
		value |= PULL_MODE(gpio, mode);
		break;
	default:
		break;
	}

	writel(value, &bank->pull);
}

static int s5p_gpio_get_pin(unsigned gpio)
{
	return S5P_GPIO_GET_PIN(gpio);
}

void gpio_set_pull(int gpio, int mode)
{
	s5p_gpio_set_pull(s5p_gpio_get_bank(gpio),
			  s5p_gpio_get_pin(gpio), mode);
}

void gpio_cfg_pin(int gpio, int cfg)
{
	s5p_gpio_cfg_pin(s5p_gpio_get_bank(gpio),
			 s5p_gpio_get_pin(gpio), cfg);
}
