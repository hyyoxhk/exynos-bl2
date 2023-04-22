#include <linux/types.h>
#include <asm/power.h>
#include <debug.h>

#define RESERVE_BLOCK_SIZE	(512)
#define BL1_SIZE		(0x2000)  /* 8 K reserved for BL1 */
#define BL2_SIZE		(0x4000)  /* 16 K reserved for BL2 */
#define UBOOT_START_OFFSET	((RESERVE_BLOCK_SIZE + BL1_SIZE + BL2_SIZE) / 512)
#define COPY_UBOOT_SIZE		(0x80000) /* 512k */
#define UBOOT_SIZE_BLOC_COUNT	(COPY_UBOOT_SIZE / 512)
#define CONFIG_SYS_TEXT_BASE	0x43E00000

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

void bl2_load_images_v1(void)
{
	NOTICE("bl2_load_images..\n");

	unsigned int bootmode = get_boot_mode();
	u32 offset = 0, size = 0;

	u32 (*copy_uboot)(u32 offset, u32 nblock, u32 dst) = NULL;
	u32 (*copy_uboot_from_emmc)(u32 nblock, u32 dst);
	void (*end_bootop_from_emmc)(void);

	switch (bootmode) {
	case BOOT_MODE_SD:
		NOTICE("BOOT_MODE_SD..\n");

		offset = UBOOT_START_OFFSET;
		size = UBOOT_SIZE_BLOC_COUNT;
		copy_uboot = get_irom_func(MMC_INDEX);
		if (copy_uboot) {
			copy_uboot(offset, size, CONFIG_SYS_TEXT_BASE);
			NOTICE("copy_uboot..\n");

		}
		break;
	case BOOT_MODE_EMMC_SD:
		NOTICE("BOOT_MODE_EMMC_SD..\n");

		copy_uboot_from_emmc = get_irom_func(EMMC44_INDEX);
		end_bootop_from_emmc = get_irom_func(EMMC44_END_INDEX);

		copy_uboot_from_emmc(UBOOT_SIZE_BLOC_COUNT, CONFIG_SYS_TEXT_BASE);
		end_bootop_from_emmc();
		break;
        }


}