/*
 * (C) Copyright 2006 OpenMoko, Inc.
 * Author: Harald Welte <laforge@openmoko.org>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#include <nand.h>
#include <asm/io.h>

#define NFCONF         	(*(volatile unsigned int *) 0x4E000000)
#define NFCONT         	(*(volatile unsigned int *) 0x4E000004)
#define NFCMMD         	(*(volatile unsigned int *) 0x4E000008)
#define NFADDR         	(*(volatile unsigned int *) 0x4E00000C)
#define NFDATA         	(*(volatile unsigned char *) 0x4E000010) //注意：类型char
#define NFMECCD0     	(*(volatile unsigned int *) 0x4E000014)
#define NFMECCD1     	(*(volatile unsigned int *) 0x4E000018)
#define NFSECCD     	(*(volatile unsigned int *) 0x4E00001C)
#define NFSTAT         	(*(volatile unsigned int *) 0x4E000020)
#define NFESTAT0     	(*(volatile unsigned int *) 0x4E000024)
#define NFESTAT1     	(*(volatile unsigned int *) 0x4E000028)
#define NFMECC0     	(*(volatile unsigned int *) 0x4E00002C)
#define NFMECC1     	(*(volatile unsigned int *) 0x4E000030)
#define NFMECC         	(*(volatile unsigned int *) 0x4E000034)
#define NFSBLK         	(*(volatile unsigned int *) 0x4E000038)
#define NFEBLK         	(*(volatile unsigned int *) 0x4E00003C)

#define TACLS    0x0
#define TWRPH0     0x03
#define TWRPH1     0x0    

static void xf2440_nand_select_chip(struct mtd_info *mtd, int chipnr)
{
	switch (chipnr) {
	case -1:
		NFCONT |= (1<<1);
		//printf("NFCONT |= (1<<1); \n");
		break;
	case 0:
		NFCONT &= ~(1<<1);
		//printf("NFCONT &= ~(1<<1);");
		break;

	default:
		BUG();
	}
}
static void xf2440_nand_cmd_ctrl(struct mtd_info *mtd, int dat, unsigned int ctrl)
{
	if (dat == NAND_CMD_NONE)
		return;

	if (ctrl & NAND_CLE)
	{
		// 发送命令
		NFCMMD = dat;
		//printf("NFCMMD = dat;");
	}
	else
	{
		// 发送地址
		NFADDR = dat;
		//printf("NFADDR = dat;");
	}
}

static int xf2440_nand_dev_ready(struct mtd_info *mtd)
{
	unsigned long val = 0;

	val = NFSTAT;
	
	return (val & (1<<0));
}


static void nand_reset(void)
{   
	xf2440_nand_select_chip(0, 0);

	// send cmd reset
	xf2440_nand_cmd_ctrl(0, NAND_CMD_RESET, NAND_CLE);

	// wait ready
	while(!xf2440_nand_dev_ready(0))
		;
	
	xf2440_nand_select_chip(0, -1);
}


int board_nand_init(struct nand_chip *nand)
{
	// init nandflash
	NFCONF = (TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4);    
	NFCONT = (0x01<<4)|(0x01<<1)|(0x01<<0);

	nand_reset();
	
	nand->select_chip 	= xf2440_nand_select_chip;
	nand->cmd_ctrl 	 	= xf2440_nand_cmd_ctrl;
	nand->dev_ready		= xf2440_nand_dev_ready;

	return 0;
}






