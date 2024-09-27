/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2019 NXP
 */

#ifndef __PIMX_H
#define __PIMX_H

#include <linux/sizes.h>
#include <linux/stringify.h>
#include <asm/arch/imx-regs.h>

#define CFG_SYS_UBOOT_BASE	    (QSPI0_AMBA_BASE + CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR * 512)

#if defined(CONFIG_CMD_NET)
#	define CFG_FEC_MXC_PHYADDR  1
#	define PHY_ANEG_TIMEOUT     20000
#endif

#define BOOT_TARGET_DEVICES(func) \
       func(MMC, mmc, 1) \
       func(MMC, mmc, 2)

#include <config_distro_bootcmd.h>

/* Initial environment variables */
#define CFG_EXTRA_ENV_SETTINGS \
	BOOTENV \
	"scriptaddr=" __stringify(CONFIG_SYS_LOAD_ADDR) "\0" \
	"kernel_addr_r=" __stringify(CONFIG_SYS_LOAD_ADDR) "\0" \
	"image=Image\0" \
	"console=ttymxc1,115200 earlycon=ec_imx6q,0x30890000,115200\0" \
	"fdt_addr_r=0x43000000\0" \
	"boot_fdt=try\0" \
	"fdtfile=" CONFIG_DEFAULT_FDT_FILE "\0" \
	"initrd_addr=0x43800000\0" \
	"bootm_size=0x10000000\0" \
	"mmcdev="__stringify(CONFIG_SYS_MMC_ENV_DEV)"\0" \
	"mmcpart=1\0" \
	"mmcroot=/dev/mmcblk1p2 rootwait rw\0" \
	"mmcautodetect=yes\0" \
	"mmcargs=setenv bootargs console=${console} console=tty1 root=${mmcroot}\0" \
	"loadimage=load mmc ${mmcdev}:${mmcpart} ${loadaddr} ${image}\0" \
	"loadfdt=load mmc ${mmcdev}:${mmcpart} ${fdt_addr_r} ${fdtfile}\0" \
	"mmcboot=echo Booting from mmc ...; " \
		"run mmcargs; " \
		"if run loadfdt; then " \
			"booti ${loadaddr} - ${fdt_addr_r}; " \
		"else " \
			"echo WARN: Cannot load the DT; " \
		"fi;\0" \
	"bootcmd=echo Running BSP bootcmd ...; " \
		"mmc dev ${mmcdev}; if mmc rescan; then " \
			"if run loadimage; then " \
				"run mmcboot; " \
			"else run netboot; " \
			"fi; " \
	   "fi;\0"

/* Link Definitions */
#define CFG_SYS_INIT_RAM_ADDR	0x40000000
#define CFG_SYS_INIT_RAM_SIZE	0x80000

/* Totally 4GB DDR */
#define CFG_SYS_SDRAM_BASE		0x40000000
#define PHYS_SDRAM			    0x40000000
#define PHYS_SDRAM_SIZE			0x100000000	/* 4 GB */

#endif
