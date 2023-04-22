#ifndef __S5P_DMC_H_
#define __S5P_DMC_H_

struct exynos4_dmc {
	unsigned int concontrol;
	unsigned int memcontrol;
	unsigned int memconfig0;
	unsigned int memconfig1;
	unsigned int directcmd;
	unsigned int prechconfig;
	unsigned int phycontrol0;
	unsigned int phycontrol1;
	unsigned int phycontrol2;
	unsigned int phycontrol3;
	unsigned int pwrdnconfig;
	unsigned char res1[0x4];
	unsigned int timingref;
	unsigned int timingrow;
	unsigned int timingdata;
	unsigned int timingpower;
	unsigned int phystatus;
	unsigned int phyzqcontrol;
	unsigned int chip0status;
	unsigned int chip1status;
	unsigned int arefstatus;
	unsigned int mrstatus;
	unsigned int phytest0;
	unsigned int phytest1;
	unsigned int qoscontrol0;
	unsigned int qosconfig0;
	unsigned int qoscontrol1;
	unsigned int qosconfig1;
	unsigned int qoscontrol2;
	unsigned int qosconfig2;
	unsigned int qoscontrol3;
	unsigned int qosconfig3;
	unsigned int qoscontrol4;
	unsigned int qosconfig4;
	unsigned int qoscontrol5;
	unsigned int qosconfig5;
	unsigned int qoscontrol6;
	unsigned int qosconfig6;
	unsigned int qoscontrol7;
	unsigned int qosconfig7;
	unsigned int qoscontrol8;
	unsigned int qosconfig8;
	unsigned int qoscontrol9;
	unsigned int qosconfig9;
	unsigned int qoscontrol10;
	unsigned int qosconfig10;
	unsigned int qoscontrol11;
	unsigned int qosconfig11;
	unsigned int qoscontrol12;
	unsigned int qosconfig12;
	unsigned int qoscontrol13;
	unsigned int qosconfig13;
	unsigned int qoscontrol14;
	unsigned int qosconfig14;
	unsigned int qoscontrol15;
	unsigned int qosconfig15;
	unsigned int qostimeout0;
	unsigned int qostimeout1;
	unsigned char res2[0x8];
	unsigned int ivcontrol;
	unsigned char res3[0x8];
	unsigned int perevconfig;
	unsigned char res4[0xDF00];
	unsigned int pmnc_ppc_a;
	unsigned char res5[0xC];
	unsigned int cntens_ppc_a;
	unsigned char res6[0xC];
	unsigned int cntenc_ppc_a;
	unsigned char res7[0xC];
	unsigned int intens_ppc_a;
	unsigned char res8[0xC];
	unsigned int intenc_ppc_a;
	unsigned char res9[0xC];
	unsigned int flag_ppc_a;
	unsigned char res10[0xAC];
	unsigned int ccnt_ppc_a;
	unsigned char res11[0xC];
	unsigned int pmcnt0_ppc_a;
	unsigned char res12[0xC];
	unsigned int pmcnt1_ppc_a;
	unsigned char res13[0xC];
	unsigned int pmcnt2_ppc_a;
	unsigned char res14[0xC];
	unsigned int pmcnt3_ppc_a;
	unsigned char res15[0xEBC];
	unsigned int pmnc_ppc_m;
	unsigned char res16[0xC];
	unsigned int cntens_ppc_m;
	unsigned char res17[0xC];
	unsigned int cntenc_ppc_m;
	unsigned char res18[0xC];
	unsigned int intens_ppc_m;
	unsigned char res19[0xC];
	unsigned int intenc_ppc_m;
	unsigned char res20[0xC];
	unsigned int flag_ppc_m;
	unsigned char res21[0xAC];
	unsigned int ccnt_ppc_m;
	unsigned char res22[0xC];
	unsigned int pmcnt0_ppc_m;
	unsigned char res23[0xC];
	unsigned int pmcnt1_ppc_m;
	unsigned char res24[0xC];
	unsigned int pmcnt2_ppc_m;
	unsigned char res25[0xC];
	unsigned int pmcnt3_ppc_m;
};

/* Bus Configuration Register Address */
#define ASYNC_CONFIG		0x10010350

#define DIRECT_CMD_NOP	        0x07000000
#define DIRECT_CMD_ZQ   	0x0a000000
#define DIRECT_CMD_CHIP1_SHIFT	(1 << 20)
#define MEM_TIMINGS_MSR_COUNT	4
#define CTRL_START	        (1 << 0)
#define CTRL_DLL_ON	        (1 << 1)
#define AREF_EN		        (1 << 5)

struct mem_timings {
	unsigned direct_cmd_msr[MEM_TIMINGS_MSR_COUNT];
	unsigned timingref;
	unsigned timingrow;
	unsigned timingdata;
	unsigned timingpower;
	unsigned zqcontrol;
	unsigned control0;
	unsigned control1;
	unsigned control2;
	unsigned concontrol;
	unsigned prechconfig;
	unsigned memcontrol;
	unsigned memconfig0;
	unsigned memconfig1;
	unsigned dll_resync;
	unsigned dll_on;
};

/* MIU */
/* MIU Config Register Offsets*/
#define APB_SFR_INTERLEAVE_CONF_OFFSET	0x400
#define APB_SFR_ARBRITATION_CONF_OFFSET	0xC00

/* Interleave: 2Bit, Interleave_bit1: 0x15, Interleave_bit0: 0x7 */
#define APB_SFR_INTERLEAVE_CONF_VAL	0x20001507
#define APB_SFR_ARBRITATION_CONF_VAL	0x00000001

#define DIRECT_CMD1		0x00020000
#define DIRECT_CMD2		0x00030000
#define DIRECT_CMD3		0x00010002
#define DIRECT_CMD4		0x00000328

#define TIMINGREF_VAL		0x000000BB
#define TIMINGROW_VAL		0x4046654f
#define	TIMINGDATA_VAL		0x46400506
#define	TIMINGPOWER_VAL		0x52000A3C

#define CTRL_ZQ_MODE_NOTERM	(0x1 << 0)
#define CTRL_ZQ_START		(0x1 << 1)
#define CTRL_ZQ_DIV		(0 << 4)
#define CTRL_ZQ_MODE_DDS	(0x7 << 8)
#define CTRL_ZQ_MODE_TERM	(0x2 << 11)
#define CTRL_ZQ_FORCE_IMPN	(0x5 << 14)
#define CTRL_ZQ_FORCE_IMPP	(0x6 << 17)
#define CTRL_DCC		(0xE38 << 20)
#define ZQ_CONTROL_VAL		(CTRL_ZQ_MODE_NOTERM | CTRL_ZQ_START\
				| CTRL_ZQ_DIV | CTRL_ZQ_MODE_DDS\
				| CTRL_ZQ_MODE_TERM | CTRL_ZQ_FORCE_IMPN\
				| CTRL_ZQ_FORCE_IMPP | CTRL_DCC)

#define CTRL_OFF		(0 << 0)
#define CTRL_DLL_OFF		(0 << 1)
#define CTRL_HALF		(0 << 2)
#define CTRL_DFDQS		(1 << 3)
#define DQS_DELAY		(0 << 4)
#define CTRL_START_POINT	(0x10 << 8)
#define CTRL_INC		(0x10 << 16)
#define CTRL_FORCE		(0x71 << 24)
#define CONTROL0_VAL		(CTRL_OFF | CTRL_DLL_OFF | CTRL_HALF\
				| CTRL_DFDQS | DQS_DELAY | CTRL_START_POINT\
				| CTRL_INC | CTRL_FORCE)

#define CTRL_SHIFTC		(0x6 << 0)
#define CTRL_REF		(8 << 4)
#define CTRL_SHGATE		(1 << 29)
#define TERM_READ_EN		(1 << 30)
#define TERM_WRITE_EN		(1 << 31)
#define CONTROL1_VAL		(CTRL_SHIFTC | CTRL_REF | CTRL_SHGATE\
				| TERM_READ_EN | TERM_WRITE_EN)

#define CONTROL2_VAL		0x00000000

#define ASYNC			(0 << 0)
#define CLK_RATIO		(1 << 1)
#define DIV_PIPE		(1 << 3)
#define AWR_ON			(1 << 4)
#define AREF_DISABLE		(0 << 5)
#define DRV_TYPE_DISABLE	(0 << 6)
#define CHIP0_NOT_EMPTY		(0 << 8)
#define CHIP1_NOT_EMPTY		(0 << 9)
#define DQ_SWAP_DISABLE		(0 << 10)
#define QOS_FAST_DISABLE	(0 << 11)
#define RD_FETCH		(0x3 << 12)
#define TIMEOUT_LEVEL0		(0xFFF << 16)
#define CONCONTROL_VAL		(ASYNC | CLK_RATIO | DIV_PIPE | AWR_ON\
				| AREF_DISABLE | DRV_TYPE_DISABLE\
				| CHIP0_NOT_EMPTY | CHIP1_NOT_EMPTY\
				| DQ_SWAP_DISABLE | QOS_FAST_DISABLE\
				| RD_FETCH | TIMEOUT_LEVEL0)

#define TP_CNT			(0xff << 24)
#define PRECHCONFIG		TP_CNT

#define CLK_STOP_DISABLE	(0 << 1)
#define DPWRDN_DISABLE		(0 << 2)
#define DPWRDN_TYPE		(0 << 3)
#define TP_DISABLE		(0 << 4)
#define DSREF_DIABLE		(0 << 5)
#define ADD_LAT_PALL		(1 << 6)
#define MEM_TYPE_DDR3		(0x6 << 8)
#define MEM_WIDTH_32		(0x2 << 12)
#define NUM_CHIP_2		(0 << 16)
#define BL_8			(0x3 << 20)
#define MEMCONTROL_VAL		(CLK_STOP_DISABLE | DPWRDN_DISABLE\
				| DPWRDN_TYPE | TP_DISABLE | DSREF_DIABLE\
				| ADD_LAT_PALL | MEM_TYPE_DDR3 | MEM_WIDTH_32\
				| NUM_CHIP_2 | BL_8)

#define CHIP_BANK_8		(0x3 << 0)
#define CHIP_ROW_14		(0x3 << 4)
#define CHIP_COL_10		(0x3 << 8)
#define CHIP_MAP_INTERLEAVED	(1 << 12)
#define CHIP_MASK		(0xC0 << 16)
#define CHIP0_BASE		(0x40 << 24)
#define CHIP1_BASE		(0x80 << 24)
#define MEMCONFIG0_VAL		(CHIP_BANK_8 | CHIP_ROW_14 | CHIP_COL_10\
				| CHIP_MAP_INTERLEAVED | CHIP_MASK | CHIP0_BASE)
#define MEMCONFIG1_VAL		(CHIP_BANK_8 | CHIP_ROW_14 | CHIP_COL_10\
				| CHIP_MAP_INTERLEAVED | CHIP_MASK | CHIP1_BASE)

#define FORCE_DLL_RESYNC	3
#define DLL_CONTROL_ON		1

#endif
