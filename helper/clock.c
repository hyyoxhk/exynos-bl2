/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2021 hey <hyyoxhk@163.com>
 *
 */

#include <linux/types.h>
#include <asm/io.h>
#include <asm/clock.h>

#define EXYNOS4X12_CLOCK_BASE		0x10030000

void system_clock_init(void)
{

	struct exynos4x12_clock *clk = (struct exynos4x12_clock *)EXYNOS4X12_CLOCK_BASE;

	/* Set PDIV, MDIV, and SDIV values (Refer to (A, M, E, V)
	 * Change other PLL control values
	 */
	writel(CLK_DIV_CPU0_VAL, &clk->div_cpu0);
	writel(CLK_DIV_CPU1_VAL, &clk->div_cpu1);
	writel(CLK_DIV_DMC0_VAL, &clk->div_dmc0);
	writel(CLK_DIV_DMC1_VAL, &clk->div_dmc1);
	writel(CLK_DIV_TOP_VAL, &clk->div_top);
	writel(CLK_DIV_LEFTBUS_VAL, &clk->div_leftbus);
	writel(CLK_DIV_RIGHTBUS_VAL, &clk->div_rightbus);
	writel(CLK_DIV_PERIL0_VAL, &clk->div_peril0);
	writel(CLK_DIV_FSYS0_VAL, &clk->div_fsys0);
	writel(CLK_DIV_FSYS1_VAL, &clk->div_fsys1);
	writel(CLK_DIV_FSYS2_VAL, &clk->div_fsys2);
	writel(CLK_DIV_FSYS3_VAL, &clk->div_fsys3);

	/* Set K, AFC, MRR, MFR values if necessary
	 * (Refer to (A, M, E, V)PLL_CON1 SFRs)
	 * Turn on a PLL (Refer to (A, M, E, V) PLL_CON0 SFRs)
	 */
	writel(APLL_CON1_VAL, &clk->apll_con1);
	writel(APLL_CON0_VAL, &clk->apll_con0);
	writel(MPLL_CON1_VAL, &clk->mpll_con1);
	writel(MPLL_CON0_VAL, &clk->mpll_con0);
	writel(EPLL_CON2_VAL, &clk->epll_con2);
	writel(EPLL_CON0_VAL, &clk->epll_con0);
	writel(VPLL_CON2_VAL, &clk->vpll_con2);
	writel(VPLL_CON0_VAL, &clk->vpll_con0);

	/* Wait until the PLL is locked */
	writel(APLL_LOCKTIME, &clk->apll_lock);
	writel(MPLL_LOCKTIME, &clk->mpll_lock);
	writel(EPLL_LOCKTIME, &clk->epll_lock);
	writel(VPLL_LOCKTIME, &clk->vpll_lock);

	/* Select the PLL output clock instead of input reference clock,
	 * after PLL output clock is stabilized.
	 * (Refer to CLK_SRC_CPU SFR for APLL and MPLL,
	 * CLK_SRC_TOP0 for EPLL and VPLL)
	 * Once a PLL is turned on, do not turn it off.
	 */
	writel(CLK_SRC_CPU_VAL, &clk->src_cpu);
	writel(CLK_SRC_DMC_VAL, &clk->src_dmc);
	writel(CLK_SRC_TOP0_VAL, &clk->src_top0);
	writel(CLK_SRC_TOP1_VAL, &clk->src_top1);
	writel(CLK_SRC_LEFTBUS_VAL, &clk->src_leftbus);
	writel(CLK_SRC_RIGHTBUS_VAL, &clk->src_rightbus);
	writel(CLK_SRC_PERIL0_VAL, &clk->src_peril0);
	writel(CLK_SRC_FSYS_VAL, &clk->src_fsys);
}
