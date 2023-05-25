/* SPDX-License-Identifier: MIT */
/*
 * Copyright (C) 2023 He Yong <hyyoxhk@163.com>
 *
 */

#include <common.h>
#include <linux/types.h>
#include <asm/power.h>
#include <debug.h>

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

#define SMC_CMD_LOAD_UBOOT			(-230)
#define SMC_CMD_COLDBOOT			(-231)
#define SMC_CMD_WARMBOOT			(-232)
#define SMC_CMD_CHECK_SECOND_BOOT		(-233)
#define SMC_CMD_EMMC_ENDBOOTOP                  (-234)

/* Boot device */
#define SDMMC_CH2		0x0
#define SDMMC_CH0		0x4
#define EMMC			0x10
#define EMMC_4_4		0x14
#define USB			0x40

static void load_uboot_image(u32 boot_device)
{
	image_info info_image;

	NOTICE("Loading uboot image\n");

	if (boot_device == SDMMC_CH2) {
		info_image.bootdev.sdmmc.image_pos = UBOOT_START_OFFSET;
		info_image.bootdev.sdmmc.blkcnt =  UBOOT_SIZE_BLKCNT;
		info_image.bootdev.sdmmc.base_addr = CONFIG_UBOOT_TEXT;
	} else if (boot_device == EMMC || boot_device == EMMC_4_4) {
		info_image.bootdev.emmc.blkcnt =  UBOOT_SIZE_BLKCNT;
		info_image.bootdev.emmc.base_addr = CONFIG_UBOOT_TEXT;
	}

	info_image.image_base_addr	= CONFIG_UBOOT_TEXT;
	info_image.size			= CONFIG_UBOOT_SIZE;
	info_image.secure_context_base	= CONFIG_SECURE_CONTEXT_BASE;
	info_image.signature_size	= 0;

	exynos_smc(SMC_CMD_LOAD_UBOOT, boot_device, (u32)&info_image, 0);
}

static void coldboot(u32 boot_device)
{
	image_info info_image;

	NOTICE("Loading tzsw image\n");

	if (boot_device == SDMMC_CH2) {
		info_image.bootdev.sdmmc.image_pos = TZSW_START_OFFSET;
		info_image.bootdev.sdmmc.blkcnt =  TZSW_SIZE_BLKCNT;
		info_image.bootdev.sdmmc.base_addr = CONFIG_TZSW_TEXT;
	} else if (boot_device == EMMC || boot_device == EMMC_4_4) {
		sdelay(100);
		info_image.bootdev.emmc.blkcnt =  TZSW_SIZE_BLKCNT;
		info_image.bootdev.emmc.base_addr = CONFIG_TZSW_TEXT;
	}

	info_image.image_base_addr	= CONFIG_TZSW_TEXT;
	info_image.size			= CONFIG_TZSW_SIZE;
	info_image.secure_context_base	= CONFIG_SECURE_CONTEXT_BASE;
	info_image.signature_size	= 0;

	exynos_smc(SMC_CMD_COLDBOOT, boot_device, (u32)&info_image, CONFIG_UBOOT_TEXT);
}

void bl2_load_images(void)
{
	unsigned int bootmode = get_boot_mode();

	NOTICE("Secure booting\n");

	if (bootmode == BOOT_MODE_OM)
		bootmode = get_boot_mode();

	switch (bootmode) {
	case BOOT_MODE_SD:
		load_uboot_image(0x0);
		break;
	case BOOT_MODE_EMMC_SD:
		load_uboot_image(0x14);
		break;
	}
}

void bl2_run_next_image(void)
{
	unsigned int bootmode = get_boot_mode();

	if (bootmode == BOOT_MODE_OM)
		bootmode = get_boot_mode();

	switch (bootmode) {
	case BOOT_MODE_SD:
		coldboot(0x0);
		break;
	case BOOT_MODE_EMMC_SD:
		coldboot(0x14);
		break;
	}
}