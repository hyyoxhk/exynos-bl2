/* SPDX-License-Identifier: MIT */
/*
 * Copyright (C) 2010 Texas Instruments, Inc.
 * Copyright (C) 2012 Samsung Electronics.
 * Copyright (C) 2022 He Yong.
 *
 * Ported from Linux - arch/arm/mach-exynos/exynos-smc.S
 */

#include <asm_macros.S>

	.globl	exynos_smc

/*
 * Function signature: void exynos_smc(u32 cmd, u32 arg1, u32 arg2, u32 arg3)
 */
	.arch armv7-a
	.arch_extension sec
func exynos_smc
	stmfd	sp!, {r4-r11, lr}
	dsb
	smc	#0
	ldmfd	sp!, {r4-r11, pc}
endfunc exynos_smc