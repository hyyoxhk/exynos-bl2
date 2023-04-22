/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2021 hey <hyyoxhk@163.com>
 *
 */

#ifndef __STDIO_H
#define __STDIO_H

#include <stdarg.h>

#define EOF -1

int puts(const char *s);

int putchar(int c);

int vprintf(const char *fmt, va_list args);

#endif /* __STDIO_H */
