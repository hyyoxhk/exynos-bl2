/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2023 He Yong <hyyoxhk@163.com>
 *
 */

#include <debug.h>
#include <common.h>
#include <console.h>
#include <linux/types.h>

#include <drivers/periph.h>

#define CONFIG_SYS_TEXT_BASE	0x43E00000

const char build_message[] = "V1.0";
const char version_string[] = "V2.0";
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
	NOTICE("BL2: %s\n", version_string);
	NOTICE("BL2: %s\n", build_message);
	__attribute__((noreturn)) void (*uboot)(void);

	/* Load the subsequent bootloader images. */
	bl2_load_images_v2();

	/* Jump to U-Boot image */
	uboot = (void *)CONFIG_SYS_TEXT_BASE;
	NOTICE("run uboot..\n");
	(*uboot)();
	NOTICE("running uboot..\n");

#if !BL2_AT_EL3
#ifndef __aarch64__
	/*
	 * For AArch32 state BL1 and BL2 share the MMU setup.
	 * Given that BL2 does not map BL1 regions, MMU needs
	 * to be disabled in order to go back to BL1.
	 */
//	disable_mmu_icache_secure();
#endif /* !__aarch64__ */

	//console_flush();

#if ENABLE_PAUTH
	/*
	 * Disable pointer authentication before running next boot image
	 */
	pauth_disable_el1();
#endif /* ENABLE_PAUTH */

	/*
	 * Run next BL image via an SMC to BL1. Information on how to pass
	 * control to the BL32 (if present) and BL33 software images will
	 * be passed to next BL image as an argument.
	 */
	//smc(BL1_SMC_RUN_IMAGE, (unsigned long)next_bl_ep_info, 0, 0, 0, 0, 0, 0);
#else /* if BL2_AT_EL3 */
	NOTICE("BL2: Booting " NEXT_IMAGE "\n");
	//print_entry_point_info(next_bl_ep_info);
	//console_flush();

#if ENABLE_PAUTH
	/*
	 * Disable pointer authentication before running next boot image
	 */
	pauth_disable_el3();
#endif /* ENABLE_PAUTH */

	//bl2_run_next_image(next_bl_ep_info);
#endif /* BL2_AT_EL3 */
}
