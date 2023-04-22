/* SPDX-License-Identifier: MIT */
/*
 * Copyright (C) 2023 He Yong <hyyoxhk@163.com>
 *
 */

#include <common.h>
#include <linux/types.h>
#include <asm/power.h>
#include <debug.h>

#define RESERVE_BLOCK_SIZE	(512)
#define BL1_SIZE		(0x3C00)  /* 15 K reserved for BL1 */
#define BL2_SIZE		(0x4000)  /* 16 K reserved for BL2 */
#define UBOOT_START_OFFSET	((RESERVE_BLOCK_SIZE + BL1_SIZE + BL2_SIZE) / 512)
#define COPY_UBOOT_SIZE		(0x80000) /* 512k */
#define UBOOT_SIZE_BLOC_COUNT	(COPY_UBOOT_SIZE / 512)
#define CONFIG_SYS_TEXT_BASE	0x43E00000

typedef struct sdmmc_dev {
	/* for SDMMC */
	u32	image_pos;
	u32	blkcnt;
	u32	base_addr;
} sdmmc_t;

typedef struct emmc_dev {
	/* for eMMC */
	u32	blkcnt;
	u32	base_addr;
} emmc_t;

typedef struct sata_dev {
	/* for SATA */
	u64	read_sector_of_hdd;
	u32	trans_byte;
	u32	*read_buffer;
	u32	position_of_mem;
} sata_t;

typedef struct sfmc_dev {
	/* for SFMC */
	u32	cs;
	u32	byte_offset;
	u32	byte_size;
	void	*dest_addr;
} sfmc_t;

typedef struct spi_sf_dev {
	/* for SPI SERIAL FLASH */
	u32	flash_read_addr;
	u32	read_size;
	u8	*read_buff;
} spi_sf_t;

/* boot device */
typedef union boot_device_u {
	sdmmc_t 	sdmmc;
	emmc_t		emmc;
	sata_t		sata;
	sfmc_t		sfmc;
	spi_sf_t	spi_sf;
} boot_device_t;

typedef struct ld_image_info {
	/* for Signature */
	u32	image_base_addr;
	u32	size;
	u32	secure_context_base;
	u32	signature_size;
	boot_device_t bootdev;

}image_info;

#define CONFIG_PHY_SDRAM_BASE		(0x40000000)
#define CONFIG_PHY_IRAM_BASE		(0x02020000)
#define SMC_SECURE_CONTEXT_BASE		(CONFIG_PHY_IRAM_BASE + 0x4c00)
#define CONFIG_PHY_TZSW_BASE		(CONFIG_PHY_IRAM_BASE + 0x8000)

#define SMC_CMD_LOAD_UBOOT			(-230)
#define SMC_CMD_COLDBOOT			(-231)
#define SMC_CMD_WARMBOOT			(-232)
#define SMC_CMD_CHECK_SECOND_BOOT		(-233)
#define SMC_CMD_EMMC_ENDBOOTOP                  (-234)

// #define CONFIG_SECURE_TZSW_ONLY 1
// #define CONFIG_SECURE_BOOT 1

#ifdef CONFIG_SECURE_BOOT
#define SMC_SIGNATURE_SIZE		256
#else
#define SMC_SIGNATURE_SIZE		0
#endif

#define CONFIG_IMAGE_INFO_BASE	(CONFIG_PHY_SDRAM_BASE)

/* Boot device */
#define SDMMC_CH2		0x0
#define SDMMC_CH0		0x4
#define EMMC			0x10
#define EMMC_4_4		0x14
#define USB			0x40

#define MOVI_FWBL1_BLKCNT	(PART_SIZE_FWBL1 / MOVI_BLKSIZE)
#define MOVI_BL1_BLKCNT		(PART_SIZE_BL1 / MOVI_BLKSIZE)
#define MOVI_ENV_BLKCNT		(CONFIG_ENV_SIZE / MOVI_BLKSIZE)	/* 16KB */
#define MOVI_UBOOT_BLKCNT	(PART_SIZE_UBOOT / MOVI_BLKSIZE)	/* 512KB */
#define MOVI_ZIMAGE_BLKCNT	(PART_SIZE_KERNEL / MOVI_BLKSIZE)	/* 4MB */
#define MOVI_ROOTFS_BLKCNT	(PART_SIZE_ROOTFS / MOVI_BLKSIZE)	/* 26MB */
#define MOVI_TZSW_BLKCNT	(PART_SIZE_TZSW / MOVI_BLKSIZE)		/* 160KB */

#define CONFIG_SYS_SDRAM_BASE		0x40000000
#define CONFIG_PHY_UBOOT_BASE		CONFIG_SYS_SDRAM_BASE + 0x3e00000

#define eFUSE_SIZE		(1 * 512)	// 512 Byte eFuse, 512 Byte reserved
#define MOVI_BLKSIZE		(1 << 9)	/* 512 bytes */

#define PART_SIZE_FWBL1		(15 * 1024)

#define PART_SIZE_BL1		(16 * 1024)

#define PART_SIZE_UBOOT		(512 * 1024)

#define PART_SIZE_TZSW		(156 * 1024)

#define MOVI_UBOOT_POS		((eFUSE_SIZE / MOVI_BLKSIZE) + MOVI_FWBL1_BLKCNT + MOVI_BL1_BLKCNT)
#define MOVI_TZSW_POS           ((eFUSE_SIZE / MOVI_BLKSIZE) + MOVI_FWBL1_BLKCNT \
                                  + MOVI_BL1_BLKCNT + MOVI_UBOOT_BLKCNT)

void load_uboot_image(u32 boot_device)
{
	image_info *info_image;

	info_image = (image_info *)CONFIG_IMAGE_INFO_BASE;

	if (boot_device == SDMMC_CH2) {

		info_image->bootdev.sdmmc.image_pos = MOVI_UBOOT_POS;
		info_image->bootdev.sdmmc.blkcnt =  MOVI_UBOOT_BLKCNT;
		info_image->bootdev.sdmmc.base_addr = CONFIG_SYS_TEXT_BASE;

	} else if (boot_device == EMMC || boot_device == EMMC_4_4) {

		info_image->bootdev.emmc.blkcnt =  MOVI_UBOOT_BLKCNT;
		info_image->bootdev.emmc.base_addr = CONFIG_SYS_TEXT_BASE;

	}

	info_image->image_base_addr = CONFIG_SYS_TEXT_BASE;
	info_image->size = (MOVI_UBOOT_BLKCNT * MOVI_BLKSIZE);
	info_image->secure_context_base = SMC_SECURE_CONTEXT_BASE;
	info_image->signature_size = SMC_SIGNATURE_SIZE;

	exynos_smc(SMC_CMD_LOAD_UBOOT, boot_device, CONFIG_IMAGE_INFO_BASE, 0);
}

void coldboot(u32 boot_device)
{
	image_info *info_image;
	int i;

	info_image = (image_info *) CONFIG_IMAGE_INFO_BASE;

	if (boot_device == SDMMC_CH2) {

		info_image->bootdev.sdmmc.image_pos = MOVI_TZSW_POS;
		info_image->bootdev.sdmmc.blkcnt =  MOVI_TZSW_BLKCNT;
		info_image->bootdev.sdmmc.base_addr = CONFIG_PHY_TZSW_BASE;

	} else if (boot_device == EMMC || boot_device == EMMC_4_4) {

		i = 100;		/* for EMMC 4.4 */
		while(i--);

		info_image->bootdev.emmc.blkcnt =  MOVI_TZSW_BLKCNT;
		info_image->bootdev.emmc.base_addr = CONFIG_PHY_TZSW_BASE;

	}

	info_image->image_base_addr = CONFIG_PHY_TZSW_BASE;
	info_image->size = (MOVI_TZSW_BLKCNT * MOVI_BLKSIZE);
	info_image->secure_context_base = SMC_SECURE_CONTEXT_BASE;
#if defined(CONFIG_SECURE_TZSW_ONLY)
	info_image->signature_size = 256;
#else
	info_image->signature_size = SMC_SIGNATURE_SIZE;
#endif

	exynos_smc(SMC_CMD_COLDBOOT, boot_device, CONFIG_IMAGE_INFO_BASE, CONFIG_SYS_TEXT_BASE);
}

void bl2_load_images_v2(void)
{
	unsigned int bootmode = get_boot_mode();

	NOTICE("bl2_load_images_v2 ..\n");

	if (bootmode == BOOT_MODE_OM)
		bootmode = get_boot_mode();

	switch (bootmode) {
	case BOOT_MODE_SD:
		load_uboot_image(0x0);
		coldboot(0x0);
		break;
	case BOOT_MODE_EMMC_SD:
		load_uboot_image(0x14);
		coldboot(0x14);
		break;
	}
}