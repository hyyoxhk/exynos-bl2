OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(bl2_entrypoint)

MEMORY { .sram : ORIGIN = 0x02025000, LENGTH = (14 * 1024) }

SECTIONS
{
	.text : {
		__TEXT_START__ = .;
		*bl2_entrypoint.o(.text*)
		*(SORT_BY_ALIGNMENT(.text*))
		*(.vectors)
		. = ALIGN(4);
		__TEXT_END__ = .;
	} >.sram
	. = ALIGN(4);

	.rodata : { *(SORT_BY_ALIGNMENT(.rodata*)) } >.sram
	. = ALIGN(4);

	.data : { *(SORT_BY_ALIGNMENT(.data*)) } >.sram
	. = ALIGN(4);

	.bss :
	{
		. = ALIGN(4);
		__BSS_START__ = .;
		*(.bss*)
		. = ALIGN(4);
		__BSS_END__ = .;
	} >.sram

	__BSS_SIZE__ = SIZEOF(.bss);
}

