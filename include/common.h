#ifndef COMMON_H
#define COMMON_H

#include <linux/types.h>

#define RESERVE_BLOCK_SIZE	(512)

#define UBOOT_START_OFFSET	((RESERVE_BLOCK_SIZE + CONFIG_BL1_SIZE + CONFIG_BL2_SIZE) / 512)
#define UBOOT_SIZE_BLKCNT	(CONFIG_UBOOT_SIZE / 512)

#define TZSW_START_OFFSET	((RESERVE_BLOCK_SIZE + CONFIG_BL1_SIZE + CONFIG_BL2_SIZE + CONFIG_UBOOT_SIZE)  / 512)
#define TZSW_SIZE_BLKCNT	(CONFIG_TZSW_SIZE / 512)


void bl2_arch_setup(void);

void bl2_load_images(void);

void bl2_run_next_image(void);

void set_ps_hold_ctrl(void);

void system_clock_init(void);

void mem_ctrl_init(void);

void exynos_smc(u32 cmd, u32 arg1, u32 arg2, u32 arg3);

void sdelay(unsigned long loops);

#endif
