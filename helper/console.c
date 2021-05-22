/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2021 hey <hyyoxhk@163.com>
 *
 */

#include <console.h>

int console_putc(int c)
{
	console_t console;

	console.base = CONFIG_DEBUG_UART_BASE;
	return console_s5p_putc(c, &console);
}
