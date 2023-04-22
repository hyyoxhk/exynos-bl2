/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2023 He Yong <hyyoxhk@163.com>
 *
 */

#include <linux/types.h>
#include <asm/io.h>
#include <asm/power.h>

#define EXYNOS4X12_POWER_BASE		0x10020000

void set_ps_hold_ctrl(void)
{
	struct exynos4x12_power *power = 
		(struct exynos4x12_power *)EXYNOS4X12_POWER_BASE;

	/* value: 1000000000B */
	setbits_le32(&power->ps_hold_control, EXYNOS_PS_HOLD_CONTROL_DATA_HIGH);

	/**
	 * GPX0PUD register
	 *
	 * 0x0 = Disables Pull-up/Pull-down
	 * 0x1 = Enables Pull-down
	 * 0x2 = Reserved
	 * 0x3 = Enables Pull-up
	 */
	writel(0x3, (unsigned int *)0x11000c08);
}

unsigned int get_boot_mode(void)
{
	unsigned int om_pin = EXYNOS4X12_POWER_BASE;

	return readl(om_pin) & OM_PIN_MASK;
}
