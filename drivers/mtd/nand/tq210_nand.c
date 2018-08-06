/*
 * (C) Copyright 2006 OpenMoko, Inc.
 * Author: Harald Welte <laforge@openmoko.org>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#include <nand.h>
#include <asm/io.h>

#define MP0_1CON  		(*(volatile u32 *)0xE02002E0)
#define	MP0_3CON  		(*(volatile u32 *)0xE0200320)
#define	MP0_6CON 		(*(volatile u32 *)0xE0200380)

#define	NFCONF  		(*(volatile u32 *)0xB0E00000) 
#define	NFCONT  		(*(volatile u32 *)0xB0E00004) 	
#define	NFCMMD  		(*(volatile u32 *)0xB0E00008) 
#define	NFADDR  		(*(volatile u32 *)0xB0E0000C)
#define	NFDATA  		(*(volatile u8 *)0xB0E00010)
#define	NFSTAT  		(*(volatile u32 *)0xB0E00028)

#define	NFMECCD0  		(*(volatile u32 *)0xB0E00014)
#define	NFMECCD1  		(*(volatile u32 *)0xB0E00018)
#define	NFECCPRGECC0 	(*(volatile u32 *)0xB0E20090)
#define	NFECCPRGECC1 	(*(volatile u32 *)0xB0E20094)
#define	NFECCPRGECC2 	(*(volatile u32 *)0xB0E20098)
#define	NFECCPRGECC3 	(*(volatile u32 *)0xB0E2009C)
#define	NFECCCONF  		(*(volatile u32 *)0xB0E20000)
#define	NFECCCONT  		(*(volatile u32 *)0xB0E20020)
#define	NFECCSTAT  		(*(volatile u32 *)0xB0E20030)

#define NFECCSECSTAT	(*(volatile u32 *)0xB0E20040)
#define NFECCERL0		(*(volatile u32 *)0xB0E200C0)
#define NFECCERL1		(*(volatile u32 *)0xB0E200C4)
#define NFECCERL2		(*(volatile u32 *)0xB0E200C8)
#define NFECCERL3		(*(volatile u32 *)0xB0E200CC)
#define NFECCERP0		(*(volatile u32 *)0xB0E200F0)
#define NFECCERP1		(*(volatile u32 *)0xB0E200F4)
#define NFECCERP2		(*(volatile u32 *)0xB0E200F8)
#define NFECCERP3		(*(volatile u32 *)0xB0E200FC)


#define CONFIG_TQ210_NAND_HWECC			1

/* add by zjh */
static struct nand_ecclayout nand_oob_64 = {
	.eccbytes = 52,		/* 2048 / 512 * 13 */
	.eccpos = {	12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
				22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
				32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 
				42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
				52, 53, 54, 55, 56, 57, 58, 59, 60, 61,
				62, 63},
	/* 0Âíå1Áî®‰∫é‰øùÂ≠òÂùèÂùóÊ†áËÆ∞Ôºå12~63‰øùÂ≠òeccÔºåÂâ©‰Ωô2~11‰∏∫free */
	.oobfree = {
			{.offset = 2,
			.length = 10}
		}
};


/* ∆¨—° */
static void  test_nand_select_chip(void)
{
	NFCONT &= ~(1 << 1);
}

/* »°œ˚∆¨—° */
static void  test_nand_deselect_chip(void)
{
	NFCONT |= (1 << 1);
}

/* ∑¢√¸¡Ó */
static void  test_nand_cmd(u32 cmd)
{
	NFCMMD = cmd;
}



/* ∂¡1byte ˝æ› */
static u8  test_nand_read(void)
{
	return NFDATA;
}







/* ∂¡NAND ID */
void test_nand_read_id(u8 id[])
{
	int i;
	test_nand_select_chip();
	test_nand_cmd(0x90);
	NFADDR = 0x00;
	for (i = 0; i < 5; i++)
	{
		id[i] = test_nand_read();
		printf("id[%d]£∫0x%02x\n", i, id[i]);
	}
		
		

	test_nand_deselect_chip();
}
   

static void tq210_nand_select_chip(struct mtd_info *mtd, int chipnr)
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
static void tq210_nand_cmd_ctrl(struct mtd_info *mtd, int dat, unsigned int ctrl)
{
	if (dat == NAND_CMD_NONE)
		return;

	if (ctrl & NAND_CLE)
	{
		// ∑¢ÀÕ√¸¡Ó
		NFCMMD = dat;
		//printf("NFCMMD = dat;");
	}
	else
	{
		// ∑¢ÀÕµÿ÷∑
		NFADDR = dat;
		//printf("NFADDR = dat;");
	}
}

static int tq210_nand_dev_ready(struct mtd_info *mtd)
{
	unsigned long val = 0;

	val = NFSTAT;
	
	return (val & (1<<0));
}


static void tq210_nand_reset(void)
{   
	tq210_nand_select_chip(0, 0);

	// send cmd reset
	tq210_nand_cmd_ctrl(0, NAND_CMD_RESET, NAND_CLE);

	// wait ready
	while(!tq210_nand_dev_ready(0))
		;
	
	tq210_nand_select_chip(0, -1);
}

#ifdef CONFIG_TQ210_NAND_HWECC
void tq210_nand_enable_hwecc(struct mtd_info *mtd, int mode)
{
	NFCONF |= (3<<23);
	
	if (mode == NAND_ECC_READ)
	{
		NFECCCONT &= ~(0x1 << 16);	/* set 8/12/16bit Ecc direction to Encoding */
		NFECCSTAT |= (1 << 24);		/* clear 8/12/16bit ecc encode done */
	}
	else
	{
		NFECCCONT |= (0x1 << 16);	/* set 8/12/16bit Ecc direction to Encoding */
		NFECCSTAT |= (1 << 25);		/* clear 8/12/16bit ecc encode done */
	}	
	NFCONT |= (1 << 5);			/* Initialize main area ECC decoder/encoder */
		  
	NFECCCONF = (511 << 16) |	/* The ECC message size(For 512-byte message, you should set 511) */
			(0x3 << 0);		/* 8-bit ECC/512B */

	NFSTAT |= ((1<<4) | (1<<5));
			
	NFECCCONT |= (0x1 << 2);	/* Initialize main area ECC decoder/ encoder */
	NFCONT &= ~(1 << 7);		/* Unlock Main area ECC   */
}

static int tq210_nand_calculate_ecc(struct mtd_info *mtd, const u_char *dat,
				      u_char *ecc_code)
{

	u32 nfeccprgecc0 = 0, nfeccprgecc1 = 0, nfeccprgecc2 = 0, nfeccprgecc3 = 0;

	/* Lock Main area ECC */
	NFCONT |= (1<<7); //writel(readl(&nand->nfcont) | (1 << 7), &nand->nfcont);
	

	nfeccprgecc0 = NFECCPRGECC0;
	nfeccprgecc1 = NFECCPRGECC1;
	nfeccprgecc2 = NFECCPRGECC2;
	nfeccprgecc3 = NFECCPRGECC3;

	ecc_code[0] = nfeccprgecc0 & 0xff;
	ecc_code[1] = (nfeccprgecc0 >> 8) & 0xff;
	ecc_code[2] = (nfeccprgecc0 >> 16) & 0xff;
	ecc_code[3] = (nfeccprgecc0 >> 24) & 0xff;
	ecc_code[4] = nfeccprgecc1 & 0xff;
	ecc_code[5] = (nfeccprgecc1 >> 8) & 0xff;
	ecc_code[6] = (nfeccprgecc1 >> 16) & 0xff;
	ecc_code[7] = (nfeccprgecc1 >> 24) & 0xff;
	ecc_code[8] = nfeccprgecc2 & 0xff;
	ecc_code[9] = (nfeccprgecc2 >> 8) & 0xff;
	ecc_code[10] = (nfeccprgecc2 >> 16) & 0xff;
	ecc_code[11] = (nfeccprgecc2 >> 24) & 0xff;
	ecc_code[12] = nfeccprgecc3 & 0xff;
	
	debug("s5pv210_nand_calculate_hwecc(%p,):\n"
		"0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n"
		"0x%02x 0x%02x 0x%02x\n", mtd , ecc_code[0], ecc_code[1], ecc_code[2], 
		ecc_code[3], ecc_code[4], ecc_code[5], ecc_code[6], ecc_code[7], 
		ecc_code[8], ecc_code[9], ecc_code[10], ecc_code[11], ecc_code[12]);

	return 0;
}

static int tq210_nand_correct_data(struct mtd_info *mtd, u_char *dat,
				     u_char *read_ecc, u_char *calc_ecc)
{
	if (read_ecc[0] == calc_ecc[0] &&
	    read_ecc[1] == calc_ecc[1] &&
	    read_ecc[2] == calc_ecc[2])
		return 0;

	printf("s5pv210_nand_correct_data: not implemented\n");
	return 0;
}

/* add by zjh */
#define NF8_ReadPage_Adv(a,b,c) (((int(*)(u32, u32, u8*))(*((u32 *)0xD0037F90)))(a,b,c))
static int tq210_nand_read_page_hwecc(struct mtd_info *mtd, struct nand_chip *chip,
				uint8_t *buf, int oob_required, int page)
{
	return NF8_ReadPage_Adv(page / 64, page % 64, buf);
}

#endif


int board_nand_init(struct nand_chip *nand)
{
	/* HCLK_PSYS=133MHz(7.5ns) */
	NFCONF =	(0x1 << 23) |	/* Disable 1-bit and 4-bit ECC */
				/* œ¬√Ê3∏ˆ ±º‰≤Œ ˝…‘Œ¢±»º∆À„≥ˆµƒ÷µ¥Û–©£®Œ“’‚¿Ô“¿¥Œº”1£©£¨∑Ò‘Ú∂¡–¥≤ªŒ»∂® */
				(0x3 << 12) |	/* 7.5ns * 2 > 12ns tALS tCLS */
				(0x2 << 8) | 	/* (1+1) * 7.5ns > 12ns (tWP) */
				(0x1 << 4) | 	/* (0+1) * 7.5 > 5ns (tCLH/tALH) */
				(0x0 << 3) | 	/* SLC NAND Flash */
				(0x0 << 2) |	/* 2KBytes/Page */
				(0x1 << 1);		/* 5 address cycle */
				
	/* 
	** The setting all nCE[3:0] zero can not be allowed. Only 
	** one nCE can be asserted to enable external NAND flash 
	** memory. The lower bit has more priority when user set all 
	** nCE[3:0] zeros. 
	*/
	NFCONT =	(0x1 << 1) |	/* Disable chip select */
				(0x1 << 0);		/* Enable NAND Flash Controller */
					
	/*
	** Port Map
	** CE1->Xm0CSn2-> MP01_2
	** CE2->Xm0CSn3-> MP01_3
	** CE3->Xm0CSn4-> MP01_4
	** CE4->Xm0CSn5-> MP01_5
	** CLE->Xm0FCLE-> MP03_0
	** ALE->Xm0FALE-> MP03_1
	** WE->Xm0FWEn->  MP03_2
	** RE->Xm0FREn->  MP03_3
	** RB1->Xm0FRnB0->MP03_4
	** RB2->Xm0FRnB1->MP03_5
	** RB3->Xm0FRnB2->MP03_6
	** RB4->Xm0FRnB3->MP03_7
	** IO[7:0]->Xm0DATA[7:0]->MP0_6[7:0]
	*/
	MP0_1CON &= ~(0xFFFF << 8);
	MP0_1CON |= (0x3333 << 8);
	MP0_3CON = 0x22222222;
	MP0_6CON = 0x22222222;
	
	tq210_nand_reset();
	
	nand->select_chip 	= tq210_nand_select_chip;
	nand->cmd_ctrl 	 	= tq210_nand_cmd_ctrl;
	nand->dev_ready		= tq210_nand_dev_ready;


#ifdef CONFIG_TQ210_NAND_HWECC
	nand->ecc.hwctl = tq210_nand_enable_hwecc;
	nand->ecc.calculate = tq210_nand_calculate_ecc;
	nand->ecc.correct = tq210_nand_correct_data;
	nand->ecc.mode = NAND_ECC_HW;
	nand->ecc.size = CONFIG_SYS_NAND_ECCSIZE;
	nand->ecc.bytes = CONFIG_SYS_NAND_ECCBYTES;
	nand->ecc.strength = 1;
	nand->ecc.layout = &nand_oob_64;	
	nand->ecc.read_page = tq210_nand_read_page_hwecc;
#else
	nand->ecc.mode = NAND_ECC_SOFT;
#endif
	nand->options |= NAND_NO_SUBPAGE_WRITE;

	return 0;
}
