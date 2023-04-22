/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2020 hey <hyyoxhk@163.com>
 *
 */

#ifndef _CLOCK_H
#define _CLOCK_H

struct exynos4x12_clock {
	unsigned char	res1[0x4200];
	unsigned int	src_leftbus;
	unsigned char	res2[0x1fc];
	unsigned int	mux_stat_leftbus;
	unsigned char	res3[0xfc];
	unsigned int	div_leftbus;
	unsigned char	res4[0xfc];
	unsigned int	div_stat_leftbus;
	unsigned char	res5[0x1fc];
	unsigned int	gate_ip_leftbus;
	unsigned char	res6[0x12c];
	unsigned int	gate_ip_image;
	unsigned char	res7[0xcc];
	unsigned int	clkout_leftbus;
	unsigned int	clkout_leftbus_div_stat;
	unsigned char	res8[0x37f8];
	unsigned int	src_rightbus;
	unsigned char	res9[0x1fc];
	unsigned int	mux_stat_rightbus;
	unsigned char	res10[0xfc];
	unsigned int	div_rightbus;
	unsigned char	res11[0xfc];
	unsigned int	div_stat_rightbus;
	unsigned char	res12[0x1fc];
	unsigned int	gate_ip_rightbus;
	unsigned char	res13[0x15c];
	unsigned int	gate_ip_perir;
	unsigned char	res14[0x9c];
	unsigned int	clkout_rightbus;
	unsigned int	clkout_rightbus_div_stat;
	unsigned char	res15[0x3608];
	unsigned int	epll_lock;
	unsigned char	res16[0xc];
	unsigned int	vpll_lock;
	unsigned char	res17[0xec];
	unsigned int	epll_con0;
	unsigned int	epll_con1;
	unsigned int	epll_con2;
	unsigned char	res18[0x4];
	unsigned int	vpll_con0;
	unsigned int	vpll_con1;
	unsigned int	vpll_con2;
	unsigned char	res19[0xe4];
	unsigned int	src_top0;
	unsigned int	src_top1;
	unsigned char	res20[0x8];
	unsigned int	src_cam;
	unsigned int	src_tv;
	unsigned int	src_mfc;
	unsigned int	src_g3d;
	unsigned char	res21[0x4];
	unsigned int	src_lcd;
	unsigned int	src_isp;
	unsigned int	src_maudio;
	unsigned int	src_fsys;
	unsigned char	res22[0xc];
	unsigned int	src_peril0;
	unsigned int	src_peril1;
	unsigned int	src_cam1;
	unsigned char	res23[0xb4];
	unsigned int	src_mask_top;
	unsigned char	res24[0xc];
	unsigned int	src_mask_cam;
	unsigned int	src_mask_tv;
	unsigned char	res25[0xc];
	unsigned int	src_mask_lcd;
	unsigned int	src_mask_isp;
	unsigned int	src_mask_maudio;
	unsigned int	src_mask_fsys;
	unsigned char	res26[0xc];
	unsigned int	src_mask_peril0;
	unsigned int	src_mask_peril1;
	unsigned char	res27[0xb8];
	unsigned int	mux_stat_top0;
	unsigned int	mux_stat_top1;
	unsigned char	res28[0x10];
	unsigned int	mux_stat_mfc;
	unsigned int	mux_stat_g3d;
	unsigned char	res29[0x28];
	unsigned int	mux_stat_cam1;
	unsigned char	res30[0xb4];
	unsigned int	div_top;
	unsigned char	res31[0xc];
	unsigned int	div_cam;
	unsigned int	div_tv;
	unsigned int	div_mfc;
	unsigned int	div_g3d;
	unsigned char	res32[0x4];
	unsigned int	div_lcd;
	unsigned int	div_isp;
	unsigned int	div_maudio;
	unsigned int	div_fsys0;
	unsigned int	div_fsys1;
	unsigned int	div_fsys2;
	unsigned int	div_fsys3;
	unsigned int	div_peril0;
	unsigned int	div_peril1;
	unsigned int	div_peril2;
	unsigned int	div_peril3;
	unsigned int	div_peril4;
	unsigned int	div_peril5;
	unsigned int	div_cam1;
	unsigned char	res33[0x14];
	unsigned int	div2_ratio;
	unsigned char	res34[0x8c];
	unsigned int	div_stat_top;
	unsigned char	res35[0xc];
	unsigned int	div_stat_cam;
	unsigned int	div_stat_tv;
	unsigned int	div_stat_mfc;
	unsigned int	div_stat_g3d;
	unsigned char	res36[0x4];
	unsigned int	div_stat_lcd;
	unsigned int	div_stat_isp;
	unsigned int	div_stat_maudio;
	unsigned int	div_stat_fsys0;
	unsigned int	div_stat_fsys1;
	unsigned int	div_stat_fsys2;
	unsigned int	div_stat_fsys3;
	unsigned int	div_stat_peril0;
	unsigned int	div_stat_peril1;
	unsigned int	div_stat_peril2;
	unsigned int	div_stat_peril3;
	unsigned int	div_stat_peril4;
	unsigned int	div_stat_peril5;
	unsigned int	div_stat_cam1;
	unsigned char	res37[0x14];
	unsigned int	div2_stat;
	unsigned char	res38[0x29c];
	unsigned int	gate_ip_cam;
	unsigned int	gate_ip_tv;
	unsigned int	gate_ip_mfc;
	unsigned int	gate_ip_g3d;
	unsigned char	res39[0x4];
	unsigned int	gate_ip_lcd;
	unsigned int	gate_ip_isp;
	unsigned char	res40[0x4];
	unsigned int	gate_ip_fsys;
	unsigned char	res41[0x8];
	unsigned int	gate_ip_gps;
	unsigned int	gate_ip_peril;
	unsigned char	res42[0xc];
	unsigned char	res43[0x4];
	unsigned char	res44[0xc];
	unsigned int	gate_block;
	unsigned char	res45[0x8c];
	unsigned int	clkout_cmu_top;
	unsigned int	clkout_cmu_top_div_stat;
	unsigned char	res46[0x3600];
	unsigned int	mpll_lock;
	unsigned char	res47[0xfc];
	unsigned int	mpll_con0;
	unsigned int	mpll_con1;
	unsigned char	res48[0xf0];
	unsigned int	src_dmc;
	unsigned char	res49[0xfc];
	unsigned int	src_mask_dmc;
	unsigned char	res50[0xfc];
	unsigned int	mux_stat_dmc;
	unsigned char	res51[0xfc];
	unsigned int	div_dmc0;
	unsigned int	div_dmc1;
	unsigned char	res52[0xf8];
	unsigned int	div_stat_dmc0;
	unsigned int	div_stat_dmc1;
	unsigned char	res53[0xf8];
	unsigned int	gate_bus_dmc0;
	unsigned int	gate_bus_dmc1;
	unsigned char	res54[0x1f8];
	unsigned int	gate_ip_dmc0;
	unsigned int	gate_ip_dmc1;
	unsigned char	res55[0xf8];
	unsigned int	clkout_cmu_dmc;
	unsigned int	clkout_cmu_dmc_div_stat;
	unsigned char	res56[0x5f8];
	unsigned int	dcgidx_map0;
	unsigned int	dcgidx_map1;
	unsigned int	dcgidx_map2;
	unsigned char	res57[0x14];
	unsigned int	dcgperf_map0;
	unsigned int	dcgperf_map1;
	unsigned char	res58[0x18];
	unsigned int	dvcidx_map;
	unsigned char	res59[0x1c];
	unsigned int	freq_cpu;
	unsigned int	freq_dpm;
	unsigned char	res60[0x18];
	unsigned int	dvsemclk_en;
	unsigned int	maxperf;
	unsigned char	res61[0x8];
	unsigned int	dmc_freq_ctrl;
	unsigned int	dmc_pause_ctrl;
	unsigned int	dddrphy_lock_ctrl;
	unsigned int	c2c_state;
	unsigned char	res62[0x2f60];
	unsigned int	apll_lock;
	unsigned char	res63[0x8];
	unsigned char	res64[0xf4];
	unsigned int	apll_con0;
	unsigned int	apll_con1;
	unsigned char	res65[0xf8];
	unsigned int	src_cpu;
	unsigned char	res66[0x1fc];
	unsigned int	mux_stat_cpu;
	unsigned char	res67[0xfc];
	unsigned int	div_cpu0;
	unsigned int	div_cpu1;
	unsigned char	res68[0xf8];
	unsigned int	div_stat_cpu0;
	unsigned int	div_stat_cpu1;
	unsigned char	res69[0x2f8];
	unsigned int	clk_gate_ip_cpu;
	unsigned char	res70[0xfc];
	unsigned int	clkout_cmu_cpu;
	unsigned int	clkout_cmu_cpu_div_stat;
	unsigned char	res71[0x5f8];
	unsigned int	armclk_stopctrl;
	unsigned int	atclk_stopctrl;
	unsigned char	res72[0x10];
	unsigned char	res73[0x8];
	unsigned int	pwr_ctrl;
	unsigned int	pwr_ctrl2;
	unsigned char	res74[0xd8];
	unsigned int	apll_con0_l8;
	unsigned int	apll_con0_l7;
	unsigned int	apll_con0_l6;
	unsigned int	apll_con0_l5;
	unsigned int	apll_con0_l4;
	unsigned int	apll_con0_l3;
	unsigned int	apll_con0_l2;
	unsigned int	apll_con0_l1;
	unsigned int	iem_control;
	unsigned char	res75[0xdc];
	unsigned int	apll_con1_l8;
	unsigned int	apll_con1_l7;
	unsigned int	apll_con1_l6;
	unsigned int	apll_con1_l5;
	unsigned int	apll_con1_l4;
	unsigned int	apll_con1_l3;
	unsigned int	apll_con1_l2;
	unsigned int	apll_con1_l1;
	unsigned char	res76[0xe0];
	unsigned int	div_iem_l8;
	unsigned int	div_iem_l7;
	unsigned int	div_iem_l6;
	unsigned int	div_iem_l5;
	unsigned int	div_iem_l4;
	unsigned int	div_iem_l3;
	unsigned int	div_iem_l2;
	unsigned int	div_iem_l1;
	unsigned char	res77[0xe0];
	unsigned int	l2_status;
	unsigned char	res78[0xc];
	unsigned int	cpu_status;
	unsigned char	res79[0xc];
	unsigned int	ptm_status;
	unsigned char	res80[0x2edc];
	unsigned int	div_isp0;
	unsigned int	div_isp1;
	unsigned char	res81[0xf8];
	unsigned int	div_stat_isp0;
	unsigned int	div_stat_isp1;
	unsigned char	res82[0x3f8];
	unsigned int	gate_ip_isp0;
	unsigned int	gate_ip_isp1;
	unsigned char	res83[0x1f8];
	unsigned int	clkout_cmu_isp;
	unsigned int	clkout_cmu_ispd_div_stat;
	unsigned char	res84[0xf8];
	unsigned int	cmu_isp_spar0;
	unsigned int	cmu_isp_spar1;
	unsigned int	cmu_isp_spar2;
	unsigned int	cmu_isp_spar3;
};

/* CLK_DIV_CPU0 */
#define CORE_RATIO		0x0
#define COREM0_RATIO		0x3
#define COREM1_RATIO		0x7
#define PERIPH_RATIO		0x0
#define ATB_RATIO		0x4
#define PCLK_DBG_RATIO		0x1
#define APLL_RATIO		0x1
#define CORE2_RATIO		0x0
#define CLK_DIV_CPU0_VAL	(CORE2_RATIO << 28 \
				| (APLL_RATIO << 24) \
				| (PCLK_DBG_RATIO << 20) \
				| (ATB_RATIO << 16) \
				| (PERIPH_RATIO << 12) \
				| (COREM1_RATIO << 8) \
				| (COREM0_RATIO << 4) \
				| (CORE_RATIO << 0))

/* CLK_DIV_CPU1 */
#define COPY_RATIO		0x4
#define HPM_RATIO		0x0
#define CORES_RATIO		0x0
#define CLK_DIV_CPU1_VAL	((CORES_RATIO << 8) \
				| (HPM_RATIO << 4) \
				| (COPY_RATIO << 0))

/* CLK_DIV_DMC0 */
#define DMCP_RATIO		0x1
#define DMCD_RATIO		0x1
#define DMC_RATIO		0x1
#define DPHY_RATIO		0x1
#define ACP_PCLK_RATIO		0x1
#define ACP_RATIO		0x3
#define CLK_DIV_DMC0_VAL	((DMCP_RATIO << 20) \
				| (DMCD_RATIO << 16) \
				| (DMC_RATIO << 12) \
				| (DPHY_RATIO << 8) \
				| (ACP_PCLK_RATIO << 4)	\
				| (ACP_RATIO << 0))

/* CLK_DIV_DMC1 */
#define G2D_ACP_RATIO		0x3
#define C2C_RATIO		0x1
#define PWI_RATIO		0x0
#define C2C_ACLK_RATIO		0x1
#define DVSEM_RATIO		0x1
#define DPM_RATIO		0x1
#define CLK_DIV_DMC1_VAL	((DPM_RATIO << 24) \
				| (DVSEM_RATIO << 16) \
				| (C2C_ACLK_RATIO << 12) \
				| (PWI_RATIO << 8) \
				| (C2C_RATIO << 4) \
				| (G2D_ACP_RATIO << 0))

/* CLK_DIV_TOP */
#define ACLK_200_RATIO		0x3
#define ACLK_100_RATIO		0x7
#define ACLK_160_RATIO		0x4
#define ACLK_133_RATIO		0x5
#define ONENAND_RATIO		0x0
#define ACLK_266_GPS_RATIO	0x2
#define	ACLK_400_MCUISP_RATIO	0x1
#define CLK_DIV_TOP_VAL		((ACLK_400_MCUISP_RATIO << 24) \
				| (ACLK_266_GPS_RATIO << 20) \
				| (ONENAND_RATIO << 16)	\
				| (ACLK_133_RATIO << 12)\
				| (ACLK_160_RATIO << 8)	\
				| (ACLK_100_RATIO << 4)	\
				| (ACLK_200_RATIO << 0))

/* CLK_DIV_LEFTBUS */
#define GPL_RATIO		0x1
#define GDL_RATIO		0x3
#define CLK_DIV_LEFTBUS_VAL	((GPL_RATIO << 4) | (GDL_RATIO))

/* CLK_DIV_RIGHTBUS */
#define GPR_RATIO		0x1
#define GDR_RATIO		0x3
#define CLK_DIV_RIGHTBUS_VAL	((GPR_RATIO << 4) | (GDR_RATIO))

/* CLK_DIV_PERIL0 */
#define UART4_RATIO		0x7
#define UART3_RATIO		0x7
#define UART2_RATIO		0x7
#define UART1_RATIO		0x7
#define UART0_RATIO		0x7
#define CLK_DIV_PERIL0_VAL	((UART4_RATIO << 16) \
				| (UART3_RATIO << 12) \
				| (UART2_RATIO << 8) \
				| (UART1_RATIO << 4) \
				| (UART0_RATIO << 0))

/* CLK_DIV_FSYS0 */
#define MIPIHSI_RATIO		0x3
#define CLK_DIV_FSYS0_VAL	((MIPIHSI_RATIO <<20))

/* CLK_DIV_FSYS1 */
#define MMC1_PRE_RATIO		0x1
#define MMC1_RATIO		0x7
#define MMC0_PRE_RATIO		0x1
#define MMC0_RATIO		0x7
#define CLK_DIV_FSYS1_VAL	((MMC1_PRE_RATIO << 24) \
				| (MMC1_RATIO << 16) \
				| (MMC0_PRE_RATIO << 8) \
				| (MMC0_RATIO << 0))

/* CLK_DIV_FSYS2 */
#define MMC3_PRE_RATIO		0x1
#define MMC3_RATIO		0x7
#define MMC2_PRE_RATIO		0x1
#define MMC2_RATIO		0x7
#define CLK_DIV_FSYS2_VAL	((MMC3_PRE_RATIO << 24) \
				| (MMC3_RATIO << 16) \
				| (MMC2_PRE_RATIO << 8) \
				| (MMC2_RATIO << 0))

/* CLK_DIV_FSYS3 */
#define MMC4_PRE_RATIO		0x0
#define MMC4_RATIO		0x7
#define CLK_DIV_FSYS3_VAL	((MMC4_PRE_RATIO << 8) \
				| (MMC4_RATIO << 0))

/* A/M PLL_CON1 */
#define AFC(x)                  ((x) & 0x1f)
#define LOCK_CON_DLY(x)         (((x) & 0x1f) << 8)
#define LOCK_CON_IN(x)          (((x) & 0x3) << 12)
#define LOCK_CON_OUT(x)         (((x) & 0x3) << 14)
#define FEED_EN(x)              (((x) & 0x1) << 16)
#define AFC_ENB(x)              (((x) & 0x1) << 20)
#define DCC_ENB(x)              (((x) & 0x1) << 21)
#define BYPASS(x)               (((x) & 0x1) << 22)
#define RESV0(x)                (((x) & 0x1) << 23)
#define RESV1(x)                (((x) & 0x1) << 24)

/* APLL_CON1 */
#define APLL_CON1_VAL		(AFC(0) | LOCK_CON_DLY(8) | LOCK_CON_IN(3) \
				| LOCK_CON_OUT(0) | FEED_EN(0) | AFC_ENB(0) \
				| DCC_ENB(1) | BYPASS(0) | RESV0(0) | RESV1(0))

/* MPLL_CON1 */
#define MPLL_CON1_VAL		(AFC(0) | LOCK_CON_DLY(8) | LOCK_CON_IN(3) \
				| LOCK_CON_OUT(0) | FEED_EN(0) | AFC_ENB(0) \
				| DCC_ENB(1) | BYPASS(0) | RESV0(0) | RESV1(0))

/* A/M/EV PLL_CON0 */
#define SDIV(x)                 ((x) & 0x7)
#define PDIV(x)                 (((x) & 0x3f) << 8)
#define MDIV(x)                 (((x) & 0x3ff) << 16)
#define FSEL(x)                 (((x) & 0x1) << 27)
#define PLL_LOCKED_BIT          (0x1 << 29)
#define PLL_ENABLE(x)           (((x) & 0x1) << 31)

/* APLL_CON0 */
#define APLL_CON0_VAL		(SDIV(0) | PDIV(3) | MDIV(125) | FSEL(0) | PLL_ENABLE(1))

/* MPLL_CON0 */
#define  MPLL_CON0_VAL		(SDIV(0) | PDIV(3) | MDIV(100) | FSEL(0) | PLL_ENABLE(1))

/* EPLL_CON0 */
#define EPLL_CON0_VAL		(SDIV(2) | PDIV(2) | MDIV(64) | FSEL(0) | PLL_ENABLE(1))

/* VPLL_CON0 */
#define VPLL_CON0_VAL		(SDIV(3) | PDIV(3) | MDIV(54) | FSEL(0) | PLL_ENABLE(1))

/* E/V PLL_CON2 */
#define ICP_BOOST(x)            ((x) & 0x3)
#define EV_FSEL(x)              (((x) & 0x1) << 2)
#define FVCO_EN(x)              (((x) & 0x1) << 3)
#define EV_BYPASS(x)            (((x) & 0x1) << 4)
#define SSCG_EN(x)              (((x) & 0x1) << 5)
#define EV_AFC_ENB(x)           (((x) & 0x1) << 6)
#define EV_DCC_ENB(x)              (((x) & 0x1) << 7)
#define EXTAFC(x)               (((x) & 0x1f) << 8)

/* EPLL_CON2 */
#define EPLL_CON2_VAL		(ICP_BOOST(0) | EV_FSEL(1) | FVCO_EN(1) | EV_BYPASS(1) \
				| SSCG_EN(0) | EV_AFC_ENB(0) | EV_DCC_ENB(1) | EXTAFC(0))

/* VPLL_CON2 */
#define VPLL_CON2_VAL		(ICP_BOOST(0) | EV_FSEL(1) | FVCO_EN(1) | EV_BYPASS(1) \
				| SSCG_EN(0) | EV_AFC_ENB(0) | EV_DCC_ENB(1) | EXTAFC(0))

/* A/M/E/V PLL_LOCK */
#define PLL_LOCKTIME(x)         ((x) & 0xffff)

#define APLL_LOCKTIME		PLL_LOCKTIME(PDIV(3) * 270)
#define MPLL_LOCKTIME		PLL_LOCKTIME(PDIV(3) * 270)
#define EPLL_LOCKTIME		PLL_LOCKTIME(PDIV(2) * 270)
#define VPLL_LOCKTIME		PLL_LOCKTIME(PDIV(3) * 270)

/* CLK_SRC_CPU */
#define MUX_APLL_SEL		0x1
#define MUX_CORE_SEL		0x0
#define MUX_HPM_SEL		0x0
#define MUX_MPLL_USER_SEL_C	0x1
#define CLK_SRC_CPU_VAL		((MUX_MPLL_USER_SEL_C << 24) \
				| (MUX_HPM_SEL << 20) \
				| (MUX_CORE_SEL << 16) \
				| (MUX_APLL_SEL << 0))

/* CLK_SRC_DMC */
#define MUX_C2C_SEL(x)		((x) & 0x1)
#define MUX_DMC_BUS_SEL(x)	(((x) & 0x1) << 4)
#define MUX_DPHY_SEL(x)		(((x) & 0x1) << 8)
#define MUX_MPLL_SEL(x)		(((x) & 0x1) << 12)
#define MUX_PWI_SEL(x)		(((x) & 0xf) << 16)
#define MUX_G2D_ACP0_SEL(x)	(((x) & 0x1) << 20)
#define MUX_G2D_ACP1_SEL(x)	(((x) & 0x1) << 24)
#define MUX_G2D_ACP_SEL(x)	(((x) & 0x1) << 28)
#define CLK_SRC_DMC_VAL		(MUX_C2C_SEL(0) | MUX_DMC_BUS_SEL(0) | MUX_DPHY_SEL(0) \
				| MUX_MPLL_SEL(1) | MUX_PWI_SEL(0) | MUX_G2D_ACP0_SEL(0) \
				| MUX_G2D_ACP1_SEL(0) | MUX_G2D_ACP_SEL(0))

/* CLK_SRC_TOP0 */
#define MUX_ONENAND_1_SEL(x)    ((x) & 0x1)
#define MUX_EPLL_SEL(x)         (((x) & 0x1) << 4)
#define MUX_VPLL_SEL(x)         (((x) & 0x1) << 8)
#define MUX_ACLK_200_SEL(x)     (((x) & 0x1) << 12)
#define MUX_ACLK_100_SEL(x)     (((x) & 0x1) << 16)
#define MUX_ACLK_160_SEL(x)     (((x) & 0x1) << 20)
#define MUX_ACLK_133_SEL(x)     (((x) & 0x1) << 24)
#define MUX_ONENAND_SEL(x)      (((x) & 0x1) << 28)
#define CLK_SRC_TOP0_VAL	(MUX_ONENAND_1_SEL(0) | MUX_EPLL_SEL(1) | MUX_VPLL_SEL(1) \
				| MUX_ACLK_200_SEL(0) | MUX_ACLK_100_SEL(0) | MUX_ACLK_160_SEL(0) \
				| MUX_ACLK_133_SEL(0) | MUX_ONENAND_SEL(1))

/* CLK_SRC_TOP1 */
#define MUX_ACLK_266_GPS_SEL(x)        (((x) & 0x1) << 4)
#define MUX_ACLK_400_MCUISP_SEL(x)     (((x) & 0x1) << 8)
#define MUX_MPLL_USER_SEL_T(x)         (((x) & 0x1) << 12)
#define MUX_ACLK_266_GPS_SUB_SEL(x)    (((x) & 0x1) << 16)
#define MUX_ACLK_200_SUB_SEL(x)        (((x) & 0x1) << 20)
#define MUX_ACLK_400_MCUISP_SUB_SEL(x) (((x) & 0x1) << 24)
#define CLK_SRC_TOP1_VAL		(MUX_ACLK_266_GPS_SEL(0) | MUX_ACLK_400_MCUISP_SEL(0) \
					| MUX_MPLL_USER_SEL_T(1) | MUX_ACLK_266_GPS_SUB_SEL(1) \
					| MUX_ACLK_200_SUB_SEL(1) | MUX_ACLK_400_MCUISP_SUB_SEL(1))

/* CLK_SRC_LEFTBUS */
#define	MUX_GDL_SEL(x)		((x) & 0x1)
#define	MUX_MPLL_USER_SEL_L(x)	(((x) & 0x1) << 4)
#define CLK_SRC_LEFTBUS_VAL	(MUX_GDL_SEL(0) | MUX_MPLL_USER_SEL_L(1))

/* CLK_SRC_RIGHTBUS */
#define MUX_GDR_SEL(x)		((x) & 0x1)
#define MUX_MPLL_USER_SEL_R(x)	(((x) & 0x1) << 4)
#define CLK_SRC_RIGHTBUS_VAL	(MUX_GDR_SEL(0) | MUX_MPLL_USER_SEL_R(1))

/* CLK_SRC_PERIL0 */
#define UART0_SEL(x)		((x) & 0xf)
#define UART1_SEL(x)		(((x) & 0xf) << 4)
#define UART2_SEL(x)		(((x) & 0xf) << 8)
#define UART3_SEL(x)		(((x) & 0xf) << 12)
#define UART4_SEL(x)		(((x) & 0xf) << 16)
#define CLK_SRC_PERIL0_VAL	(UART0_SEL(6) | UART1_SEL(6) | UART2_SEL(6) \
				| UART3_SEL(6) | UART4_SEL(6))

/* CLK_SRC_FSYS */
#define MMC1_SEL(x)		(((x) & 0xf) << 4)
#define MMC2_SEL(x)		(((x) & 0xf) << 8)
#define MMC3_SEL(x)		(((x) & 0xf) << 12)
#define MMC4_SEL(x)		(((x) & 0xf) << 16)
#define MIPIHSI_SEL(x)		(((x) & 0x1) << 24)
#define CLK_SRC_FSYS_VAL	(MMC1_SEL(6) | MMC2_SEL(6) | MMC3_SEL(6) \
				| MMC4_SEL(6) | MIPIHSI_SEL(0))
#endif
