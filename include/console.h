/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2021 hey <hyyoxhk@163.com>
 *
 */

#ifndef __CONSOLE_H
#define __CONSOLE_H

#define REGSZ 4

#define CONSOLE_T_NEXT			((0) * REGSZ)
#define CONSOLE_T_FLAGS			((1) * REGSZ)
#define CONSOLE_T_PUTC			((2) * REGSZ)
#define CONSOLE_T_GETC			((3) * REGSZ)
#define CONSOLE_T_FLUSH			((4) * REGSZ)
#define CONSOLE_T_BASE			((5) * REGSZ)
#define CONSOLE_T_DRVDATA		((6) * REGSZ)

#define CONSOLE_FLAG_BOOT		((1) << 0)
#define CONSOLE_FLAG_RUNTIME		((1) << 1)
#define CONSOLE_FLAG_CRASH		((1) << 2)
/* Bits 3 to 7 reserved for additional scopes in future expansion. */
#define CONSOLE_FLAG_SCOPE_MASK		(((1) << 8) - 1)
/* Bits 8 to 31 for non-scope use. */
#define CONSOLE_FLAG_TRANSLATE_CRLF	((1) << 8)

/* Returned by getc callbacks when receive FIFO is empty. */
#define ERROR_NO_PENDING_CHAR		(-1)
/* Returned by console_xxx() if no registered console implements xxx. */
#define ERROR_NO_VALID_CONSOLE		(-128)

#include <linux/types.h>

typedef struct console {
	struct console *next;
	/*
	 * Only the low 32 bits are used. The type is uintptr_t to align the
	 * fields of the struct to 64 bits in AArch64 and 32 bits in AArch32
	 */
	uintptr_t flags;
	int (*putc)(int character, struct console *console);
	int (*getc)(struct console *console);
	int (*flush)(struct console *console);
	uintptr_t base;
	/* Additional private driver data may follow here. */
} console_t;

#define CONFIG_DEBUG_UART_BASE 0x13820000

int console_register(uintptr_t baseaddr, uint32_t clock, uint32_t baud, console_t *console);

int console_putc(int c, console_t *console);

void uart_config(int peripheral);

#endif /* __CONSOLE_H */
