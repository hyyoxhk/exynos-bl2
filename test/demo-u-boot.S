#define SYMBOL_NAME(X)		X
#define ASM_NL		 ;

#define __ALIGN .align 0

#define ALIGN			__ALIGN

#define SYMBOL_NAME_LABEL(X)	X##:

#define LENTRY(name) \
	ALIGN ASM_NL \
	SYMBOL_NAME_LABEL(name)

#define ENTRY(name) \
	.globl SYMBOL_NAME(name) ASM_NL \
	LENTRY(name)

#define STT_FUNC	2

#define END(name) \
	.size name, .-name

#define ENDPROC(name) \
	.type name STT_FUNC ASM_NL \
	END(name)

ENTRY(_main)

ENDPROC(_main)
