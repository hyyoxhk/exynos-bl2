/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2023 He Yong <hyyoxhk@163.com>
 *
 */

#include <debug.h>
#include <common.h>
#include <stdio.h>
#include <console.h>
#include <linux/types.h>
#include <version.h>

#include <drivers/periph.h>

#define CONFIG_SYS_TEXT_BASE	0x43E00000

const char version_string[] = BL2_VERSION;
console_t console;

void bl2_setup(phys_addr_t arg0, phys_addr_t arg1, phys_addr_t arg2, phys_addr_t arg3)
{
	/* Perform late platform-specific setup */
	set_ps_hold_ctrl();

	system_clock_init();

	uart_config(PERIPH_ID_UART2);

	console_register(CONFIG_DEBUG_UART_BASE, 100000000, 115200, &console);

	mem_ctrl_init();
}

void bl2_main(void)
{
	putchar('\n');
	NOTICE("BL2: %s\n", version_string);

	/* Load the subsequent bootloader images. */
	bl2_load_images();
	/* Jump to U-Boot image */
	//uboot = (void *)CONFIG_SYS_TEXT_BASE;
	//(*uboot)();


	/*
	 * Run next BL image via an SMC to BL1. Information on how to pass
	 * control to the BL32 (if present) and BL33 software images will
	 * be passed to next BL image as an argument.
	 */
	//smc(BL1_SMC_RUN_IMAGE, (unsigned long)next_bl_ep_info, 0, 0, 0, 0, 0, 0);

	//NOTICE("BL2: Booting " NEXT_IMAGE "\n");
	//print_entry_point_info(next_bl_ep_info);


	bl2_run_next_image();
}
