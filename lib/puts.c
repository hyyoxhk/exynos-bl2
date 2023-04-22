/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2021 hey <hyyoxhk@163.com>
 *
 */

#include <stdio.h>
#include <console.h>

int puts(const char *s)
{
	int count = 0;

	while (*s != '\0') {
		if (putchar(*s) == EOF)
			return EOF;
		s++;
		count++;
	}

	// if (putchar('\n') == EOF)
	// 	return EOF;

	return count + 1;
}
