/*
 * Copyright (c) 2016-2020, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef ARCH_H
#define ARCH_H

#define VBAR		p15, 0, c12, c0, 0
#define SCTLR		p15, 0, c1, c0, 0
#define SCTLR_I_BIT		((1) << 12)
#define SCTLR_V_BIT		((1) << 13)
#define SCTLR_DSSBS_BIT		((1) << 31)

#define MODE32_MASK		(0x1f)

#define CTR_DMINLINE_SHIFT	16
#define CTR_DMINLINE_WIDTH	4

#define DCIMVAC		p15, 0, c7, c6, 1
#define CTR		p15, 0, c0, c0, 1

#endif /* ARCH_H */
