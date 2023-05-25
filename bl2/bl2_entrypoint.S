/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2016-2019, ARM Limited and Contributors. All rights reserved.
 *
 */

#include <arch.h>
#include <asm_macros.S>

	.globl	bl2_vector_table
	.globl	bl2_entrypoint
	.globl	report_exception

vector_base bl2_vector_table
	b	bl2_entrypoint
	b	report_exception	/* Undef */
	b	report_exception	/* SVC call */
	b	report_exception	/* Prefetch abort */
	b	report_exception	/* Data abort */
	b	report_exception	/* Reserved */
	b	report_exception	/* IRQ */
	b	report_exception	/* FIQ */


func bl2_entrypoint
	/*---------------------------------------------
	 * Save arguments x0 - x3 from BL1 for future
	 * use.
	 * ---------------------------------------------
	 */
	mov	r9, r0
	mov	r10, r1
	mov	r11, r2
	mov	r12, r3

	/* ---------------------------------------------
	 * Set the exception vector to something sane.
	 * ---------------------------------------------
	 */
	ldr	r0, =bl2_vector_table
	stcopr	r0, VBAR
	isb

	/* --------------------------------------------------------
	 * Enable the instruction cache - disable speculative loads
	 * --------------------------------------------------------
	 */
	ldcopr	r0, SCTLR
	orr	r0, r0, #SCTLR_I_BIT
	bic	r0, r0, #SCTLR_DSSBS_BIT
	stcopr	r0, SCTLR
	isb

	/* ---------------------------------------------
	 * Zero out NOBITS sections. There are 2 of them:
	 *   - the .bss section;
	 *   - the coherent memory section.
	 * ---------------------------------------------
	 */
	ldr	r0, =__BSS_START__
	ldr	r1, =__BSS_SIZE__
	bl	zeromem

#if USE_COHERENT_MEM
	ldr	r0, =__COHERENT_RAM_START__
	ldr	r1, =__COHERENT_RAM_UNALIGNED_SIZE__
	bl	zeromem
#endif

	/* --------------------------------------------
	 * Allocate a stack whose memory will be marked
	 * as Normal-IS-WBWA when the MMU is enabled.
	 * There is no risk of reading stale stack
	 * memory after enabling the MMU as only the
	 * primary cpu is running at the moment.
	 * --------------------------------------------
	 */
	bl	plat_set_my_stack

	/* ---------------------------------------------
	 * Initialize the stack protector canary before
	 * any C code is called.
	 * ---------------------------------------------
	 */
#if STACK_PROTECTOR_ENABLED
	bl	update_stack_protector_canary
#endif

	/* ---------------------------------------------
	 * Perform BL2 setup
	 * ---------------------------------------------
	 */
	mov	r0, r9
	mov	r1, r10
	mov	r2, r11
	mov	r3, r12

	bl	bl2_setup

	/* ---------------------------------------------
	 * Jump to main function.
	 * ---------------------------------------------
	 */
	bl	bl2_main

	/* ---------------------------------------------
	 * Should never reach this point.
	 * ---------------------------------------------
	 */
	no_ret	plat_panic_handler

endfunc bl2_entrypoint

func report_exception
	mrs	r0, cpsr
	and	r0, #MODE32_MASK
	no_ret	plat_panic_handler
endfunc report_exception

func plat_panic_handler
	b	plat_panic_handler
endfunc plat_panic_handler
