#include <arch.h>
#include <asm_macros.S>

	.weak	plat_set_my_stack

#define CONFIG_INIT_SP_ADDR	0x02040000

func plat_set_my_stack
	ldr	r0, =(CONFIG_INIT_SP_ADDR)
	bic	r0, r0, #7	/* 8-byte alignment for ABI compliance */
	mov	sp, r0
endfunc plat_set_my_stack



