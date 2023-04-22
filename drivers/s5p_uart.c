// typedef unsigned long uintptr_t;
// typedef unsigned int u32;

// #define DMB	asm volatile ("dmb sy" : : : "memory")
// #define dmb()	DMB

// #define __arch_putl(v,a)		(*(volatile unsigned int *)(a) = (v))
// #define __iowmb()	dmb()

// #define writel(v,c)	({ u32 __v = v; __iowmb(); __arch_putl(__v,c); __v; })

#include <linux/errno.h>
#include <asm/io.h>
#include <console.h>
#include <drivers/s5p_uart_regs.h>
#include <drivers/s5p_uart.h>
#include <drivers/s5p_gpio.h>
#include <drivers/periph.h>

static void s5p_uart_init(uintptr_t base_addr, unsigned int uart_clk, unsigned int baud_rate)
{
	/* enable FIFOs, auto clear Rx FIFO */
	writel(0x3, base_addr + UFCON);
	writel(0, base_addr + UMCON);
	/* 8N1 */
	writel(0x3, base_addr + ULCON);
	/* No interrupts, no DMA, pure polling */
	writel(0x245, base_addr + UCON);

	u32 val;

	val = uart_clk / baud_rate;
	writel(val / 16 - 1, base_addr + UBRDIV);
	writeb(val % 16, base_addr + UFRACVAL);
}

static int uart_err_check(uintptr_t base_addr, int op)
{
	unsigned int mask;
	/*
	 * UERSTAT
	 * Break Detect	[3]
	 * Frame Err	[2] : receive operation
	 * Parity Err	[1] : receive operation
	 * Overrun Err	[0] : receive operation
	 */
	if (op)
		mask = 0x8;
	else
		mask = 0xf;

	return readl(base_addr + UERSTAT) & mask;
}

static int s5p_uart_putc(int c, console_t *console)
{
	uintptr_t base_addr = console->base;

	while (readl(base_addr + UFSTAT) & TX_FIFO_FULL);

	writeb(c, base_addr + UTXH);
	uart_err_check(base_addr, 1);

	return 0;
}

int console_register(uintptr_t baseaddr, uint32_t clock, uint32_t baud, console_t *console)
{
	if (console < 0)
		return -1;

	console->base = baseaddr;

	s5p_uart_init(baseaddr, clock, baud);

	console->putc  = s5p_uart_putc;
	console->getc  = NULL;
	console->flush = NULL;
	return 0;
}

int console_putc(int c, console_t *console)
{
	if (console < 0)
		return -1;

	if (c == '\n') \
		console->putc('\r', console);
	console->putc(c, console);
	return 0;
}

void uart_config(int peripheral)
{
	int i, start, count;

	switch (peripheral) {
	case PERIPH_ID_UART0:
		start = EXYNOS4X12_GPIO_A00;
		count = 4;
		break;
	case PERIPH_ID_UART1:
		start = EXYNOS4X12_GPIO_A04;
		count = 4;
		break;
	case PERIPH_ID_UART2:
		start = EXYNOS4X12_GPIO_A10;
		count = 4;
		break;
	case PERIPH_ID_UART3:
		start = EXYNOS4X12_GPIO_A14;
		count = 2;
		break;
	default:
		return;
	}
	for (i = start; i < (start + count); i++) {
		gpio_set_pull(i, S5P_GPIO_PULL_NONE);
		gpio_cfg_pin(i, S5P_GPIO_FUNC(0x2));
	}
}

