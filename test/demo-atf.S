	.macro func _name, _align=2
	/*
	 * Add Call Frame Information entry in the .debug_frame section for
	 * debugger consumption. This enables callstack printing in debuggers.
	 * This does not use any space in the final loaded binary, only in the
	 * ELF file.
	 * Note that a function manipulating the CFA pointer location (i.e. the
	 * x29 frame pointer on AArch64) should declare it using the
	 * appropriate .cfi* directives, or be prepared to have a degraded
	 * debugging experience.
	 */
	.cfi_sections .debug_frame
	.section .text.asm.\_name, "ax"
	.type \_name, %function
	/*
	 * .cfi_startproc and .cfi_endproc are needed to output entries in
	 * .debug_frame
	 */
	.cfi_startproc
	.align \_align
	\_name:

	/* When Branch Target Identification is enabled, insert "bti jc"
	 * instruction to enable indirect calls and branches
	 */
	 bti	jc

	.endm

	/*
	 * This macro is used to mark the end of a function.
	 */
	.macro endfunc _name
	.cfi_endproc
	.size \_name, . - \_name
	.endm

func bl2_entrypoint

endfunc bl2_entrypoint
