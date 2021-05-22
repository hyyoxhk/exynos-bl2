/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2021 hey <hyyoxhk@163.com>
 *
 */

#ifndef __CONSOLE_H
#define __CONSOLE_H

#include <linux/types.h>

typedef struct console {
	struct console *next;
	/*
	 * Only the low 32 bits are used. The type is uintptr_t to align the
	 * fields of the struct to 64 bits in AArch64 and 32 bits in AArch32
	 */
	uintptr_t flags;
	int (*const putc)(int character, struct console *console);
	int (*const getc)(struct console *console);
	int (*const flush)(struct console *console);
	uintptr_t base;
	/* Additional private driver data may follow here. */
} console_t;

#define CONFIG_DEBUG_UART_BASE 0x13820000

int console_putc(int c);

int console_s5p_core_putc(int c, uintptr_t base_addr);

int console_s5p_register(uintptr_t baseaddr, uint32_t clock, uint32_t baud,
			   console_t *console);

int console_s5p_putc(int c, console_t *console);

#endif /* __CONSOLE_H */
