/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2021 hey <hyyoxhk@163.com>
 *
 */
 
#include <asm_macros.S>
#include <console_macros.S>
#include <drivers/s5p_console.h>
#include <drivers/s5p_uart_regs.h>

	/*
	 * "core" functions are low-level implementations that don't require
	 * writeable memory and are thus safe to call in BL1 crash context.
	 */
	.globl	console_s5p_core_init
	.globl	console_s5p_core_putc
	.globl	console_s5p_core_getc
	.globl	console_s5p_core_flush

	.globl	console_s5p_putc
	.globl	console_s5p_flush

	/* -----------------------------------------------------------------
	 * int console_s5p_core_init(uintptr_t base_addr,
	 *			 unsigned int uart_clk,
	 *			 unsigned int baud_rate)
	 *
	 * Function to initialize the console without a C Runtime to print
	 * debug information. This function will be accessed by console_init
	 * and crash reporting.
	 *
	 * In: r0 - console base address
	 *     r1 - Uart clock in Hz
	 *     r2 - Baud rate
	 * Out: return 1 on success else 0 on error
	 * Clobber list : r1, r2, r3
	 * -----------------------------------------------------------------
	 */
func console_s5p_core_init
	/* Check the input base address */
	cmp	r0, #0
	beq	core_init_fail
#if defined(IMAGE_BL2)
	/* Check baud rate and uart clock for sanity */
	cmp	r1, #0
	beq	core_init_fail
	cmp	r2, #0
	beq	core_init_fail
	/* enable FIFOs, auto clear Rx FIFO */
	mov	r3, #0x3
	str	r3, [r0, #UFCON]
	mov	r3, #0x0 
	str	r3, [r0, #UMCON]
	/* 8N1 */
	mov	r3, #0x3
	str	r3, [r0, #ULCON]
	/* No interrupts, no DMA, pure polling */
	mov	r3, #0x245
	str	r3, [r0, #UCON]
	/* DIV_VAL = (SCLK_UART / (bps * 16)) - 1 */
	udiv	r3, r1, r2
	udiv	r3, r3, #0x10
	sub	r3, r3, #0x1
	str	r3, [r0, #UBRDIV]
#endif /* IMAGE_BL2 */
	mov	r0, #1
	bx	lr
core_init_fail:
	mov	r0, #0
	bx	lr
endfunc console_s5p_core_init

	.globl	console_s5p_register

	/* -------------------------------------------------------
	 * int console_s5p_register(uintptr_t baseaddr,
	 *     uint32_t clock, uint32_t baud,
	 *     console_t *console);
	 * Function to initialize and register a new samsung_s5p
	 * console. Storage passed in for the console struct
	 * *must* be persistent (i.e. not from the stack).
	 * In: r0 - UART register base address
	 *     r1 - UART clock in Hz
	 *     r2 - Baud rate
	 *     r3 - pointer to empty console_t struct
	 * Out: return 1 on success, 0 on error
	 * Clobber list : r0, r1, r2
	 * -------------------------------------------------------
	 */
func console_s5p_register
	push	{r4, lr}
	mov	r4, r3
	cmp	r4, #0
	beq	register_fail
	str	r0, [r4, #CONSOLE_T_BASE]

	bl console_s5p_core_init
	cmp	r0, #0
	beq	register_fail

	mov	r0, r4
	pop	{r4, lr}
	finish_console_register s5p putc=1, getc=0, flush=1

register_fail:
	pop	{r4, pc}
endfunc console_s5p_register

	/* ---------------------------------------------------------------
	 * int console_s5p_core_putc(int c, uintptr_t base_addr)
	 *
	 * Function to output a character over the console. It returns the
	 * character printed on success or -1 on error.
	 *
	 * In : r0 - character to be printed
	 *      r1 - console base address
	 * Out : return -1 on error else return character.
	 * Clobber list : r2
	 * ---------------------------------------------------------------
	 */
func console_s5p_core_putc
	/* Check the input parameter */
	cmp	r1, #0
	beq	putc_error
	ldr	r2, [r1, #UFSTAT]
	tst	r2, #TX_FIFO_FULL
	beq	putc_error
	str	r0, [r1, #UTXH]
	bx	lr
putc_error:
	mov	r0, #-1
	bx	lr
endfunc console_s5p_core_putc

	/* --------------------------------------------------------
	 * int console_s5p_putc(int c, console_t *console)
	 * Function to output a character over the console. It
	 * returns the character printed on success or -1 on error.
	 * In : r0 - character to be printed
	 *      r1 - pointer to console_t structure
	 * Out : return -1 on error else return character.
	 * Clobber list : r2
	 * --------------------------------------------------------
	 */
func console_s5p_putc
#if ENABLE_ASSERTIONS
	cmp	r1, #0
	ASM_ASSERT(ne)
#endif /* ENABLE_ASSERTIONS */
	ldr	r1, [r1, #CONSOLE_T_BASE]
	b	console_s5p_core_putc
endfunc console_s5p_putc

	/* -----------------------------------------------------------
	 * int console_s5p_core_getc(uintptr_t base_addr)
	 *
	 * Function to get a character from the console.
	 * It returns the character grabbed on success or -1 on error.
	 *
	 * In : r0 - console base address
	 * Out : return -1.
	 * Clobber list : r0, r1
	 * -----------------------------------------------------------
	 */
func console_s5p_core_getc
	/* Not supported */
	mov	r0, #-1
	bx	lr
endfunc console_s5p_core_getc

	/* ---------------------------------------------------------------
	 * int console_s5p_core_flush(uintptr_t base_addr)
	 *
	 * Function to force a write of all buffered data that hasn't been
	 * output.
	 *
	 * In : r0 - console base address
	 * Out : return -1 on error else return 0.
	 * Clobber list : r0, r1
	 * ---------------------------------------------------------------
	 */
func console_s5p_core_flush
	cmp	r0, #0
	beq	flush_error
fifo_lopp:
	ldr	r1, [r0, #UFSTAT]
	tst	r1, #TX_FIFO_FULL
	beq	fifo_lopp
	mov	r0, #0
	bx	lr
flush_error:
	mov	r0, #-1
	bx	lr
endfunc console_s5p_core_flush

	/* ------------------------------------------------------
	 * int console_stm32_flush(console_t *console)
	 * Function to force a write of all buffered
	 * data that hasn't been output.
	 * In : r0 - pointer to console_t structure
	 * Out : return -1 on error else return 0.
	 * Clobber list: r0, r1
	 * ------------------------------------------------------
	 */
func console_s5p_flush
#if ENABLE_ASSERTIONS
	cmp	r0, #0
	ASM_ASSERT(ne)
#endif /* ENABLE_ASSERTIONS */
	ldr	r0, [r0, #CONSOLE_T_BASE]
	b	console_s5p_core_flush
endfunc console_s5p_flush
