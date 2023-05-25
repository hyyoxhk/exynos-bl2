#include <arch.h>
#include <asm_macros.S>

	.weak	plat_set_my_stack

func plat_set_my_stack
	ldr	r0, =(CONFIG_SP_ADDR)
	bic	r0, r0, #7	/* 8-byte alignment for ABI compliance */
	mov	sp, r0
endfunc plat_set_my_stack
