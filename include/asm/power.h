#ifndef __POWER_H_
#define __POWER_H_

#ifndef __ASSEMBLY__
struct exynos4x12_power {
	unsigned int	om_stat;
	unsigned char	res1[0xc];
	unsigned int	rtc_clko_sel;
	unsigned int	gnss_rtc_out_ctrl;
	unsigned int	lpi_denial_mask0;
	unsigned int	lpi_denial_mask1;
	unsigned int	lpi_denial_mask2;
	unsigned int	c2c_ctrl;
	unsigned char	res2[0x1d8];
	unsigned int	central_seq_config;
	unsigned int	res3;
	unsigned int	central_seq_option;
	unsigned char	res4[0x1f4];
	unsigned int	swreset;
	unsigned int	rst_stat;
	unsigned int	auto_wdt_reset_disable;
	unsigned int	mask_wdt_reset_request;
	unsigned char	res5[0x1f0];
	unsigned int	wakeup_stat;
	unsigned int	eint_wakeup_mask;
	unsigned int	wakeup_mask;
	unsigned char	res6[0xf4];
	unsigned int	hdmi_phy_control;
	unsigned int	usbdevice_phy_control;
	unsigned int	hsic_1_phy_control;
	unsigned int	hsic_2_phy_control;
	unsigned int	mipi_phy0_control;
	unsigned int	mipi_phy1_control;
	unsigned int	adc_phy_control;
	unsigned char	res7[0x64];
	unsigned int	body_bias_con0;
	unsigned int	body_bias_con1;
	unsigned int	body_bias_con2;
	unsigned int	body_bias_con3;
	unsigned char	res8[0x70];
	unsigned int	inform0;
	unsigned int	inform1;
	unsigned int	inform2;
	unsigned int	inform3;
	unsigned int	inform4;
	unsigned int	inform5;
	unsigned int	inform6;
	unsigned int	inform7;
	unsigned char	res9[0x1e0];
	unsigned int	pmu_debug;
	unsigned char	res10[0x5fc];
	unsigned int	arm_core0_sys_pwr_reg;
	unsigned char	res11[0xc];
	unsigned int	arm_core1_sys_pwr_reg;
	unsigned char	res12[0x6c];
	unsigned int	arm_common_sys_pwr_reg;
	unsigned char	res13[0x3c];
	unsigned int	arm_cpu_l2_0_sys_pwr_reg;
	unsigned int	arm_cpu_l2_1_sys_pwr_reg;
	unsigned char	res14[0x38];
	unsigned int	cmu_aclkstop_sys_pwr_reg;
	unsigned int	cmu_sclkstop_sys_pwr_reg;
	unsigned char	res15[0x4];
	unsigned int	cmu_reset_sys_pwr_reg;
	unsigned char	res16[0x10];
	unsigned int	apll_sysclk_sys_pwr_reg;
	unsigned int	mpll_sysclk_sys_pwr_reg;
	unsigned int	vpll_sysclk_sys_pwr_reg;
	unsigned int	epll_sysclk_sys_pwr_reg;
	unsigned char	res17[0x8];
	unsigned int	cmu_clkstop_gps_alive_sys_pwr_reg;
	unsigned int	cmu_reset_gps_alive_sys_pwr_reg;
	unsigned int	cmu_clkstop_cam_sys_pwr_reg;
	unsigned int	cmu_clkstop_tv_sys_pwr_reg;	
	unsigned int	cmu_clkstop_mfc_sys_pwr_reg;
	unsigned int	cmu_clkstop_g3d_sys_pwr_reg;
	unsigned int	cmu_clkstop_lcd0_sys_pwr_reg;
	unsigned int	cmu_clkstop_isp_sys_pwr_reg;
	unsigned int	cmu_clkstop_maudio_sys_pwr_reg;
	unsigned int	cmu_clkstop_gps_sys_pwr_reg;
	unsigned int	cmu_reset_cam_sys_pwr_reg;
	unsigned int	cmu_reset_tv_sys_pwr_reg;
	unsigned int	cmu_reset_mfc_sys_pwr_reg;
	unsigned int	cmu_reset_g3d_sys_pwr_reg;
	unsigned int	cmu_reset_lcd0_sys_pwr_reg;
	unsigned int	cmu_reset_isp_sys_pwr_reg;
	unsigned int	cmu_reset_maudio_sys_pwr_reg;
	unsigned int	cmu_reset_gps_sys_pwr_reg;
	unsigned int	top_bus_sys_pwr_reg;
	unsigned int	top_retention_sys_pwr_reg;
	unsigned int	top_pwr_sys_pwr_reg;
	unsigned char	res18[0x14];
	unsigned int	logic_reset_sys_pwr_reg;
	unsigned char	res19[0x1c];
	unsigned int	onenandxl_mem_sys_pwr_reg;
	unsigned int	hsi_mem_sys_pwr_reg;
	unsigned char	res20[0x4];	
	unsigned int	usbotg_mem_sys_pwr_reg;
	unsigned int	sdmmc_mem_sys_pwr_reg;
	unsigned int	cssys_mem_sys_pwr_reg;
	unsigned int	secss_mem_sys_pwr_reg;
	unsigned int	potator_mem_sys_pwr_reg;
	unsigned char	res21[0x20];
	unsigned int	pad_retention_dram_sys_pwr_reg;
	unsigned int	pad_retention_maudio_sys_pwr_reg;
	unsigned char	res22[0x18];
	unsigned int	pad_retention_gpio_sys_pwr_reg;
	unsigned int	pad_retention_uart_sys_pwr_reg;
	unsigned int	pad_retention_mmca_sys_pwr_reg;
	unsigned int	pad_retention_mmcb_sys_pwr_reg;
	unsigned int	pad_retention_ebia_sys_pwr_reg;
	unsigned int	pad_retention_ebib_sys_pwr_reg;
	unsigned char	res23[0x8];
	unsigned int	pad_isolation_sys_pwr_reg;
	unsigned char	res24[0x1c];
	unsigned int	pad_alv_sel_sys_pwr_reg;
	unsigned char	res25[0x1c];
	unsigned int	xusbxti_sys_pwr_reg;
	unsigned int	xxti_sys_pwr_reg;
	unsigned char	res26[0x38];
	unsigned int	ext_regulator_sys_pwr_reg;
	unsigned char	res27[0x3c];
	unsigned int	gpio_mode_sys_pwr_reg;
	unsigned char	res28[0x3c];
	unsigned int	gpio_mode_maudio_sys_pwr_reg;
	unsigned char	res29[0x3c];
	unsigned int	cam_sys_pwr_reg;
	unsigned int	tv_sys_pwr_reg;
	unsigned int	mfc_sys_pwr_reg;
	unsigned int	g3d_sys_pwr_reg;
	unsigned int	lcd0_sys_pwr_reg;
	unsigned int	isp_sys_pwr_reg;
	unsigned int	maudio_sys_pwr_reg;
	unsigned int	gps_sys_pwr_reg;
	unsigned int	gps_alive_sys_pwr_reg;
	unsigned char	res30[0xc5c];
	unsigned int	arm_core0_configuration;
	unsigned int	arm_core0_status;
	unsigned int	arm_core0_option;
	unsigned char	res31[0x74];
	unsigned int	arm_core1_configuration;
	unsigned int	arm_core1_status;
	unsigned int	arm_core1_option;
	unsigned char	res32[0x37c];
	unsigned int	arm_common_option;
	unsigned char	res33[0x1f4];
	unsigned int	arm_cpu_l2_0_configuration;
	unsigned int	arm_cpu_l2_0_status;
	unsigned char	res34[0x18];
	unsigned int	arm_cpu_l2_1_configuration;
	unsigned int	arm_cpu_l2_1_status;
	unsigned char	res35[0xa00];
	unsigned int	pad_retention_maudio_option;
	unsigned char	res36[0xdc];
	unsigned int	pad_retention_gpio_option;
	unsigned char	res37[0x1c];
	unsigned int	pad_retention_uart_option;
	unsigned char	res38[0x1c];
	unsigned int	pad_retention_mmca_option;
	unsigned char	res39[0x1c];
	unsigned int	pad_retention_mmcb_option;
	unsigned char	res40[0x1c];
	unsigned int	pad_retention_ebia_option;
	unsigned char	res41[0x1c];
	unsigned int	pad_retention_ebib_option;
	unsigned char	res42[0x160];
	unsigned int	ps_hold_control;
	unsigned char	res43[0xf0];
	unsigned int	xusbxti_configuration;
	unsigned int	xusbxti_status;
	unsigned char	res44[0x14];
	unsigned int	xusbxti_duration;
	unsigned int	xxti_configuration;
	unsigned int	xxti_status;
	unsigned char	res45[0x14];
	unsigned int	xxti_duration;
	unsigned char	res46[0x1dc];
	unsigned int	ext_regulator_duration;
	unsigned char	res47[0x5e0];
	unsigned int	cam_configuration;
	unsigned int	cam_status;
	unsigned int	cam_option;
	unsigned char	res48[0x14];
	unsigned int	tv_configuration;
	unsigned int	tv_status;
	unsigned int	tv_option;
	unsigned char	res49[0x14];
	unsigned int	mfc_configuration;
	unsigned int	mfc_status;
	unsigned int	mfc_option;
	unsigned char	res50[0x14];
	unsigned int	g3d_configuration;
	unsigned int	g3d_status;
	unsigned int	g3d_option;
	unsigned char	res51[0x14];
	unsigned int	lcd0_configuration;
	unsigned int	lcd0_status;
	unsigned int	lcd0_option;
	unsigned char	res52[0x14];
	unsigned int	isp_configuration;
	unsigned int	isp_status;
	unsigned int	isp_option;
	unsigned char	res53[0x34];
	unsigned int	gps_configuration;
	unsigned int	gps_status;
	unsigned int	gps_option;
	unsigned char	res54[0x14];
	unsigned int	gps_alive_configuration;
	unsigned int	gps_alive_status;
	unsigned int	gps_alive_option;
};
#endif	/* __ASSEMBLY__ */

#define OM_PIN_BITS	0x1f
#define OM_PIN_SHIFT	0x1
#define OM_PIN_MASK	(OM_PIN_BITS << OM_PIN_SHIFT)

enum {
	/*
	 * Assign the OM pin values for respective boot modes.
	 * Exynos4 does not support spi boot and the mmc boot OM
	 * pin values are the same across Exynos4 and Exynos5.
	 */
	BOOT_MODE_SD = 4,      /* SD_CH2  | USB */
	BOOT_MODE_EMMC = 8,     /* EMMC4.4 | USB */
	BOOT_MODE_EMMC_SD = 40, /* EMMC4.4 | SD_CH2 */
	BOOT_MODE_SERIAL = 20,
	/* Boot based on Operating Mode pin settings */
	BOOT_MODE_OM = 32,
	BOOT_MODE_USB,	/* Boot using USB download */
};

uint32_t get_reset_status(void);

#define EXYNOS_PS_HOLD_CONTROL_DATA_HIGH	(1 << 8)

/*
 * Set ps_hold data driving value high
 * This enables the machine to stay powered on
 * after the initial power-on condition goes away
 * (e.g. power button).
 */
void set_ps_hold_ctrl(void);

unsigned int get_boot_mode(void);

#endif
