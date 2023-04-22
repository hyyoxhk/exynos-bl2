/*
 * Copyright (c) 2015-2020, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef S5P_UART_REGS_H
#define S5P_UART_REGS_H

#define ULCON		(0x00)
#define UCON		(0x04)
#define UFCON		(0x08)
#define UMCON		(0x0C)
#define UTRSTAT		(0x10)
#define UERSTAT		(0x14)
#define UFSTAT		(0x18)
#define UMSTAT		(0x1C)
#define UTXH		(0x20)
#define URXH		(0x24)
#define UBRDIV		(0x28)
#define UFRACVAL	(0x2C)
#define UINTP		(0x30)
#define UINTSP		(0x34)
#define UINTM		(0x38)

#define TX_FIFO_FULL		(1 << 24)

#endif /* S5P_UART_REGS_H */
