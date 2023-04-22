/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2021 hey <hyyoxhk@163.com>
 *
 */

#include <stdio.h>
#include <console.h>

extern console_t console;

int putchar(int c)
{
	int res;
	if (console_putc((unsigned char)c, &console) >= 0)
		res = c;
	else
		res = EOF;

	return res;
}
