#ifndef COMMON_H
#define COMMON_H

#include <linux/types.h>

void bl2_arch_setup(void);

void bl2_load_images_v1(void);

void bl2_load_images_v2(void);

void set_ps_hold_ctrl(void);

void system_clock_init(void);

void mem_ctrl_init(void);

void exynos_smc(u32 cmd, u32 arg1, u32 arg2, u32 arg3);

void sdelay(unsigned long loops);

#endif
