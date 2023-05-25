#include <common.h>
#include <linux/types.h>
#include <asm/power.h>
#include <debug.h>

/* Index into irom ptr table */
enum index {
	MMC_INDEX,
	EMMC44_INDEX,
	EMMC44_END_INDEX,
	SPI_INDEX,
	USB_INDEX,
};

/* IROM Function Pointers Table */
u32 irom_ptr_table[] = {
	[MMC_INDEX] = 0x02020030,	/* iROM Function Pointer-SDMMC boot */
	[EMMC44_INDEX] = 0x02020044,	/* iROM Function Pointer-EMMC4.4 boot*/
	[EMMC44_END_INDEX] = 0x02020048,/* iROM Function Pointer
						-EMMC4.4 end boot operation */
	[SPI_INDEX] = 0x02020058,	/* iROM Function Pointer-SPI boot */
	[USB_INDEX] = 0x02020070,	/* iROM Function Pointer-USB boot*/
	};

void *get_irom_func(int index)
{
	return (void *)*(u32 *)irom_ptr_table[index];
}

void bl2_load_images(void)
{
	unsigned int bootmode = get_boot_mode();
	u32 offset = 0, size = 0;

	u32 (*copy_bl2)(u32 offset, u32 nblock, u32 dst) = NULL;
	u32 (*copy_uboot_from_emmc)(u32 nblock, u32 dst);
	void (*end_bootop_from_emmc)(void);

	NOTICE("Normal booting\n");

	switch (bootmode) {
	case BOOT_MODE_SD:
		offset = UBOOT_START_OFFSET;
		size = UBOOT_SIZE_BLKCNT;
		copy_bl2 = get_irom_func(MMC_INDEX);
		break;
	case BOOT_MODE_EMMC_SD:
		copy_uboot_from_emmc = get_irom_func(EMMC44_INDEX);
		end_bootop_from_emmc = get_irom_func(EMMC44_END_INDEX);

		copy_uboot_from_emmc(UBOOT_SIZE_BLKCNT, CONFIG_UBOOT_TEXT);
		end_bootop_from_emmc();
		break;
	default:
		break;
        }

	if (copy_bl2)
		copy_bl2(offset, size, CONFIG_UBOOT_TEXT);

}

void bl2_run_next_image(void)
{
	__attribute__((noreturn)) void (*uboot)(void);

	/* Jump to U-Boot image */
	uboot = (void *)CONFIG_UBOOT_TEXT;
	(*uboot)();
}
