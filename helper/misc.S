#include <arch.h>
#include <asm_macros.S>

	.globl	zeromem


/* -----------------------------------------------------------------------
 * void zeromem(void *mem, unsigned int length)
 *
 * Initialise a region in normal memory to 0. This functions complies with the
 * AAPCS and can be called from C code.
 *
 * -----------------------------------------------------------------------
 */
func zeromem
	/*
	 * Readable names for registers
	 *
	 * Registers r0, r1 and r2 are also set by zeromem which
	 * branches into the fallback path directly, so cursor, length and
	 * stop_address should not be retargeted to other registers.
	 */
	cursor       .req r0 /* Start address and then current address */
	length       .req r1 /* Length in bytes of the region to zero out */
	/*
	 * Reusing the r1 register as length is only used at the beginning of
	 * the function.
	 */
	stop_address .req r1  /* Address past the last zeroed byte */
	zeroreg1     .req r2  /* Source register filled with 0 */
	zeroreg2     .req r3  /* Source register filled with 0 */
	tmp	     .req r12 /* Temporary scratch register */

	mov	zeroreg1, #0

	/* stop_address is the address past the last to zero */
	add	stop_address, cursor, length

	/*
	 * Length cannot be used anymore as it shares the same register with
	 * stop_address.
	 */
	.unreq	length

	/*
	 * If the start address is already aligned to 8 bytes, skip this loop.
	 */
	tst	cursor, #(8-1)
	beq	.Lzeromem_8bytes_aligned

	/* Calculate the next address aligned to 8 bytes */
	orr	tmp, cursor, #(8-1)
	adds	tmp, tmp, #1
	/* If it overflows, fallback to byte per byte zeroing */
	beq	.Lzeromem_1byte_aligned
	/* If the next aligned address is after the stop address, fall back */
	cmp	tmp, stop_address
	bhs	.Lzeromem_1byte_aligned

	/* zero byte per byte */
1:
	strb	zeroreg1, [cursor], #1
	cmp	cursor, tmp
	bne	1b

	/* zero 8 bytes at a time */
.Lzeromem_8bytes_aligned:

	/* Calculate the last 8 bytes aligned address. */
	bic	tmp, stop_address, #(8-1)

	cmp	cursor, tmp
	bhs	2f

	mov	zeroreg2, #0
1:
	stmia	cursor!, {zeroreg1, zeroreg2}
	cmp	cursor, tmp
	blo	1b
2:

	/* zero byte per byte */
.Lzeromem_1byte_aligned:
	cmp	cursor, stop_address
	beq	2f
1:
	strb	zeroreg1, [cursor], #1
	cmp	cursor, stop_address
	bne	1b
2:
	bx	lr

	.unreq	cursor
	/*
	 * length is already unreq'ed to reuse the register for another
	 * variable.
	 */
	.unreq	stop_address
	.unreq	zeroreg1
	.unreq	zeroreg2
	.unreq	tmp
endfunc zeromem
