#include <arch.h>
#include <asm_macros.S>

	.globl	inv_dcache_range

/*
 * This macro can be used for implementing various data cache operations `op`
 */
.macro do_dcache_maintenance_by_mva op, coproc, opc1, CRn, CRm, opc2
	/* Exit early if size is zero */
	cmp	r1, #0
	beq	exit_loop_\op
	dcache_line_size r2, r3
	add	r1, r0, r1
	sub	r3, r2, #1
	bic	r0, r0, r3
loop_\op:
	stcopr	r0, \coproc, \opc1, \CRn, \CRm, \opc2
	add	r0, r0, r2
	cmp	r0, r1
	blo	loop_\op
	dsb	sy
exit_loop_\op:
	bx	lr
.endm

func inv_dcache_range
	do_dcache_maintenance_by_mva imvac, DCIMVAC
endfunc inv_dcache_range
